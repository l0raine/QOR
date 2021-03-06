//WinQLDeviceInstanceModel.cpp

// Copyright Querysoft Limited 2016
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#include "WinQL/CodeServices/WinQLPolicy.h"
#include "WinQL/CodeServices/Text/WinString.h"
#include "WinQL/System/Devices/Instances/WinQLDeviceInstanceModel.h"
#include "WinQL/Definitions/Constants.h"
#include "WinQAPI/Kernel32.h"
#include "WinQAPI/SetupAPI.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	using namespace nsWinQAPI;

	//--------------------------------------------------------------------------------
	__QOR_IMPLEMENT_OCLASS_LUID( CDeviceInstanceModel );

	//--------------------------------------------------------------------------------
	CDeviceInstanceModel::CDeviceInstanceModel( nsMammut::CModel* pContainer ) : BaseName( pContainer )
	,	m_Properties( this )
	,	m_ID					(	&m_Properties, CTString( _TXT( "ID"			) ) )
	,	m_ulIndex				(	&m_Properties, CTString( _TXT( "Index"		) ) )
	,	m_Info					(	&m_Properties, CTString( _TXT( "Info"		) ) )
	,	m_PDOName				(	this, CTString( _TXT( "PDOName"				) ) )
	,	m_Location				(	this, CTString( _TXT( "Location"			) ) )
	,	m_FriendlyName			(	this, CTString( _TXT( "Friendly Name"		) ) )
	,	m_Manufacturer			(	this, CTString( _TXT( "Manufacturer"		) ) )
	,	m_DisplayName			(	this, CTString( _TXT( "DisplayName"			) ) )
	,	m_Description			(	this, CTString( _TXT( "Description"			) ) )
	,	m_Parent				(	this, CTString( _TXT( "Parent"				) ) )
	,	m_Service				(	this, CTString( _TXT( "Service"				) ) )
	,	m_SetupClassName		(	this, CTString( _TXT( "SetupClassName"		) ) )
	,	m_Driver				(	this, CTString( _TXT( "Driver"				) ) )
	{
		Initialize();
	}

	//--------------------------------------------------------------------------------
	CDeviceInstanceModel::CDeviceInstanceModel( const CDeviceInstanceModel& src) : BaseName( src.m_pContainer )
	,	m_Properties( this )
	,	m_ID					(	&m_Properties, CTString( _TXT( "ID"			) ) )
	,	m_ulIndex				(	&m_Properties, CTString( _TXT( "Index"		) ) )
	,	m_Info					(	&m_Properties, CTString( _TXT( "Info"		) ) )	
	,	m_PDOName				(	this, CTString( _TXT( "PDOName"				) ) )
	,	m_Location				(	this, CTString( _TXT( "Location"			) ) )
	,	m_FriendlyName			(	this, CTString( _TXT( "Friendly Name"		) ) )
	,	m_Manufacturer			(	this, CTString( _TXT( "Manufacturer"		) ) )
	,	m_DisplayName			(	this, CTString( _TXT( "DisplayName"			) ) )
	,	m_Description			(	this, CTString( _TXT( "Description"			) ) )
	,	m_Parent				(	this, CTString( _TXT( "Parent"				) ) )
	,	m_Service				(	this, CTString( _TXT( "Service"				) ) )
	,	m_SetupClassName		(	this, CTString( _TXT( "SetupClassName"		) ) )
	,	m_Driver				(	this, CTString( _TXT( "Driver"				) ) )
	{		
		Initialize();
		*this = src;
	}

	//--------------------------------------------------------------------------------
	void CDeviceInstanceModel::Initialize()
	{		
		insert( CTString( _TXT( "Properties" ) ), m_Properties.Ref() );
		insert( CTString( _TXT( "Interfaces" ) ), m_Interfaces.Ref() );
	}

	//--------------------------------------------------------------------------------
	CDeviceInstanceModel& CDeviceInstanceModel::operator = ( const CDeviceInstanceModel& src )
	{
		if( &src != this )
		{
			nsMammut::CModel::operator=( src );
		}
		return *this;
	}

	//--------------------------------------------------------------------------------
	CDeviceInstanceModel::~CDeviceInstanceModel()
	{
	}

	//--------------------------------------------------------------------------------
	CDeviceStringProperty::CDeviceStringProperty( CDeviceInstanceModel* pModel, const CTString& strName, unsigned long ulPropertyIndex ) :
		BaseName(dynamic_cast< nsMammut::CModel* >(pModel), strName, this), m_pModel(pModel), m_ulPropertyIndex(ulPropertyIndex)
	{
	}

}//nsWin32
