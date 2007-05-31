/*
 * main.c
 *
 * Main routine of the BioAPI sample application
 */

#pragma warning (disable:4115)
#include <windows.h>
#include "bioapi.h"
#include "bioapi_schema.h"
#include "port/bioapi_port.h"
#include "bioapi_uuid.h"
#include "bioapi_util.h"
#include "resource.h"

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;
BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam);
BioAPI_RETURN OutputToFile(LPTSTR lptszUserName, BioAPI_BIR_HANDLE BirHandle);
BioAPI_RETURN InputFromFile(LPTSTR lptszUserName, BioAPI_INPUT_BIR * InputBir);
void RegisterWindowsClass(HINSTANCE hInstance, WNDCLASSEX * wndclass);
void PrintErrorCode(BioAPI_RETURN bioReturn);
BioAPI_RETURN BiometricEventHandler(BioAPI_UUID *BSPUuid,
									void * AppNotifyCallbackCtx,
									BioAPI_DEVICE_ID DeviceID,
									uint32 Reserved,
									BioAPI_MODULE_EVENT EventType);
void ReleaseBSP(BioAPI_UUID_PTR * uuid);

HWND g_hWnd;
HWND hUserId, hEnumTech, hCurrHbt;
BioAPI_HANDLE gModuleHandle;
TCHAR  szAppName[] = TEXT("BioAPISample");


int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
					PSTR szCmdLine, int iCmdShow)
	{
		HWND		 hwnd ;
		MSG			 msg ;
		WNDCLASSEX	 wndclass ;
		BioAPI_RETURN bioReturn;
		BioAPI_VERSION bioVersion;
		BioAPI_BSP_SCHEMA * BspSchemaArray;
		BioAPI_BSP_SCHEMA * CurrSchema;
		int index;
		uint32 ArraySize, ElementsNeeded, NumElementsReturned, i;

		RegisterWindowsClass(hInstance, &wndclass);

		bioVersion.Major = BioAPI_MAJOR;
		bioVersion.Minor = BioAPI_MINOR;
		bioReturn = BioAPI_Init(&bioVersion, 0, NULL, 0, NULL);
		if(BioAPI_OK != bioReturn)
			{
				if(BioAPIERR_H_FRAMEWORK_INCOMPATIBLE_VERSION == bioReturn)
					{
						MessageBox(GetActiveWindow(),
							TEXT("This application is not compatible with the installed version of the BioAPI"),
								TEXT("BioAPI Error"),
									MB_OK | MB_ICONSTOP);
					}
				else
					{
						PrintErrorCode(bioReturn);
					}
				return 0;

			}
		gModuleHandle = 0;
		hwnd = CreateDialog (hInstance, szAppName, 0, NULL) ;

		ShowWindow (hwnd, iCmdShow) ;

		EnumChildWindows(hwnd, EnumChildProc, IDC_USERID);
		hUserId = g_hWnd;
		EnumChildWindows(hwnd, EnumChildProc, IDC_BIOTECH);
		hEnumTech = g_hWnd;
		EnumChildWindows(hwnd, EnumChildProc, IDC_CURRENTHBT);
		hCurrHbt = g_hWnd;

		bioReturn = BioAPI_EnumModules(NULL,
									0,
									&ElementsNeeded,
									&NumElementsReturned);

		if(bioReturn != BioAPI_OK)
			{
				PrintErrorCode(bioReturn);
				return 0;
			}
		ArraySize = ElementsNeeded;
		BspSchemaArray = (BioAPI_BSP_SCHEMA *)malloc(ElementsNeeded * sizeof(BioAPI_BSP_SCHEMA));
		if(BspSchemaArray == NULL)
		{
			MessageBox(GetActiveWindow(), TEXT("Unable to allocate BSP list"),
									TEXT("BioAPI Sample"), MB_OK);
			return 0;
		}
		bioReturn = BioAPI_EnumModules(BspSchemaArray,
									ArraySize,
									&ElementsNeeded,
									&NumElementsReturned);
		if(bioReturn != BioAPI_OK)
			{
				PrintErrorCode(bioReturn);
				free(BspSchemaArray);
				return 0;
			}
		CurrSchema = BspSchemaArray;
		for(i = 0; i < NumElementsReturned; i ++)
			{
				index = SendMessage(hEnumTech, CB_ADDSTRING, (WPARAM)0, (LPARAM)(CurrSchema->Description));
				SendMessage(hEnumTech, CB_SETITEMDATA, (WPARAM)index, (LPARAM)CurrSchema);
				CurrSchema ++;
			}

		 while (GetMessage (&msg, NULL, 0, 0))
			{
				TranslateMessage (&msg) ;
				DispatchMessage (&msg) ;
			}
		 free(BspSchemaArray);
		 BioAPI_Terminate();
		 return msg.wParam ;
	}

LRESULT CALLBACK WndProc (HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
	{
		HDC hdc;
		PAINTSTRUCT ps;
		RECT rc;
		HBRUSH hBrush, hBrushOld;
		HPEN hPen, hPenOld;
		LOGBRUSH lgBrush;
		int index;
		static BioAPI_UUID_PTR uuid;
		BioAPI_RETURN bioReturn;
		TCHAR szUserName[100];
		BioAPI_VERSION Version;

		BioAPI_BIR_HANDLE EnrolledTemplate, CapturedTemplate, ProcessedBir;

		BioAPI_INPUT_BIR birEnroll, birCapture, InputBirProcessed;
		BioAPI_BIR_HEADER birHeader;
		BioAPI_FAR MaxFAR, AchievedFAR;

		BioAPI_BOOL bResponse;
		BioAPI_BOOL bPrecedence = BioAPI_TRUE;

		static BioAPI_BSP_SCHEMA * CurrSchema;

		switch (iMsg)
			{
			case WM_PAINT :
				hdc = BeginPaint(hwnd, &ps);
				GetClientRect(hwnd, &rc);
				lgBrush.lbStyle = BS_SOLID;
				lgBrush.lbColor = GetSysColor(COLOR_3DFACE);
				hBrush = CreateBrushIndirect(&lgBrush);
				hPen = CreatePen(PS_SOLID, 0, GetSysColor(COLOR_3DFACE));
				hPenOld = SelectObject(hdc, hPen);
				hBrushOld = SelectObject(hdc, hBrush);
				Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
				SelectObject(hdc, hBrushOld);
				SelectObject(hdc, hPenOld);
				DeleteObject(hBrush);
				DeleteObject(hPen);
				EndPaint(hwnd, &ps);
				return 0;

			case WM_COMMAND :
				switch (HIWORD (wParam))
					{
					case CBN_SELCHANGE :
						ReleaseBSP(&uuid);

						// Retrieve the index of the item selected
						index = SendMessage(hEnumTech, CB_GETCURSEL, 0, 0);
						// Retrieve a pointer to the uuid for the module
						CurrSchema = (BioAPI_BSP_SCHEMA *)SendMessage(hEnumTech, CB_GETITEMDATA, index, 0);
						uuid = (BioAPI_UUID *)malloc(sizeof(BioAPI_UUID));
						if(uuid == NULL)
						{
							MessageBox(hwnd, TEXT("Unable to allocate memory to load the module identifier"),
										TEXT("BioAPI Sample"), MB_OK);
							return 0;
						}
						BioAPI_CopyUuid(uuid, CurrSchema->ModuleId);
						bioReturn = BioAPI_ModuleLoad(uuid, 0, NULL/*(BioAPI_ModuleEventHandler)BiometricEventHandler*/, 0);

						if(BioAPI_OK != bioReturn)
							{
								PrintErrorCode(bioReturn);
								free(uuid);
								uuid = NULL;
								return 0;
							}
//						wsprintf(szCurrHandle, TEXT("Current Handle: 0x%X"), hBtCurrent);
//						SetWindowText(hCurrHbt, szCurrHandle);

						Version.Major = BioAPI_MAJOR;
						Version.Minor = BioAPI_MINOR;
						bioReturn = BioAPI_ModuleAttach(uuid, &Version, &BioAPIWinMemoryFuncs,
										0,
										0,0,0,
										NULL,
										0,
										NULL,
										&gModuleHandle);
						if(BioAPI_OK != bioReturn)
							{
								PrintErrorCode(bioReturn);
								BioAPI_ModuleUnload (uuid, NULL, 0);
								free(uuid);
								uuid = NULL;
								return 0;
							}

						break;

					case BN_CLICKED:
						switch (LOWORD (wParam))
							{
								case IDOK :
									ReleaseBSP(&uuid);
									EndDialog(hwnd, 0);
									PostQuitMessage(0);
									break;
								case IDC_ENROLL :
									if(GetWindowText(hUserId, szUserName, 100)==0)
										MessageBox(hwnd, TEXT("Please specify a user id"), TEXT("Bad User Id"), MB_OK);
									else
										{
											bioReturn = BioAPI_Enroll(gModuleHandle,
															BioAPI_PURPOSE_ENROLL_FOR_VERIFICATION_ONLY,
															NULL,
															&EnrolledTemplate,
															NULL,
															-1,
															NULL);

											if(bioReturn != BioAPI_OK)
												{
													PrintErrorCode(bioReturn);
													return 0;
												}

											OutputToFile(szUserName, EnrolledTemplate);
										}
									break;
								case IDC_VERIFY :
									if(GetWindowText(hUserId, szUserName, 100)==0)
										MessageBox(hwnd, TEXT("Please specify a user id"), TEXT("Bad User Id"), MB_OK);
									else
										{
											if(InputFromFile(szUserName, &birEnroll) != BioAPI_OK)
												{
													MessageBox(hwnd, TEXT("User not enrolled"), TEXT("Bad User Id"), MB_OK);
													return 0;
												}
											// See if the BSP supports BioAPI_VerifyMatch by checking
											// the operations mask
											if(CurrSchema->Operations & BioAPI_VERIFYMATCH)
												{
													if((bioReturn = BioAPI_Capture(gModuleHandle,
																		BioAPI_PURPOSE_VERIFY,
																		&CapturedTemplate,
																		-1,
																		NULL)) != BioAPI_OK)
														{
															PrintErrorCode(bioReturn);
															GlobalFree(birEnroll.InputBIR.BIR);
															return 0;
														}
													if((bioReturn = BioAPI_GetHeaderFromHandle(gModuleHandle,
																		CapturedTemplate,
																		&birHeader)) != BioAPI_OK)
														{
															PrintErrorCode(bioReturn);
															GlobalFree(birEnroll.InputBIR.BIR);
															return 0;
														}
													if(birHeader.Type == BioAPI_BIR_DATA_TYPE_INTERMEDIATE)
														{
															birCapture.Form = BioAPI_BIR_HANDLE_INPUT;
															birCapture.InputBIR.BIRinBSP = &CapturedTemplate;
															if((bioReturn = BioAPI_Process(gModuleHandle,
																				&birCapture,
																				&ProcessedBir)) != BioAPI_OK)
																{
																	PrintErrorCode(bioReturn);
																	GlobalFree(birEnroll.InputBIR.BIR);
																	return 0;
																}
															MaxFAR = 1;
															InputBirProcessed.Form = BioAPI_BIR_HANDLE_INPUT;
															InputBirProcessed.InputBIR.BIRinBSP = &ProcessedBir;
														}
													else
														{
															MaxFAR = 1;
															InputBirProcessed.Form = BioAPI_BIR_HANDLE_INPUT;
															InputBirProcessed.InputBIR.BIRinBSP = &CapturedTemplate;
														}
													bioReturn = BioAPI_VerifyMatch(gModuleHandle,
																	&MaxFAR,
																	NULL,
																	&bPrecedence,
																	&InputBirProcessed,
																	&birEnroll,
																	NULL,
																	&bResponse,
																	&AchievedFAR,
																	NULL,
																	NULL);
												}
											else		// We simply call BioAPI_Verify
												{
													MaxFAR = 1;
													bioReturn = BioAPI_Verify(gModuleHandle,
																				&MaxFAR,
																				NULL,
																				&bPrecedence,
																				&birEnroll,
																				NULL,
																				&bResponse,
																				&AchievedFAR,
																				NULL,
																				NULL,
																				-1,
																				NULL);
												}
											GlobalFree(birEnroll.InputBIR.BIR);

											if(bioReturn != BioAPI_OK)
												{
													PrintErrorCode(bioReturn);
													return 0;
												}
											if(bResponse == TRUE)
												MessageBox(hwnd, TEXT("Match"), TEXT("BioAPI"), MB_OK);
											else MessageBox(hwnd, TEXT("No Match"), TEXT("BioAPI"), MB_OK);
										}
									break;
							}
						break;
					}
				return 0 ;
			case WM_CLOSE :
				ReleaseBSP(&uuid);
				EndDialog(hwnd, 0);
				PostQuitMessage(0);
				return 0;
			case WM_DESTROY :
				ReleaseBSP(&uuid);
				EndDialog(hwnd, 0);
				PostQuitMessage(0);
				return 0 ;
			}
		return DefWindowProc (hwnd, iMsg, wParam, lParam) ;
	}



BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam)

	{
		long lId;

		lId = GetWindowLong(hwnd, GWL_ID);
		if(lId == lParam)
			{
				g_hWnd = hwnd;
//				return FALSE;
			}
		return TRUE;
	}

BioAPI_RETURN OutputToFile(LPTSTR lptszUserName, BioAPI_BIR_HANDLE BirHandle)

	{
		TCHAR szFileName[_MAX_PATH];
		HANDLE hFile;
		DWORD dwBytesToWrite, dwBytesWritten;
		BioAPI_BIR_PTR birData = NULL;
		BioAPI_RETURN bioReturn;

		/* Retrieve the BIR from the BSP */
		bioReturn = BioAPI_GetBIRFromHandle(gModuleHandle,
							BirHandle,
							&birData);
		if(bioReturn != BioAPI_OK)
			return(bioReturn);

		/* Open the file */
		wsprintf(szFileName, TEXT("c:\\%s.bir"), lptszUserName);
		hFile = CreateFile(szFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
			return(0); /* this return value is ignored anyway */

		/* Write the header */
		WriteFile(hFile, &(birData->Header), sizeof (BioAPI_BIR_HEADER), &dwBytesWritten, NULL);

		/* Write the biometric data */
		dwBytesToWrite = LocalEndian4 (birData->Header.Length) - sizeof (BioAPI_BIR_HEADER);
		WriteFile(hFile, birData->BiometricData, dwBytesToWrite, &dwBytesWritten, NULL);

		/* Write the signature if present */
		if (birData->Signature)
		{
			WriteFile(hFile, &(birData->Signature->Length), 4, &dwBytesWritten, NULL);
			dwBytesToWrite = LocalEndian4 (birData->Signature->Length);
			WriteFile(hFile, birData->Signature->Data, dwBytesToWrite, &dwBytesWritten, NULL);
		}

		/* Close the file */
		CloseHandle(hFile);

		/* Free all the memory allocated for the BIR */
		GlobalFree(birData->BiometricData);
		if (birData->Signature)
		{
			GlobalFree (birData->Signature->Data);
			GlobalFree (birData->Signature);
		}
		GlobalFree(birData);

		return(BioAPI_OK);
	}

BioAPI_RETURN InputFromFile(LPTSTR lptszUserName, BioAPI_INPUT_BIR * InputBir)

	{
		TCHAR szFileName[_MAX_PATH];
		HANDLE hFile;
		DWORD dwBytesToRead, dwBytesRead;
		BioAPI_BIR *bir;

		/* Open the file */
		wsprintf(szFileName, TEXT("c:\\%s.bir"), lptszUserName);
		hFile = CreateFile(szFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if(hFile == INVALID_HANDLE_VALUE)
			return BioAPIERR_BSP_RECORD_NOT_FOUND; // Return this BSP error if the file isn't present

		/* Read the header in, to determine the size */
		dwBytesToRead = sizeof(BioAPI_BIR_HEADER);
		bir = GlobalAlloc(GPTR, sizeof (BioAPI_BIR));
		if (!bir)
			return (!BioAPI_OK);
		ReadFile(hFile, &(bir->Header), dwBytesToRead, &dwBytesRead, NULL);

		/* Read the biometric data */
		dwBytesToRead = LocalEndian4 (bir->Header.Length) - sizeof (BioAPI_BIR_HEADER);
		bir->BiometricData = GlobalAlloc(GPTR, dwBytesToRead);
		if (!bir->BiometricData)
			return (!BioAPI_OK);
		ReadFile(hFile, bir->BiometricData, dwBytesToRead, &dwBytesRead, NULL);

		/* Read the signature if present */
		dwBytesToRead = 0;
		if (ReadFile(hFile, &dwBytesToRead, 4, &dwBytesRead, NULL) != 0 &&
				dwBytesToRead != 0)
		{
			bir->Signature = GlobalAlloc(GPTR, sizeof (BioAPI_DATA));
			if (!bir->Signature)
				return (!BioAPI_OK);
			bir->Signature->Length = dwBytesToRead;
			dwBytesToRead = LocalEndian4 (dwBytesToRead);
			bir->Signature->Data = GlobalAlloc(GPTR, dwBytesToRead);
			if (!bir->Signature->Data)
				return (!BioAPI_OK);
			ReadFile(hFile, bir->Signature->Data, dwBytesToRead, &dwBytesRead, NULL);
		}

		/* Close the file */
		CloseHandle(hFile);

		/* Set up the return values */
		InputBir->InputBIR.BIR = bir;
		InputBir->Form = BioAPI_FULLBIR_INPUT;

		return(BioAPI_OK);
	}

void RegisterWindowsClass(HINSTANCE hInstance, WNDCLASSEX * wndclass)

	{

		wndclass->cbSize		= sizeof (*wndclass) ;
		wndclass->style			= CS_HREDRAW | CS_VREDRAW;
		wndclass->lpfnWndProc	= WndProc ;
		wndclass->cbClsExtra	= 0 ;
		wndclass->cbWndExtra	= DLGWINDOWEXTRA ;
		wndclass->hInstance		= hInstance ;
		wndclass->hIcon			= LoadIcon (hInstance, szAppName) ;
		wndclass->hCursor		= LoadCursor (NULL, IDC_ARROW) ;
		wndclass->hbrBackground = (HBRUSH) (COLOR_WINDOW + 1) ;
		wndclass->lpszMenuName	= NULL ;
		wndclass->lpszClassName = szAppName ;
		wndclass->hIconSm		= LoadIcon (hInstance, szAppName) ;
		RegisterClassEx (wndclass) ;
	}

void PrintErrorCode(BioAPI_RETURN bioReturn)

	{
		TCHAR szMessage[255];

		wsprintf(szMessage, TEXT("BioAPI Error Code: %ld"), bioReturn);
		MessageBox(GetActiveWindow(), szMessage, TEXT("BioAPI Error"), MB_OK | MB_ICONSTOP);
	}


BioAPI_RETURN BiometricEventHandler(BioAPI_UUID *BSPUuid,
									void * AppNotifyCallbackCtx,
									BioAPI_DEVICE_ID DeviceID,
									uint32 Reserved,
									BioAPI_MODULE_EVENT EventType)

	{
		BioAPI_RETURN bioReturn = BioAPI_OK;
		BioAPI_VERSION Version;

		switch(EventType)
			{
			case BioAPI_NOTIFY_INSERT :
				if(gModuleHandle == 0)
				{
					Version.Major = BioAPI_MAJOR;
					Version.Minor = BioAPI_MINOR;
					bioReturn = BioAPI_ModuleAttach(BSPUuid, &Version, &BioAPIWinMemoryFuncs,
									DeviceID,
									0,0,0,
									NULL,
									0,
									NULL,
									&gModuleHandle);
				}

				break;
			case BioAPI_NOTIFY_REMOVE :
				if(gModuleHandle != 0)
				{
					bioReturn = BioAPI_ModuleDetach(gModuleHandle);
					gModuleHandle = 0;
				}
				break;
			case BioAPI_NOTIFY_FAULT :
				break;
			case BioAPI_NOTIFY_SOURCE_PRESENT :
				break;
			case BioAPI_NOTIFY_SOURCE_REMOVED :
				break;
			}
		if(bioReturn != BioAPI_OK)
			PrintErrorCode(bioReturn);

		return(bioReturn);
	}


void ReleaseBSP(BioAPI_UUID_PTR * uuid)

{
	BioAPI_RETURN bioReturn;
	// If the device is attached (which is signified by hCurrentBiometric NOT being equal to
	// 0) then call BioAPI_ModuleDetach.
	if(gModuleHandle != 0)
		{
			bioReturn = BioAPI_ModuleDetach(gModuleHandle);
			if(BioAPI_OK != bioReturn)
				{
					PrintErrorCode(bioReturn);
					return;
				}
			gModuleHandle = 0;
		}
	// If the Module was loaded (which is signified by the uuid NOT being equal to 0) then call
	// BioAPI_ModuleUnload.
	if(*uuid != NULL)
		{
			bioReturn = BioAPI_ModuleUnload(*uuid, NULL/*(BioAPI_ModuleEventHandler)BiometricEventHandler*/, 0);
			if(BioAPI_OK != bioReturn)
				{
					PrintErrorCode(bioReturn);
					return;
				}
			free(*uuid);
			*uuid = NULL;
		}

}