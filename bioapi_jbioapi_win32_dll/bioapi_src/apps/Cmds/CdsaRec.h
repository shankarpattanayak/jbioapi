/*-----------------------------------------------------------------------
 * File: CDSAREC.H
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */


// CdsaRec.h: interface for the CCdsaRec class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CDSAREC_H__27F7C8CA_6CF4_11D2_A091_00A0C90988EF__INCLUDED_)
#define AFX_CDSAREC_H__27F7C8CA_6CF4_11D2_A091_00A0C90988EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Rec.h"
#include "appmemtrack.h"
#include "cssmMemTrack.h"

template < class RecInfoType >
class CCdsaRec : public CRec
{
public:
	virtual int NumAttributes() const;

	virtual int FindStringInRecord(LPCTSTR szString,
								   BOOL bMatchWholeWordOnly,
								   BOOL bMatchCase,
								   BOOL bExamineAttrName,
								   BOOL bExamineAttrValue,
								   int iStartSearchAt = 0);

	CCdsaRec(const RecInfoType & recType,
			 CRecType *pRecType,
			 CSSM_DB_UNIQUE_RECORD_PTR recordId = NULL,
			 const CSSM_DB_RECORD_ATTRIBUTE_DATA_PTR outputAttributes = NULL);
	virtual ~CCdsaRec();

};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

template <class RecInfoType >
CCdsaRec< RecInfoType >::CCdsaRec(const RecInfoType & recType,
							  CRecType *pRecType,
							  CSSM_DB_UNIQUE_RECORD_PTR recordId,
							  const CSSM_DB_RECORD_ATTRIBUTE_DATA_PTR outputAttributes) :
	CRec( pRecType, recordId )
{
	m_outputAttributeData = new CSSM_DB_ATTRIBUTE_DATA[m_pRecType->m_dwNumAttrs];

	if ( outputAttributes )
	{
		memcpy(
			m_outputAttributeData,
			outputAttributes->AttributeData,
			sizeof(CSSM_DB_ATTRIBUTE_DATA)*(m_pRecType->m_dwNumAttrs));

		memcpy(
			&m_outputAttributes,
			outputAttributes,
			sizeof(m_outputAttributes));
	}
	m_outputAttributes.AttributeData = m_outputAttributeData;
}

template <class RecInfoType >
CCdsaRec< RecInfoType >::~CCdsaRec()
{
	for ( DWORD i = 0; i < m_pRecType->m_dwNumAttrs; i++ )
	{
		CSSM_FREE_WRAPPER(CMdsUtil_free, m_outputAttributeData[i].Value->Data, &CMdsUtil_AllocRef );
		memset( &m_outputAttributeData[i].Value, 0, sizeof(m_outputAttributeData[i].Value) );
	}

	delete [] m_outputAttributeData;
	m_outputAttributeData = NULL;
}

template <class RecInfoType >
int CCdsaRec< RecInfoType >::NumAttributes() const
{
	return m_pRecType->m_dwNumAttrs;
}

template <class RecInfoType >
int CCdsaRec< RecInfoType >::FindStringInRecord(LPCTSTR szString,
												BOOL bMatchWholeWordOnly,
												BOOL bMatchCase,
												BOOL bExamineAttrName,
												BOOL bExamineAttrValue,
												int iStartSearchAt)
{
	ASSERT( bExamineAttrName || bExamineAttrValue );
	CString strString = szString;
	if ( !bMatchCase )
	{
		strString.MakeLower();
	}

	ASSERT( strString != "" );
	for ( DWORD i = iStartSearchAt; i < m_pRecType->m_dwNumAttrs; i++ )
	{
		CString strAttrName	 = m_outputAttributeData[i].Info.Label.AttributeName;
		CString strAttrValue = m_outputAttributeData[i].Value->Data;

		if ( !bMatchCase )
		{
			strAttrName.MakeLower();
			strAttrValue.MakeLower();
		}

		if ( bExamineAttrName )
		{
			if ((bMatchWholeWordOnly  && (strString == strAttrName))	||
				(!bMatchWholeWordOnly && (strAttrName.Find(strString) != -1)))
			{
				return i;
			}
		}

		if (bExamineAttrValue									&&
			(m_outputAttributeData[i].Info.AttributeFormat ==
			 CSSM_DB_ATTRIBUTE_FORMAT_STRING)					&&
			 m_outputAttributeData[i].Value->Data)
		{
			if ((bMatchWholeWordOnly  && (strString == strAttrValue))	||
				(!bMatchWholeWordOnly && (strAttrValue.Find(strString) != -1)))
			{
				return i;
			}
		}
	}

	return -1;
}

#endif // !defined(AFX_CDSAREC_H__27F7C8CA_6CF4_11D2_A091_00A0C90988EF__INCLUDED_)
