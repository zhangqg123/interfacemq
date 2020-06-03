#pragma once

// 计算机生成了由 Microsoft Visual C++ 创建的 IDispatch 包装类

// 注意: 不要修改此文件的内容。如果此类由
//  Microsoft Visual C++ 重新生成，您的修改将被覆盖。

/////////////////////////////////////////////////////////////////////////////
// CDbcommocxctrlfc71 包装类

class CDbcommocxctrlfc71 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CDbcommocxctrlfc71)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x82192883, 0x43C6, 0x441F, { 0xA7, 0xC4, 0x4A, 0x75, 0xB0, 0xE8, 0xCE, 0xD5 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// 特性
public:
enum
{
    STATUS_OK = 0,
    STATUS_NOCONNECT = 1,
    STATUS_INIT = 2,
    STATUS_DISCONNECT = 3,
    STATUS_RECONNECT = 4,
    STATUS_NOLIC = 5,
    STATUS_INITFALSE = 6
}StatusValue;


// 操作
public:

// _DDbCommOcxFC7

// Functions
//

	long OpenLocalConnect()
	{
		long result;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long OpenRemoteConnect(BSTR * RemoteAddr, long RemotePortNo, BSTR * LocalAddr, long LocalPortNo)
	{
		long result;
		static BYTE parms[] = VTS_PBSTR VTS_I4 VTS_PBSTR VTS_I4 ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, RemoteAddr, RemotePortNo, LocalAddr, LocalPortNo);
		return result;
	}
	void CloseConnect()
	{
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	VARIANT GetData(VARIANT TagName)
	{
		VARIANT result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, &TagName);
		return result;
	}
	long SetData(VARIANT TagName, VARIANT TagData)
	{
		long result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, parms, &TagName, &TagData);
		return result;
	}
	VARIANT GetHisData(DATE StartTime, DATE EndTime, long DataCount, VARIANT TagName)
	{
		VARIANT result;
		static BYTE parms[] = VTS_DATE VTS_DATE VTS_I4 VTS_VARIANT ;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, StartTime, EndTime, DataCount, &TagName);
		return result;
	}
	long GetStatus()
	{
		long result;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	BOOL IsWorking()
	{
		BOOL result;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL IsConnected()
	{
		BOOL result;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	long InsertHisData(BSTR * TagName, VARIANT DataTime, VARIANT DataTimeSh, VARIANT DataValue)
	{
		long result;
		static BYTE parms[] = VTS_PBSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_I4, (void*)&result, parms, TagName, &DataTime, &DataTimeSh, &DataValue);
		return result;
	}
	long GetAllTagCount()
	{
		long result;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	VARIANT GetAllTagName()
	{
		VARIANT result;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	long GetTagParCount(BSTR * TagName)
	{
		long result;
		static BYTE parms[] = VTS_PBSTR ;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_I4, (void*)&result, parms, TagName);
		return result;
	}
	long GetTagType(BSTR * TagName)
	{
		long result;
		static BYTE parms[] = VTS_PBSTR ;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_I4, (void*)&result, parms, TagName);
		return result;
	}
	VARIANT GetTagTypePars(long TagType)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, TagType);
		return result;
	}
	VARIANT GetNodeAllTagName(long AreaNo)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, AreaNo);
		return result;
	}
	VARIANT GetNodeInfo(long AreaNo)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x13, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, AreaNo);
		return result;
	}
	VARIANT GetTagPars(BSTR * TagName)
	{
		VARIANT result;
		static BYTE parms[] = VTS_PBSTR ;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, TagName);
		return result;
	}
	VARIANT GetRegData(VARIANT TagName)
	{
		VARIANT result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, &TagName);
		return result;
	}
	VARIANT SetChangeTagPars(VARIANT TagName)
	{
		VARIANT result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, &TagName);
		return result;
	}
	long DelChangeTagParsByName(VARIANT TagName)
	{
		long result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x17, DISPATCH_METHOD, VT_I4, (void*)&result, parms, &TagName);
		return result;
	}
	long DelChangeTagParsByRegNo(VARIANT RegNo)
	{
		long result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x18, DISPATCH_METHOD, VT_I4, (void*)&result, parms, &RegNo);
		return result;
	}
	BOOL RemoveChangeTagPars()
	{
		BOOL result;
		InvokeHelper(0x19, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	VARIANT GetHisTrace(DATE StartTime, DATE EndTime, BSTR * TagName)
	{
		VARIANT result;
		static BYTE parms[] = VTS_DATE VTS_DATE VTS_PBSTR ;
		InvokeHelper(0x1a, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, StartTime, EndTime, TagName);
		return result;
	}
	BOOL GetMarkupLayerStr(BSTR * MarkerLayerStr)
	{
		BOOL result;
		static BYTE parms[] = VTS_PBSTR ;
		InvokeHelper(0x1b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, MarkerLayerStr);
		return result;
	}
	long GetAlarmCount()
	{
		long result;
		InvokeHelper(0x1c, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	VARIANT GetAlarmData(long lBegin, long lCount, long * lRetCount)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PI4 ;
		InvokeHelper(0x1d, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, lBegin, lCount, lRetCount);
		return result;
	}
	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

// Properties
//

long GetTimeOut()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}
void SetTimeOut(long propVal)
{
	SetProperty(0x1, VT_I4, propVal);
}
long GetUpDateTime()
{
	long result;
	GetProperty(0x2, VT_I4, (void*)&result);
	return result;
}
void SetUpDateTime(long propVal)
{
	SetProperty(0x2, VT_I4, propVal);
}


};
