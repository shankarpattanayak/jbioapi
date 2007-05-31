/*-----------------------------------------------------------------------
 * File: RECTYPE.H
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */


// RecType.h: interface for the CRecType class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECTYPE_H__6111832B_6C46_11D2_A091_00A0C90988EF__INCLUDED_)
#define AFX_RECTYPE_H__6111832B_6C46_11D2_A091_00A0C90988EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMDS;
class CDir;
class CRec;

class CRecType : public CObject
{
public:
	virtual CRec * NewRec( CSSM_DB_UNIQUE_RECORD_PTR recordId ) = 0;
	virtual CRec * NextRec() = 0;
	virtual CRec * FirstRec() = 0;
	CDir * m_pDir;
	CSSM_DB_RECORDTYPE m_dwRecType;
	DWORD m_dwNumAttrs;
	CSSM_DB_ATTRIBUTE_DATA_PTR m_outputAttributeData;
	CSSM_DB_RECORD_ATTRIBUTE_DATA m_outputAttributes;

	CSSM_DB_UNIQUE_RECORD_PTR FirstRecordId( CSSM_DB_RECORD_ATTRIBUTE_DATA & outputAttributes );
	CSSM_DB_UNIQUE_RECORD_PTR NextRecordId( CSSM_DB_RECORD_ATTRIBUTE_DATA & outputAttributes );
	virtual CString Name() const = 0;
	CRecType( CDir *pDir, CSSM_DB_RECORDTYPE dwRecType, DWORD dwNumAttrs );
	virtual ~CRecType();

#ifdef _DEBUG
	virtual void AssertValid() const;
#endif

protected:
	CSSM_QUERY m_cqQuery;
	CSSM_BOOL m_cbEndOfDataStore;
	CSSM_HANDLE m_resultsHandle;
};

#endif // !defined(AFX_RECTYPE_H__6111832B_6C46_11D2_A091_00A0C90988EF__INCLUDED_)
