 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagCallParameter_StructInfo.h"

Serialize__tagCallParameter::_Myt& Serialize__tagCallParameter::operator=(_tagCallParameter & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagCallParameter::GetData()
{
	m_Val.szPassword=szPassword; 
	m_Val.bCallSuccess=bCallSuccess; 
	m_Val.ObjectPath=ObjectPath; 
	m_Val.Object=Object; 
	m_Val.tagObjectState=tagObjectState; 
	m_Val.nError=nError; 
	m_Val.szFinder=szFinder; 
	m_Val.DirectoryInfo=DirectoryInfo; 
	m_Val.strPar=strPar;
}

BOOL Serialize__tagCallParameter::Construct(StorageObjectInterface * pOutObject)
{
	szPassword.init(this,_T("szPassword"),0,pOutObject); 
	bCallSuccess.init(this,_T("bCallSuccess"),0,pOutObject); 
	ObjectPath.init(this,_T("ObjectPath"),0,pOutObject); 
	Object.init(this,_T("Object"),0,pOutObject); 
	tagObjectState.init(this,_T("tagObjectState"),0,pOutObject); 
	nError.init(this,_T("nError"),0,pOutObject); 
	szFinder.init(this,_T("szFinder"),0,pOutObject); 
	DirectoryInfo.init(this,_T("DirectoryInfo"),0,pOutObject); 
	strPar.init(this,_T("strPar"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagCallParameter::SetData(_tagCallParameter & _X)
{
	szPassword=_X.szPassword; 
	bCallSuccess=_X.bCallSuccess; 
	ObjectPath=_X.ObjectPath; 
	Object=_X.Object; 
	tagObjectState=_X.tagObjectState; 
	nError=_X.nError; 
	szFinder=_X.szFinder; 
	DirectoryInfo=_X.DirectoryInfo; 
	strPar=_X.strPar;
}

BOOL Serialize__tagCallParameter::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szPassword")))
	{
		*RetObj=&szPassword;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("bCallSuccess")))
	{
		*RetObj=&bCallSuccess;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ObjectPath")))
	{
		*RetObj=&ObjectPath;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("Object")))
	{
		*RetObj=&Object;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("tagObjectState")))
	{
		*RetObj=&tagObjectState;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nError")))
	{
		*RetObj=&nError;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szFinder")))
	{
		*RetObj=&szFinder;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("DirectoryInfo")))
	{
		*RetObj=&DirectoryInfo;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("strPar")))
	{
		*RetObj=&strPar;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagCallParameter::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagCallParameter"),this);

	szPassword.Save(pStorageObject); 
	bCallSuccess.Save(pStorageObject); 
	ObjectPath.Save(pStorageObject); 
	Object.Save(pStorageObject); 
	tagObjectState.Save(pStorageObject); 
	nError.Save(pStorageObject); 
	szFinder.Save(pStorageObject); 
	DirectoryInfo.Save(pStorageObject); 
	strPar.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagCallParameter"),this);
	return TRUE;
}

BOOL Serialize__tagCallParameter::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szPassword); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&bCallSuccess); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ObjectPath); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&Object); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&tagObjectState); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nError); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szFinder); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&DirectoryInfo); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&strPar);
	return TRUE;
}




