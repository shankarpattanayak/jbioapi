/*-----------------------------------------------------------------------
 * File: CDSARECTYPE.H
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */


// CdsaRecType.h: interface for the CdsaRecType template class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CDSARECORDTYPE_H__27F7C8BB_6CF4_11D2_A091_00A0C90988EF__INCLUDED_)
#define AFX_CDSARECORDTYPE_H__27F7C8BB_6CF4_11D2_A091_00A0C90988EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "recType.h"
#include "MdsRecType.h"

class CDir;

template < class RecInfoType >
class CCdsaRecType : public CRecType
{
public:
	virtual CRec * NewRec( CSSM_DB_UNIQUE_RECORD_PTR recordId );
	virtual CRec * NextRec();
	virtual CRec * FirstRec();
	virtual CString Name() const;
	CCdsaRecType( const RecInfoType & recType, CDir *pDir );
	virtual ~CCdsaRecType();

	void SpecifyAttributes();

	CString m_strName;
};

#include "CdsaRec.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

template < class RecInfoType >
CCdsaRecType< RecInfoType >::CCdsaRecType(const RecInfoType & recType, CDir *pDir) :
	m_strName( recType.m_strName ),
	CRecType( pDir, recType.m_dwRecType, recType.m_dwNumAttrs )
{
	m_outputAttributeData =
		new CSSM_DB_ATTRIBUTE_DATA[m_dwNumAttrs];

	m_cqQuery.RecordType			 = recType.m_dwRecType;
	m_cqQuery.Conjunctive			 = CSSM_DB_NONE;
	m_cqQuery.NumSelectionPredicates = 0;
	m_cqQuery.SelectionPredicate	 = NULL;
	m_cqQuery.QueryLimits.TimeLimit	 = CSSM_QUERY_TIMELIMIT_NONE;
	m_cqQuery.QueryLimits.SizeLimit	 = CSSM_QUERY_SIZELIMIT_NONE;
	m_cqQuery.QueryFlags			 = 0;

	memset( &m_outputAttributes, 0, sizeof(CSSM_DB_RECORD_ATTRIBUTE_DATA) );
	m_outputAttributes.DataRecordType	  = m_dwRecType;
	m_outputAttributes.NumberOfAttributes = m_dwNumAttrs;
	m_outputAttributes.AttributeData	  = (struct cssm_db_attribute_data *) m_outputAttributeData;

	SpecifyAttributes();
}

template < class RecInfoType >
CCdsaRecType< RecInfoType >::~CCdsaRecType()
{
	delete [] m_outputAttributeData;
	m_outputAttributeData = NULL;
}

template < class RecInfoType >
CString CCdsaRecType< RecInfoType >::Name() const
{
	return m_strName;
}

template < class RecInfoType >
CRec * CCdsaRecType< RecInfoType >::FirstRec()
{
	CRec * pRec = NULL;
	CSSM_DB_UNIQUE_RECORD_PTR recordId =
		CRecType::FirstRecordId( m_outputAttributes );
	if ( recordId )
	{
		RecInfoType recType;
		pRec =
			new CCdsaRec< RecInfoType >(
					recType,
					this,
					recordId,
					&m_outputAttributes);
	}

	return pRec;
}

template < class RecInfoType >
CRec * CCdsaRecType< RecInfoType >::NextRec()
{
	CRec * pRec = NULL;
	CSSM_DB_UNIQUE_RECORD_PTR recordId =
		CRecType::NextRecordId( m_outputAttributes );
	if ( recordId )
	{
		RecInfoType recType;
		pRec =
			new CCdsaRec< RecInfoType >(
					recType,
					this,
					recordId,
					&m_outputAttributes);
	}

	return pRec;
}

template <class RecInfoType >
CRec * CCdsaRecType< RecInfoType >::NewRec(CSSM_DB_UNIQUE_RECORD_PTR recordId)
{
	RecInfoType recInfoType;
	CRec * pRec =
		new CCdsaRec< RecInfoType >(
				recInfoType,
				this,
				recordId,
				&m_outputAttributes);

	return pRec;
}

#endif // !defined(AFX_CDSARECORDTYPE_H__27F7C8BB_6CF4_11D2_A091_00A0C90988EF__INCLUDED_)
