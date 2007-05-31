/*-----------------------------------------------------------------------
 * File: REC.H
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */


// Rec.h: interface for the CRec class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REC_H__6111832E_6C46_11D2_A091_00A0C90988EF__INCLUDED_)
#define AFX_REC_H__6111832E_6C46_11D2_A091_00A0C90988EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRecType;

class CRec : public CObject
{
	CRec() :	//this is not a bug.  Yes, it is a private constructor.
		m_pRecType( NULL ),
		m_recordId( NULL ),
		m_outputAttributeData( NULL )
	{
		memset( &m_outputAttributes, 0, sizeof(m_outputAttributes) );
	}

public:
	DECLARE_SERIAL( CRec )
	void Serialize( CArchive& archive );

	static BOOL s_bViewBlobAsString;
	virtual int FindStringInRecord(LPCTSTR szString,
								   BOOL bMatchWholeWordOnly,
								   BOOL bMatchCase,
								   BOOL bExamineAttrName,
								   BOOL bExamineAttrValue,
								   int iStartSearchAt = 0) { return -1;}

	CString operator [](int i) const;

	CString AttributeFormatBlob( int i ) const;
	CString AttributeFormatString( int i ) const;
	CString AttributeFormatUint32( int i ) const;
	CString AttributeFormatSint32( int i ) const;
	CString AttributeFormatMultiUint32( int i ) const;

	CRecType * m_pRecType;
	CSSM_DB_UNIQUE_RECORD_PTR m_recordId;
	CSSM_DB_ATTRIBUTE_DATA_PTR m_outputAttributeData;
	CSSM_DB_RECORD_ATTRIBUTE_DATA m_outputAttributes;

	CRec(CRecType * pRectType,
		 CSSM_DB_UNIQUE_RECORD_PTR recordId);
	virtual ~CRec();

#ifdef _DEBUG
	virtual void AssertValid() const;
#endif

protected:
};

#endif // !defined(AFX_REC_H__6111832E_6C46_11D2_A091_00A0C90988EF__INCLUDED_)
