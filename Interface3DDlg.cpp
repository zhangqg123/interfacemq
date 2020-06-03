//m_bAutoDestroyBmp

// Interface3DDlg.cpp : 实现文件 -- 测试文件
//

#include "stdafx.h"
#include "Interface3D.h"
#include "Interface3DDlg.h"
#include "afxdialogex.h"
//#include  "DBManager.h"
#include "Markup.h"
#include "SetDlg.h"
#include "AddItem.h"
//active mq
#include <sstream>
#include <stdlib.h>  
#include <stdio.h>  
#include <iostream>  
#include <memory>  
#include <locale>

#include <DbgHelp.h>
#pragma comment(lib,"Dbghelp.lib")
//using namespace activemq::core;   


#pragma warning(disable:4204)
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_UPDATWLIST   WM_USER + 100
#define WM_TRAY         WM_USER + 101
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

static int g_nStrid[21][17] = {
	IDS_STRING_01,IDS_STRING_02,IDS_STRING_03,IDS_STRING_04,IDS_STRING_05,IDS_STRING_07,IDS_STRING_08,IDS_STRING_09,IDS_STRING_10,IDS_STRING_11,
	IDS_STRING_12,IDS_STRING121,IDS_STRING122,-1,-1,-1,-1,
	IDS_STRING123,IDS_STRING124,IDS_STRING125,IDS_STRING126,IDS_STRING127,IDS_STRING128,IDS_STRING129,IDS_STRING130,IDS_STRING131,IDS_STRING132,
	-1,-1,-1,-1,-1,-1,-1,
	IDS_STRING133,IDS_STRING134,IDS_STRING135,IDS_STRING136,IDS_STRING137,IDS_STRING138,IDS_STRING139,IDS_STRING140,IDS_STRING141,IDS_STRING142,
	IDS_STRING143,IDS_STRING144,IDS_STRING145,IDS_STRING146,IDS_STRING147,IDS_STRING148,IDS_STRING132,
	IDS_STRING150,IDS_STRING140,IDS_STRING151,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	IDS_STRING152,IDS_STRING153,IDS_STRING154,IDS_STRING155,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	IDS_STRING156,IDS_STRING157,IDS_STRING158,IDS_STRING159,IDS_STRING160,IDS_STRING161,IDS_STRING162,IDS_STRING163,IDS_STRING164,IDS_STRING165,
	IDS_STRING166,IDS_STRING167,IDS_STRING168,IDS_STRING169,IDS_STRING170,IDS_STRING132,-1,
	IDS_STRING171,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	IDS_STRING146,IDS_STRING172,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	IDS_STRING173,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	IDS_STRING171,IDS_STRING174,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	IDS_STRING173,IDS_STRING175,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	IDS_STRING173,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	IDS_STRING173,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	IDS_STRING173,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	IDS_STRING173,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	IDS_STRING176,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	IDS_STRING177,IDS_STRING182,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	IDS_STRING177,IDS_STRING178,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	IDS_STRING173,IDS_STRING179,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	IDS_STRING173,IDS_STRING180,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	IDS_STRING181,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
};

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CInterface3DDlg 对话框

CInterface3DDlg::CInterface3DDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInterface3DDlg::IDD, pParent)
	, m_csDeviceName(_T(""))
	, m_csIndex(_T(""))
	, m_csContext(_T(""))
	, m_csIODeviceName(_T(""))
	, m_csSourceID(_T(""))
	, m_csOriAlarmLevel(_T(""))
	, m_csAlarmLevel(_T(""))
	, m_csCompress(_T(""))
	, m_csIndexEx(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_csSceneName = _T("");
	m_csDeviceId = _T("");
	m_csType = _T("");
	m_csDataType = _T("");
	m_connection = NULL;  
	m_csPointType = _T("");
	m_trPara.bIsExit = TRUE;
	m_bFlagStop = FALSE;
	m_nStateus = 0;
	m_threadNumber=0;
	m_nItemIndex = 0;
	m_csItemEnglish = _T("");
	m_csTypeNum = _T("");
	m_csAlaCause = _T("");
	m_csAlaColor = _T("");
	m_csAlaType = _T("");
	m_csAlaLevel = _T("");
	m_nAlaCount = 0;
	m_nTagType = 0;
	m_bSendAlarm = FALSE;

	/****************  hjq *********************/
	m_csIODeviceName = _T("");	//IO设备名称
	m_csSourceID = _T("");		//来源标识
	m_csOriAlarmLevel = _T("");	//原始告警级别
	m_csAlarmLevel = _T("");	//告警级别
	m_csCompress = _T("");		//压缩标识
	m_csIndexEx = _T("");		//指标实例
}


CInterface3DDlg::~CInterface3DDlg()
{
	
	POSITION pos =	m_pSceneList.GetHeadPosition();
	while(pos != NULL)//场景
	{
		Scene_para *pScene = (Scene_para *)m_pSceneList.GetNext(pos);
		POSITION posBuild =	pScene->pBuildList.GetHeadPosition();
		while(posBuild != NULL)//楼宇
		{
			Build_para *pBuild = (Build_para *)pScene->pBuildList.GetNext(posBuild);
			POSITION posFloor =	pBuild->pFloorList.GetHeadPosition();
			while(posFloor != NULL)//楼层
			{
				Floor_para *pFloor = (Floor_para *)pBuild->pFloorList.GetNext(posFloor);
				POSITION posRoom =	pFloor->pRoomList.GetHeadPosition();
				while(posRoom != NULL)//房间
				{
					Room_para *pRoom = (Room_para *)pFloor->pRoomList.GetNext(posRoom);
					POSITION posDevice = pRoom->pDeviceList.GetHeadPosition();
					while(posDevice != NULL)//设备
					{
						Device *pDevice = (Device *)pRoom->pDeviceList.GetNext(posDevice);
						POSITION pos2 =	pDevice->pPointList.GetHeadPosition();
						while(pos2 != NULL)
						{
							POINT_DB *pPoint = (POINT_DB *)pDevice->pPointList.GetNext(pos2);
							delete pPoint;
						}
						delete pDevice;
					}
					delete pRoom;
				}
				delete pFloor;
			}
			delete pBuild;
		}
		delete pScene;
	}
	m_trPara.bIsExit = FALSE;

	if(m_threadNumber>0){
		for(int i = 0;i < m_threadNumber; i++){
//			WaitForSingleObject(m_trPara.pThre[i],100);
			if(WaitForSingleObject(m_trPara.pThre[i],INFINITE) == WAIT_OBJECT_0)  //等待退出
			{
//				m_trPara.pThre[i]->ResumeThread();
			}

		}	
	}


	try{  
		if( m_connection != NULL) 
		{
			m_connection->close(); 
			delete m_connection;  
			m_connection = NULL; 
			activemq::library::ActiveMQCPP::shutdownLibrary();
		}
	}
	catch ( CMSException& e ) {
		e.printStackTrace();
	}  
	  
	
}

void CInterface3DDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DBCOMMOCXCTRLFC71, m_dbCom);
	DDX_Control(pDX, IDC_LIST_CUR_NODE, m_clCurNode);
	DDX_Control(pDX, IDC_LIST_ALL_NODE, m_clAllNode);
	DDX_Control(pDX, IDC_LIST_CUR_NODE, m_clCurNode);
	DDX_Text(pDX, IDC_COMB_SCENE_NAME, m_csSceneName);
	DDX_Text(pDX, IDC_COMB_DEVICE_ID, m_csDeviceId);
	DDX_Control(pDX, IDC_TREE_SCENE, m_TreeCtrl);
	DDX_Text(pDX, IDC_COMB_DEVICE_NAME, m_csDeviceName);
	DDX_CBString(pDX, IDC_COMBO_TYPE, m_csType);
	DDX_Control(pDX, IDC_COMBO_POINT, m_cbPointType);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cbType);
	DDX_CBString(pDX, IDC_COMBO_POINT, m_csPointType);
	//DDX_Control(pDX, IDC_COMBO_INDEX, m_index);
	DDX_Control(pDX, IDC_COMBO_INDEX, m_cbIndex);
	DDX_CBString(pDX, IDC_COMBO_INDEX, m_csIndex);
	DDX_Text(pDX, IDC_EDIT1, m_csContext);


	DDX_Control(pDX, IDC_COMB_SCENE_NAME, m_cbSceneName);
	DDX_Control(pDX, IDC_COMB_DEVICE_NAME, m_cbDeviceName);
	DDX_Control(pDX, IDC_COMB_DEVICE_ID, m_cbDeviceID);
	DDX_Control(pDX, IDC_COMB_BUILDING_NAME, m_cbBuildName);
	DDX_Control(pDX, IDC_COMB_FLOOR_NAME, m_cbFloorName);
	DDX_Control(pDX, IDC_COMB_ROOM_NAME, m_cbRoomName);
	DDX_Control(pDX, IDC_COMB_ALM_CAUSE, m_cbAlaCause);
	DDX_Control(pDX, IDC_COMB_ALM_TYPE, m_cbAlaType);

	DDX_Text(pDX, IDC_COMB_BUILDING_NAME, m_csBuildName);
	DDX_Text(pDX, IDC_COMB_FLOOR_NAME, m_csFloorName);
	DDX_Text(pDX, IDC_COMB_ROOM_NAME, m_csRoomName);
	DDX_Text(pDX, IDC_COMB_ALM_CAUSE, m_csAlaCause);
	DDX_Text(pDX, IDC_COMB_ALM_TYPE, m_csAlaType);
	DDX_Control(pDX, IDC_BTN_ALM_COLOR, m_MfcBtnAlmColor);
	DDX_Control(pDX, IDC_COMB_IO_DEVICE_NAME, m_cbIODeviceName);
	DDX_CBString(pDX, IDC_COMB_IO_DEVICE_NAME, m_csIODeviceName);
	DDX_Control(pDX, IDC_COMB_SOURCE_ID, m_cbSourceID);
	DDX_CBString(pDX, IDC_COMB_SOURCE_ID, m_csSourceID);
	DDX_Control(pDX, IDC_COMB_ORI_ALARM_LEVEL, m_cbOriAlarmLevel);
	DDX_CBString(pDX, IDC_COMB_ORI_ALARM_LEVEL, m_csOriAlarmLevel);
	DDX_Control(pDX, IDC_COMB_ALARM_LEVEL, m_cbAlarmLevel);
	DDX_CBString(pDX, IDC_COMB_ALARM_LEVEL, m_csAlarmLevel);
	DDX_Control(pDX, IDC_COMB_COMPRESS_ID, m_cbCompress);
	DDX_CBString(pDX, IDC_COMB_COMPRESS_ID, m_csCompress);
	DDX_Control(pDX, IDC_COMB_DEVICE_ID2, m_cbIndexEx);
	DDX_CBString(pDX, IDC_COMB_DEVICE_ID2, m_csIndexEx);
}

BEGIN_MESSAGE_MAP(CInterface3DDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CInterface3DDlg::OnBnClickedOk)
	ON_WM_TIMER()
	ON_LBN_SELCHANGE(IDC_LIST_ALL_NODE, &CInterface3DDlg::OnLbnSelchangeListAllNode)
	ON_LBN_SELCHANGE(IDC_LIST_CUR_NODE, &CInterface3DDlg::OnLbnSelchangeListCurNode)
	ON_BN_CLICKED(ID_ITEM_DELETE, &CInterface3DDlg::OnBnClickedDelete)
	ON_CBN_SELCHANGE(IDC_COMBO_INDEX, &CInterface3DDlg::OnCbnSelchangeComboIndex)
	ON_BN_CLICKED(IDC_BUTTON1, &CInterface3DDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CInterface3DDlg::OnBnClickedButton2)
	ON_MESSAGE(WM_TRAY,OnBnTray)
	ON_BN_CLICKED(IDC_BTN_ITEMADD, &CInterface3DDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_ITEMDEl, &CInterface3DDlg::OnBnClickedBtnItemdel)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_ALM_COLOR, &CInterface3DDlg::OnBnClickeBtnAlmColor)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_TREE_SCENE, &CInterface3DDlg::OnCustomdrawTreeScene)
END_MESSAGE_MAP()


// CInterface3DDlg 消息处理程序

long  __stdcall CrashInfocallback( _EXCEPTION_POINTERS *pexcp)
{
	if (pexcp != NULL)
	{	
		//获取一下保存路径
		TCHAR szAppPath[MAX_PATH] = {0};
		if (_tcsclen(szAppPath) <= 0)
		{
			GetCurrentDirectory( MAX_PATH, szAppPath); 
		}
		if (_tcsclen(szAppPath) <= 0)
		{
			GetTempPath(MAX_PATH, szAppPath); //获取失败 那就用临时目录吧
		}

		//设置保存dmp路径及名称
		CString csSaveFile(szAppPath);
		csSaveFile += _T("\\");
		CTime tm = CTime::GetCurrentTime();
		CString strFileName;
		strFileName.Format(_T("InterfaceCMS.exe_%02d-%02d-%02d %02d-%02d-%02d.dmp"), 
			tm.GetYear(), tm.GetMonth(), tm.GetDay(), tm.GetHour()
			,tm.GetMinute(), tm.GetSecond());
		csSaveFile += strFileName;

		//创建dmp文件
		HANDLE hDumpFile = ::CreateFile(
			csSaveFile,
			GENERIC_WRITE,  //写入
			0, //不共享
			NULL,  //默认安全属性
			CREATE_ALWAYS,  //总是创建
			FILE_ATTRIBUTE_NORMAL, //默认属性
			NULL //为NULL，则不利用其他文件扩展属性
			);
		if( hDumpFile != INVALID_HANDLE_VALUE)
		{
			MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
			dumpInfo.ExceptionPointers = pexcp;
			dumpInfo.ThreadId = ::GetCurrentThreadId();
			dumpInfo.ClientPointers = TRUE;

			::MiniDumpWriteDump(
				::GetCurrentProcess(),
				::GetCurrentProcessId(),
				hDumpFile,
				MiniDumpNormal,
				&dumpInfo,
				NULL,
				NULL
				);

			::CloseHandle(hDumpFile);
		}
	}
	return 0;
}


BOOL CInterface3DDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化

	::SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)CrashInfocallback);

	m_MfcBtnAlmColor.SetFaceColor(RGB(128,0,128));
	m_csAlaColor.Format(_T("#%X"),RGB(128,0,128));

	m_dbCom.OpenLocalConnect();	
	int nRet = m_dbCom.IsConnected();
	m_cbPointType.SetCurSel(0);
	m_cbDataType.SetCurSel(0);
	m_cbIndex.SetCurSel(0);
	m_cbSceneName.SetCurSel(0);//场景名
	m_cbDeviceName.SetCurSel(0);//设备名
	m_cbDeviceID.SetCurSel(0);//设备ID
	m_cbBuildName.SetCurSel(0);//楼宇
	m_cbFloorName.SetCurSel(0);//楼层
	m_cbRoomName.SetCurSel(0);//房间
	m_cbAlaCause.SetCurSel(0);//告警原因
	m_cbAlaType.SetCurSel(0);//告警类型
//	OnCbnSelchangeComboIndex();

	m_cbIODeviceName.SetCurSel(0);	//IO设备名称
	m_cbSourceID.SetCurSel(0);		//来源标识
	m_cbOriAlarmLevel.SetCurSel(0);	//原始告警级别
	m_cbAlarmLevel.SetCurSel(0);		//告警级别
	m_cbCompress.SetCurSel(0);		//压缩标识
	m_cbIndexEx.SetCurSel(0);		//指标实例

	activemq::library::ActiveMQCPP::initializeLibrary();//
	ThreadBegin();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void CInterface3DDlg::InitActiveMQ(void)
{
	OutputDebugString(_T("[hao]:InitActiveMQ: ----------start"));
	CString csTmp = _T("failover:(tcp://") + m_csIP + _T(":") + m_csPort + _T(")");
	if(csTmp.IsEmpty())
	{
		AfxMessageBox(_T("IP为空"));
		return;
	}
	CStringA csTmpA;
	csTmpA = csTmp;
	string brokerURI = csTmpA.GetBuffer();
	csTmpA.ReleaseBuffer();

	try {  
		// Create a ConnectionFactory  
		auto_ptr<ConnectionFactory> connectionFactory(ConnectionFactory::createCMSConnectionFactory(brokerURI));  

		if(connectionFactory.get())  //只能指针是否为空
		{
			// Create a Connection  
			m_connection = connectionFactory->createConnection();
			if (m_connection == NULL)
			{
				AfxMessageBox(_T("初始化创建Connection失败"));
			}
			else
			{
				m_connection->start();	//DDian
			}
		} 

	}catch ( CMSException& e ) {  
		OutputDebugString(_T("[hao]:InitActiveMQ: ----------CMSException"));
		e.printStackTrace();  
	} 
	OutputDebugString(_T("[hao]:InitActiveMQ: ----------end"));
}

void CInterface3DDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CInterface3DDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CInterface3DDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

string CInterface3DDlg::CStrToStr(CString str)
{
	CStringA csAss(str);
//	csAss = str;
	string s = csAss.GetBuffer(0);
	csAss.ReleaseBuffer();
	return s;
}

//告警
void CInterface3DDlg::AlarmJsonString(LPVOID pS,LPVOID pB,LPVOID pF,LPVOID pR,LPVOID pD,LPVOID pT,double pv,int tn)
{
	Scene_para *ps = (Scene_para *)pS;
	Build_para *pb = (Build_para *)pB;
	Floor_para *pf = (Floor_para *)pF;
	Room_para *pr = (Room_para *)pR;
	Device *pd = (Device *)pD;
	POINT_DB *pt = (POINT_DB *)pT;

	//perf_time
	CTime time  = CTime::GetCurrentTime();
	CString csTime = time.Format("%Y-%m-%d %H:%M:%S");
	//project_id
	int nPos =  ps->csName.Find(_T("_"));
	CString csProID = ps->csName.Right(ps->csName.GetLength() - nPos - 1);//获取 "_" 后的数字
	int nProID = _ttoi(csProID);
	//floor_id
	nPos = pf->csName.Find(_T("_"));
	CString csFloorName = pf->csName.Right(pf->csName.GetLength() - nPos - 1);//获取 "_" 后的字符串
	//obj_id
	int nObjID = _ttoi(pt->csBigTypeNum);
	//alarm_type
	int nPosType = pt->csAlaType.Find(_T("("));
	CString csAlmType = pt->csAlaType.Mid(nPosType + 1,1);
	int nAlmType = _ttoi(csAlmType);
	//alarm_level
	int nAllLevel = _ttoi(pt->csAlaLevel);
	//status
	CString csValue;
	/*if (m_nTagType == 0)
	{
		csValue.Format(_T("%lf"),pv);
	}
	else if (m_nTagType == 1)
	{
		csValue.Format(_T("%d"),pv);
	}*/
	/*if (m_nTagType == 1)
		csValue.Format(_T("%d"),pv);
	else*/
		csValue.Format(_T("%lf"),pv);

	Json::Value Son;

	/*******************   hjq   ****************************/
	Son["Summary"] = Json::Value(CStrToStr(pt->csTagDESC));//数据库变量的DESC
	Son["SourceAlertKey"] = Json::Value(CStrToStr(pt->csType));//指标级
	Son["SourceSeverity"] = Json::Value(CStrToStr(pt->csOriAlarmLevel));
	Son["SourceIdentifier"] = Json::Value(CStrToStr(pt->csCompress));
	Son["SourceEventID"] = Json::Value(CStrToStr(pt->csLongTagName));//数据库点名
	Son["Severity"] = Json::Value(CStrToStr(pt->csAlarmLevel));
	Son["LastOccurrence"] = Json::Value(CStrToStr(csTime));	//时间
	Son["SourceCIName"] = Json::Value(CStrToStr(pt->csIODeviceName));
	Son["Status"] = Json::Value(CStrToStr(csValue));	//PV值
	Son["SourceID"] = Json::Value(CStrToStr(pt->csSourceID));

	if (m_bSendAlarm)
	{
		Jroot_A[tn][""].append(Son);
		pt->nState = pv;
	}
	else
	{
		Jroot_A[tn].clear();
	}

	/*
	[
		{
			"Summary": "CPU使⽤用率⾼高于86%,设备负载过⾼高(来源于：BP2)",
			"SourceAlertKey": "CPU使⽤用率",
			"SourceSeverity": "Critical",
			"SourceIdentifier": "Identifier",
			"SourceEventID": "1455867577750",
			"Severity": "3",
			"LastOccurrence": "2018-08-19 17:18:23",
			"SourceCIName": "192.168.123.191",
			"Status": "1",
			"SourceID":"2"
		}
	]
	*/
}

//监控
void CInterface3DDlg::MonitorJsonString(LPVOID pS,LPVOID pB,LPVOID pF,LPVOID pR,LPVOID pD,LPVOID pT,double pv,int tn)
{
	Scene_para *ps = (Scene_para *)pS;
	Build_para *pb = (Build_para *)pB;
	Floor_para *pf = (Floor_para *)pF;
	Room_para *pr = (Room_para *)pR;
	Device *pd = (Device *)pD;
	POINT_DB *pt = (POINT_DB *)pT;
	
	Json::Value son;
	Json::Value grandSon;
	//根节点属性
	//判断为空时跳过
	if (pd->csName.IsEmpty()||pt->csBigType.IsEmpty()||pt->csType.IsEmpty())
	{
		return;
	}

	//perf_time
	CTime time  = CTime::GetCurrentTime();
	CString csTime = time.Format("%Y-%m-%d %H:%M:%S");
	//project_id
	int nPos =  ps->csName.Find(_T("_"));
	CString csProID = ps->csName.Right(ps->csName.GetLength() - nPos - 1);//获取 "_" 后的数字
	int nProID = _ttoi(csProID);
	//floor_id
	nPos = pf->csName.Find(_T("_"));
	CString csFloorName = pf->csName.Right(pf->csName.GetLength() - nPos - 1);//获取 "_" 后的字符串
	//monitor_type
	int nBigTypeNum = _ttoi(pt->csBigTypeNum);
	//var
	CString csVar;
	/*if (m_nTagType == 0)
	{
		csVar.Format(_T("%lf"),pv);
	}
	else if (m_nTagType == 1)
	{
		csVar.Format(_T("%d"),pv);
	}*/
	/*if (m_nTagType == 1)
		csVar.Format(_T("%d"),pv);
	else*/
		csVar.Format(_T("%lf"),pv);
	//val_type
	CString csValType;
	csValType.Format(_T("%d"),m_nTagType);

	/*******************   hjq   ****************************/

	son["ciCode"] = Json::Value(CStrToStr(pt->csIODeviceName));
	son["metric"] = Json::Value(CStrToStr(pt->csTagDESC));
	son["instance"] = Json::Value(CStrToStr(pt->csIndexEx));
	son["value"] = Json::Value(CStrToStr(csVar));
	son["timestamp"] = Json::Value(CStrToStr(csTime));
	Jroot_M[tn][""].append(son);
	/*
	[
		{
			"ciCode":"P211-E1-01",
			"metric":"CPU使⽤用率",
			"instance":"cpu0",
			"value":"50",
			"timestamp":"1500790703007"
		}
	]
	*/
}

string  CInterface3DDlg::UnicodetoUTF_8(string &pstrOut)
{
	/*CString cstrTest = _T("中");
	pstrOut = CT2A(cstrTest.GetString*/

	wchar_t*  wideStr; 
	const char * pszStrU8 = pstrOut.c_str(); 
	int   nCharLen;
	string strUTF;

	/*USES_CONVERSION;
	wideStr = A2W(pszStrU8);*/

	nCharLen = MultiByteToWideChar(CP_ACP, 0, pszStrU8, -1, NULL, 0); 	
	wideStr = (wchar_t*) new WCHAR[nCharLen + 1]; 
	memset((void*)wideStr,0,sizeof(wchar_t) * (nCharLen + 1));
	MultiByteToWideChar(CP_ACP, 0, pszStrU8, -1, wideStr, nCharLen);

	nCharLen = WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, NULL, 0, NULL, NULL);
	char * pszStr = (char*)new char[nCharLen + 1];
	memset((void*)pszStr,0,sizeof(char) * (nCharLen + 1));
	WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, pszStr, nCharLen, NULL, NULL);
	strUTF = pszStr;

	delete [] wideStr; 
	delete [] pszStr;
	return strUTF;
}
void CInterface3DDlg::SendTextMessage(string StrQueue,int tn,Session* m_session, MessageProducer* m_producer)
{
//	Session  * m_session;	//DDian
//	Destination *m_destination;
//	MessageProducer * m_producer;
	try
	{		
		//StrQueue = UnicodetoUTF_8(StrQueue,0) ;	//2019/11/26 发送工程名转换编码格式

//		if(m_connection == NULL)		return;

//		m_session = m_connection->createSession(Session::AUTO_ACKNOWLEDGE);		//DDian
//		m_destination = m_session->createQueue(StrQueue); 
//		m_producer = m_session->createProducer(m_destination);  

//		if(m_session)		OutputDebugString(_T("[hao]:		Connection::createSession"));
//		if(m_destination)	OutputDebugString(_T("[hao]:		Session::createQueue"));
//		if(m_producer)	OutputDebugString(_T("[hao]:		Session::createProducer"));
		

		TextMessage *message;	//DDian
		string strMessage = "",strMessageTmp = "";
		string::size_type idx;
		string strFind = "project_";
		idx = StrQueue.find(strFind);
		if(idx != string::npos)
		{
			CStringA csRootM(Jroot_M[tn].toStyledString().c_str());
			csRootM.Replace("\\\\","\\");
			strMessageTmp = csRootM.GetBuffer(0);
			strMessage = UnicodetoUTF_8(strMessageTmp) ;

			strMessage = strMessage.substr(strMessage.find('['),strMessage.find(']') - strMessage.find('[') + 1);
			message = m_session->createTextMessage(strMessage); 		//DDian
			OutputDebugString(_T("[hao]:		send开始"));
			m_producer->send(message);	//DDian
			OutputDebugString(_T("[hao]:		send结束"));
		}
		else
		{
			Destination *m_destination2;
			MessageProducer * m_producer2;
			m_destination2 = m_session->createQueue(StrQueue); 
			m_producer2 = m_session->createProducer(m_destination2);  

			CStringA csRootA(Jroot_A[tn].toStyledString().c_str());
			csRootA.Replace("\\\\","\\");
			strMessageTmp = csRootA.GetBuffer(0);
			strMessage = UnicodetoUTF_8(strMessageTmp) ;
			strMessage = strMessage.substr(strMessage.find('['),strMessage.find(']') - strMessage.find('[') + 1);
			message = m_session->createTextMessage(strMessage);		//DDian

			OutputDebugString(_T("[hao]:		createTextMessage"));
			CString csMesTmp;
			csMesTmp = strMessage.c_str();
			csMesTmp.Format(_T("[hao] 2: %s"),csMesTmp);
			OutputDebugString(csMesTmp);
			OutputDebugString(_T("[hao]:		send开始"));
			m_producer2->send(message);	//DDian
			OutputDebugString(_T("[hao]:		send结束"));
			if(m_destination2)
			{
				delete m_destination2;
			}
			if(m_producer2)
			{
				m_producer2->close();
				delete m_producer2;
			}
		}



		m_log.m_bFlagSend = TRUE;
		delete message;	//DDian
	}
	catch (CException* e)
	{
		
	}

/*	if(m_session)	//DDian
	{
		m_session->close();
		delete m_session;
	}

	if(m_destination)
	{
		delete m_destination;
	}
	if(m_producer)
	{
		m_producer->close();
		delete m_producer;
	}
*/	
}

void CInterface3DDlg::DoWork(Scene_para* pS,int tn,string StrQueue,Session* m_session,MessageProducer* m_producer)
{


	OutputDebugString(_T("[hao]: DoWork   -- start"));
	VARIANT vtTagName,vtTagDESC;
	VARIANT vtTagValue;
	//VariantInit(&vtTagName);
	CString csPName;
	
	POSITION  pos = m_pSceneList.GetHeadPosition();

	if(pos != NULL)
	{
		POSITION posBuild = pS->pBuildList.GetHeadPosition();

		while(posBuild != NULL)
		{
			Build_para *pB= (Build_para *)pS->pBuildList.GetNext(posBuild);
			POSITION posFloor = pB->pFloorList.GetHeadPosition();
			while(posFloor != NULL)
			{
				Floor_para *pFloor= (Floor_para *)pB->pFloorList.GetNext(posFloor);
				POSITION posRoom = pFloor->pRoomList.GetHeadPosition();
				while(posRoom != NULL)
				{
					Room_para *pRoom = (Room_para *)pFloor->pRoomList.GetNext(posRoom);
					POSITION posDevice = pRoom->pDeviceList.GetHeadPosition();
					while(posDevice != NULL)
					{
						Device *pPd= (Device *)pRoom->pDeviceList.GetNext(posDevice);
						POSITION pos2 = pPd->pPointList.GetHeadPosition();	
						Json::Value root;
						
						while(pos2 != NULL)
						{
							if(!Jroot_M[tn].isNull())
							{
								Jroot_M[tn].clear();//清空 elemt
							}
							if (!Jroot_A[tn].isNull())
							{
								Jroot_A[tn].clear();//清空 elemt
							}

							double dbValue = 0;
							Point_DB  *pPt= (Point_DB *)pPd->pPointList.GetNext(pos2);
							vtTagName.vt = VT_BSTR;
							CString csTagName;//长点名
							//CString csPV =  pPt->csPath +_T("\\") + pPt->csName;

							//节约内存，提升速度
							CString csPV = pPt->csPath;
							csPV += _T("\\");
							csPV += pPt->csName;
							pPt->csLongTagName = csPV;

							CString csDebugValue;
							csDebugValue.Format(_T("[hao]:	DB点名： %s"),csPV);
							OutputDebugString(csDebugValue);
							
							vtTagName.bstrVal = csPV.AllocSysString();
							
							vtTagValue = m_dbCom.GetData(vtTagName);
							
							//点类型 0 模拟点  1 数字点
							m_nTagType = m_dbCom.GetTagType(&vtTagName.bstrVal);
							
							
							//PV
							if (vtTagValue.vt != VT_NULL && vtTagValue.vt != VT_EMPTY)
							{
								SAFEARRAY* pSafeArray = vtTagValue.parray;

								VARIANT HUGEP* pbstrPv;
								//VariantInit(pbstrPv);
								SafeArrayAccessData(pSafeArray, (void HUGEP*FAR*)&pbstrPv);
								if (pbstrPv[0].vt == VT_R8)
								{
									dbValue = pbstrPv[0].dblVal;     //监控数据
								}
								else if(pbstrPv[0].vt == VT_I4)
								{
									dbValue = (double)pbstrPv[0].dblVal;
								}
					//			SysFreeString(vtTagName.bstrVal);
								SafeArrayUnaccessData(pSafeArray);
								SafeArrayDestroy(pSafeArray);

								csDebugValue.Format(_T("[hao]:	DB数值： %.4f"),dbValue);
								OutputDebugString(csDebugValue);
							}
							SysFreeString(vtTagName.bstrVal);
							VariantClear (&vtTagName);

							OutputDebugString(_T("[hao]:	---------------------------1"));
							//获取报警点DESC
							vtTagDESC.vt = VT_BSTR;
							pPt->csParDESC = csPV + _T(".DESC");
							vtTagDESC.bstrVal = pPt->csParDESC.AllocSysString();
							vtTagValue = m_dbCom.GetData(vtTagDESC);
							csDebugValue.Format(_T("[hao]:pPt->csParDESC： m_dbCom.GetData(%s)"),pPt->csParDESC);
							OutputDebugString(csDebugValue);
							OutputDebugString(_T("[hao]:	---------------------------2"));
							if (vtTagValue.vt != VT_NULL && vtTagValue.vt != VT_EMPTY)
							{
								OutputDebugString(_T("[hao]:	---------------------------3"));
								SAFEARRAY* pSafeArray = vtTagValue.parray;
								VARIANT HUGEP* pbstrPv;
								SafeArrayAccessData(pSafeArray, (void HUGEP*FAR*)&pbstrPv);
								if (pbstrPv[0].vt == VT_BSTR)
								{
									pPt->csTagDESC = pbstrPv[0].bstrVal;     //监控数据
								}			
								csDebugValue.Format(_T("[hao]:DESC： %s"),pPt->csTagDESC);
								OutputDebugString(csDebugValue);
								OutputDebugString(_T("[hao]:	---------------------------4"));
				//				SysFreeString(vtTagDESC.bstrVal);
								SafeArrayUnaccessData(pSafeArray);
								SafeArrayDestroy(pSafeArray);
								OutputDebugString(_T("[hao]:	---------------------------5"));
							}
							SysFreeString(vtTagDESC.bstrVal);
							VariantClear (&vtTagDESC);
							VariantClear (&vtTagValue);

							OutputDebugString(_T("[hao]:	---------------------------6"));
							m_bSendAlarm = FALSE;
							
							//报警
							
							POSITION pos1,pos2;
							CString csTagNameTmp;
							for (pos1 = m_cslistTagName.GetHeadPosition(); ( pos2 = pos1 ) != NULL;  )
							{
								OutputDebugString(_T("[hao]:	---------------------------7"));
								csTagNameTmp = m_cslistTagName.GetNext(pos1); 
								csDebugValue.Format(_T("[hao]: csTagNameTmp:%s "),csTagNameTmp);
								OutputDebugString(csDebugValue);
								csDebugValue.Format(_T("[hao]: csPV:%s "),csPV);
								OutputDebugString(csDebugValue);
								if (csTagNameTmp == csPV)
								{
									csDebugValue.Format(_T("[hao]:	检测到有报警产生 start"));
									m_bSendAlarm = TRUE;
									m_cslistTagName.RemoveAt(pos2);
									if (m_nTagType == 0)	//模拟点报警发送1
									{
										dbValue = 1;
									}
									csDebugValue.Format(_T("[hao]:	检测到有报警产生 end"));
								}
							}
							OutputDebugString(_T("[hao]:	---------------------------8"));
							//恢复
							AlarmTagInfo AlarmTagInfoStruct;
							for (pos1 = m_AlarmTagInfoList.GetHeadPosition(); ( pos2 = pos1 ) != NULL;  )
							{
								AlarmTagInfoStruct = m_AlarmTagInfoList.GetNext(pos1); 
								if (AlarmTagInfoStruct.csTagName == csPV)
								{
									if (AlarmTagInfoStruct.bFlag == 1)
									{
										if (AlarmTagInfoStruct.bAlarmTagType == 0)	//模拟点
										{
											if (AlarmTagInfoStruct.bLimitHiFlag == 1 && AlarmTagInfoStruct.bLimitLoFlag == 0)		//高报
											{
												if (AlarmTagInfoStruct.dbLimitHi >  dbValue)
												{
													m_bSendAlarm = TRUE;
													m_AlarmTagInfoList.RemoveAt(pos2);
													dbValue = 2;
												}
											}
											if (AlarmTagInfoStruct.bLimitHiFlag == 0 && AlarmTagInfoStruct.bLimitLoFlag == 1)		//低报
											{
												if (AlarmTagInfoStruct.dbLimiLo <  dbValue)
												{
													m_bSendAlarm = TRUE;
													m_AlarmTagInfoList.RemoveAt(pos2);
													dbValue = 2;
												}
											}
										}
										else if (AlarmTagInfoStruct.bAlarmTagType == 1)	//数字点
										{
											if (AlarmTagInfoStruct.bDigType == 0)	//关闭->打开
											{
												
												if ((fabs(dbValue - 0) < (1E-15)))
												{
													m_bSendAlarm = TRUE;
													m_AlarmTagInfoList.RemoveAt(pos2);
													dbValue = 2;
												}
											}
											if (AlarmTagInfoStruct.bDigType == 1)	//打开->关闭
											{
												if ((fabs(dbValue - 1) < (1E-15)))
												{
													m_bSendAlarm = TRUE;
													m_AlarmTagInfoList.RemoveAt(pos2);
													dbValue = 2;
												}
											}
										}
									}	
								}
							}

							
							OutputDebugString(_T("[hao]:	---------------------------9"));
							if(pPt->csPointType == _T("监控"))
							{
								MonitorJsonString(pS,pB,pFloor,pRoom,pPd,pPt,dbValue,tn);
								if(!Jroot_M[tn].isNull())
								{
									csDebugValue.Format(_T("[hao]:	监控   DB点名： %s"),csPV);
									OutputDebugString(csDebugValue);
									SendTextMessage(StrQueue,tn,m_session,m_producer);
								}
							}
							else 
							{	
								AlarmJsonString(pS,pB,pFloor,pRoom,pPd,pPt,dbValue,tn);
								if(!Jroot_A[tn].isNull() && m_bSendAlarm)
								{
									csDebugValue.Format(_T("[hao]:	告警   DB点名： %s"),csPV);
									OutputDebugString(csDebugValue);

									CString csSceneNameNoNum = pS->csName.Right(pS->csName.GetLength() - 6);
									std::string Alarm_name( CW2A( csSceneNameNoNum.GetString() ) ); 
									SendTextMessage("alarm_" + Alarm_name,tn,m_session,m_producer);
								}
							}
							
							Sleep(5);
							OutputDebugString(_T("[hao]:	---------------------------10"));
							
						}
						
						OutputDebugString(_T("[hao]:	1111111111111111"));
					}
					OutputDebugString(_T("[hao]:	22222222222222222"));
				}
				OutputDebugString(_T("[hao]:	33333333333333333"));
			}
			OutputDebugString(_T("[hao]:	44444444444444444"));
		}

		OutputDebugString(_T("[hao]:	55555555555555555"));
	}
	Sleep(m_nTime);	
	OutputDebugString(_T("[hao]: DoWork   -- end"));

}

UINT __cdecl ThreadPro(LPVOID args)
{
	CInterface3DDlg *pDlg = (CInterface3DDlg *)args;
	int tn;
	DWORD nID = GetCurrentThreadId();

	if(pDlg->m_threadNumber>0){
		for(int i = 0;i < pDlg->m_threadNumber; i++){
			if(pDlg->m_trPara.pThre[i]){
				if(pDlg->m_trPara.pThre[i]->m_nThreadID==nID){
					tn=i;
				}
			}else{
				break;
			}
		}
	}
	Scene_para *pS;
			int i=0;
			for(POSITION pos = pDlg->m_pSceneList.GetHeadPosition(); pos != NULL; i++)
			{
				pS = (Scene_para *)pDlg->m_pSceneList.GetNext(pos);
				if(tn==i)
				{
					break;
				}
			}

	CString csSceneNameNoNum = pS->csName.Right(pS->csName.GetLength() - 6);
	std::string Scene_name( CW2A( csSceneNameNoNum.GetString() ) ); 
	string StrQueue="project_" + Scene_name;
	Session  * m_session;	//DDian
	Destination *m_destination;
	MessageProducer * m_producer;

		if(pDlg->m_connection == NULL)		return 0;

		m_session = pDlg->m_connection->createSession(Session::AUTO_ACKNOWLEDGE);		//DDian
		m_destination = m_session->createQueue(StrQueue); 
		m_producer = m_session->createProducer(m_destination);  

		if(m_session)		OutputDebugString(_T("[hao]:		Connection::createSession"));
		if(m_destination)	OutputDebugString(_T("[hao]:		Session::createQueue"));
		if(m_producer)	OutputDebugString(_T("[hao]:		Session::createProducer"));

	while(pDlg->m_trPara.bIsExit)
	{
		pDlg->DoWork(pS,tn,StrQueue,m_session,m_producer);
		Sleep(10);
	}

	if(m_producer)
	{
		m_producer->close();
		delete m_producer;
	}
	if(m_destination)
	{
		delete m_destination;
	}

	if(m_session)	//DDian
	{
		m_session->close();
		delete m_session;
	}
	return 0;
}


void CInterface3DDlg::GetSetting(void)
{
	CIniFile ini;
	TCHAR tcPath[100];
	::GetModuleFileName(NULL,tcPath,100);
	CString csPath = tcPath;
	csPath = csPath.Left( csPath.ReverseFind('\\') + 1) + _T("config.ini");
	ini.SetFileName(csPath);
	m_csIP = ini.GetString(_T("SET"),_T("IP"));
	m_csPort = ini.GetString(_T("SET"),_T("PORT"));
	m_nTime = ini.GetInt(_T("SET"),_T("time"));
	if(m_nTime < 1)
	{
		m_nTime = 10;
	}
}
//db采集线程及推送
void CInterface3DDlg::ThreadBegin(void)
{
	GetSetting();
	NodeFromFile();
	UpDateItem();
	
	this->m_log.m_bFlagAmq = FALSE;
	this->m_log.Run();
	OutputDebugString(_T("[hao]:InitActiveMQ start"));
	this->InitActiveMQ();
	OutputDebugString(_T("[hao]:InitActiveMQ end"));
	this->m_log.m_bFlagAmq = TRUE;
	Scene_para *pS;
	int i=0;
	for(POSITION pos = m_pSceneList.GetHeadPosition(); pos != NULL; i++)
	{
		pS = (Scene_para *)m_pSceneList.GetNext(pos);
		if(pS->csName != VT_NULL )
		{
			m_trPara.pThre[i] = AfxBeginThread(ThreadPro,(LPVOID)this,THREAD_PRIORITY_NORMAL,0,CREATE_SUSPENDED,0);
//			m_trPara.pThre[i] = AfxBeginThread(ThreadPro,(LPVOID)this,0,0,0,0);
		}

	}
	m_threadNumber=i;

}

BEGIN_EVENTSINK_MAP(CInterface3DDlg, CDialogEx)
	ON_EVENT(CInterface3DDlg, IDC_DBCOMMOCXCTRLFC71, 1, CInterface3DDlg::StatusChangeDbcommocxctrlfc71, VTS_I4)
	ON_EVENT(CInterface3DDlg, IDC_DBCOMMOCXCTRLFC71, 3, CInterface3DDlg::AlarmChangeDbcommocxctrlfc71, VTS_BOOL VTS_I4 VTS_VARIANT)
END_EVENTSINK_MAP()


void CInterface3DDlg::StatusChangeDbcommocxctrlfc71(long Status)
{
	// TODO: 在此处添加消息处理程序代码
	switch(Status)
	{
	case 0:	//已经连接上
//		CmdLineHandle();

		if(m_threadNumber>0){
			for(int i = 0;i < m_threadNumber; i++){
				if(m_trPara.pThre[i]){
					m_trPara.pThre[i]->ResumeThread();
				}else{
					break;
				}
			}
		}

		UpdateList();

		break;
	case 1:
		AfxMessageBox(_T("LINK ERROR"));
		break;
	default:
		break;
	}
}


LRESULT CInterface3DDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	switch(message)
	{
	case WM_UPDATWLIST:
		m_clAllNode.AddString(m_csNodeName);
		break;
	case WM_CLOSE:
		if(m_trPara.bWorkMode == WORK_VIEW)
		{
			CreateTray();
			return 0;
		}
		break;
	default:
		break;
	}
	return CDialogEx::WindowProc(message, wParam, lParam);
}

//更新设备名
void CInterface3DDlg::UpdateList(void)
{
	BSTR bsPtr;
	CMarkup mark;
	if(m_dbCom.GetMarkupLayerStr(&bsPtr))
	{
		CString csStr = bsPtr;
		mark.SetDoc(csStr);
		while(mark.FindChildElem())
		{
			m_csNodeName = mark.GetChildAttrib(_T("Name")) + _T("_") + mark.GetChildAttrib(_T("NodeID"));
			SendMessage(WM_UPDATWLIST);
			Sleep(10);//休息一会
		}
		
	}
	//delete bsPtr;
}

void CInterface3DDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	NodeToFile();

}

//往comb控件中添加备选项
void CInterface3DDlg::CombAddString(emComb combAdd,CString csItemName)
{
	if (csItemName.IsEmpty())
	{
		return;
	}
	switch(combAdd)
	{
	case CombSceneName://场景
		{
			int nFindIndex = m_cbSceneName.FindStringExact(0, csItemName);
			if (nFindIndex < 0)
			{
				m_cbSceneName.AddString(csItemName);
			}
			break;
		}
	case CombBuildName://楼宇
		{
			int nFindIndex = m_cbBuildName.FindStringExact(0, csItemName);
			if (nFindIndex < 0)
			{
				m_cbBuildName.AddString(csItemName);
			}
			break;
		}
	case CombFloorName://楼层
		{
			int nFindIndex = m_cbFloorName.FindStringExact(0, csItemName);
			if (nFindIndex < 0)
			{
				m_cbFloorName.AddString(csItemName);
			}
			break;
		}
	case CombRoomName://房间
		{
			int nFindIndex = m_cbRoomName.FindStringExact(0, csItemName);
			if (nFindIndex < 0)
			{
				m_cbRoomName.AddString(csItemName);
			}
			break;
		}
	case CombDeviceName://设备名
		{
			int nFindIndex = m_cbDeviceName.FindStringExact(0, csItemName);
			if (nFindIndex < 0)
			{
				m_cbDeviceName.AddString(csItemName);
			}
			break;
		}
	case CombDeviceID://设备ID
		{
			int nFindIndex = m_cbDeviceID.FindStringExact(0, csItemName);
			if (nFindIndex < 0)
			{
				m_cbDeviceID.AddString(csItemName);
			}
			break;
		}
	case CombAlmCause://告警原因
		{
			int nFindIndex = m_cbAlaCause.FindStringExact(0, csItemName);
			if (nFindIndex < 0)
			{
				m_cbAlaCause.AddString(csItemName);
			}
			break;
		}
	case CombIODeviceName://IO设备名称
		{
			int nFindIndex = m_cbIODeviceName.FindStringExact(0, csItemName);
			if (nFindIndex < 0)
			{
				m_cbIODeviceName.AddString(csItemName);
			}
			break;
		}
	case CombSourceID://来源标识
		{
			int nFindIndex = m_cbSourceID.FindStringExact(0, csItemName);
			if (nFindIndex < 0)
			{
				m_cbSourceID.AddString(csItemName);
			}
			break;
		}
	case CombOriAlarmLevel://原始告警级别
		{
			int nFindIndex = m_cbOriAlarmLevel.FindStringExact(0, csItemName);
			if (nFindIndex < 0)
			{
				m_cbOriAlarmLevel.AddString(csItemName);
			}
			break;
		}
	case CombAlarmLevel://告警级别
		{
			int nFindIndex = m_cbAlarmLevel.FindStringExact(0, csItemName);
			if (nFindIndex < 0)
			{
				m_cbAlarmLevel.AddString(csItemName);
			}
			break;
		}
	case CombCompress://压缩标识
		{
			int nFindIndex = m_cbCompress.FindStringExact(0, csItemName);
			if (nFindIndex < 0)
			{
				m_cbCompress.AddString(csItemName);
			}
			break;
		}
	case CombIndexEx://指标实例
		{
			int nFindIndex = m_cbIndexEx.FindStringExact(0, csItemName);
			if (nFindIndex < 0)
			{
				m_cbIndexEx.AddString(csItemName);
			}
			break;
		}
	default:
		break;
	}
}

void CInterface3DDlg::UpDateTree(void)
{                                                   
	//HTREEITEM  hParrent;                                                                      
	HTREEITEM hRoot = m_TreeCtrl.GetRootItem();
	while(hRoot)//场景
	{
		CString csTmp = m_TreeCtrl.GetItemText(hRoot);
		CString csChangJing = csTmp;
		if(csTmp == m_csSceneName)
		{
			HTREEITEM hSonBuild = m_TreeCtrl.GetChildItem(hRoot);
			while(hSonBuild)//楼宇
			{
				csTmp = m_TreeCtrl.GetItemText(hSonBuild);
				if (csTmp == m_csBuildName)
				{
					HTREEITEM hSonFloor = m_TreeCtrl.GetChildItem(hSonBuild);
					while(hSonFloor)//楼层
					{
						csTmp = m_TreeCtrl.GetItemText(hSonFloor);
						if (csTmp == m_csFloorName)
						{
							HTREEITEM hSonRoom = m_TreeCtrl.GetChildItem(hSonFloor);
							while(hSonRoom)//房间
							{
								csTmp = m_TreeCtrl.GetItemText(hSonRoom);
								if (csTmp == m_csRoomName)
								{
									HTREEITEM hSon = m_TreeCtrl.GetChildItem(hSonRoom);
									while(hSon)//设备
									{
										csTmp = m_TreeCtrl.GetItemText(hSon);
										if(csTmp == m_csDeviceName)
										{
											HTREEITEM hGrandSon = m_TreeCtrl.GetChildItem(hSon);
											while(hGrandSon)//点
											{
												csTmp = m_TreeCtrl.GetItemText(hGrandSon);
												if(csTmp == m_csPointName)
												{
													CString csRe;
//													csRe.LoadString(IDS_STRING_NodeExist);
//													AfxMessageBox(csRe);
//													return;
													HTREEITEM hPointType = m_TreeCtrl.GetChildItem(hGrandSon);
													while(hPointType)//点类型
													{
														csTmp = m_TreeCtrl.GetItemText(hPointType);
														if(csTmp == m_csPointType)
														{
															CString csRe;
															csRe.LoadString(IDS_STRING_NodeExist);
															AfxMessageBox(csRe);
															return;
														}
														hPointType = m_TreeCtrl.GetNextSiblingItem(hPointType);
													}
												}
												hGrandSon = m_TreeCtrl.GetNextSiblingItem(hGrandSon);
											}
											hGrandSon = m_TreeCtrl.InsertItem(m_csPointName,hSon,TVI_LAST);
											m_TreeCtrl.SetItemData(hGrandSon,1);
											HTREEITEM hGrandSon1 = m_TreeCtrl.InsertItem(m_csPath,hGrandSon,TVI_LAST);
											m_TreeCtrl.SetItemData(hGrandSon1,0);
											hGrandSon1 = m_TreeCtrl.InsertItem(m_csPointType,hGrandSon,TVI_LAST);
											m_TreeCtrl.SetItemData(hGrandSon1,0);
											hGrandSon1 = m_TreeCtrl.InsertItem(m_csIndex,hGrandSon,TVI_LAST);
											m_TreeCtrl.SetItemData(hGrandSon1,0);
											hGrandSon1 = m_TreeCtrl.InsertItem(m_csTypeNum,hGrandSon,TVI_LAST);
											m_TreeCtrl.SetItemData(hGrandSon1,0);
											hGrandSon1 = m_TreeCtrl.InsertItem(m_csItemEnglish,hGrandSon,TVI_LAST);
											m_TreeCtrl.SetItemData(hGrandSon1,0);
											hGrandSon1 = m_TreeCtrl.InsertItem(m_csType,hGrandSon,TVI_LAST);
											m_TreeCtrl.SetItemData(hGrandSon1,0);
											hGrandSon1 = m_TreeCtrl.InsertItem(m_csContext,hGrandSon,TVI_LAST);
											m_TreeCtrl.SetItemData(hGrandSon1,0);
											if (m_csPointType == _T("告警"))
											{
												hGrandSon1 = m_TreeCtrl.InsertItem(m_csAlaCause,hGrandSon,TVI_LAST);
												m_TreeCtrl.SetItemData(hGrandSon1,0);
												CombAddString(CombAlmCause,m_csAlaCause);
												hGrandSon1 = m_TreeCtrl.InsertItem(m_csAlaColor,hGrandSon,TVI_LAST);
												m_TreeCtrl.SetItemData(hGrandSon1,3);
												hGrandSon1 = m_TreeCtrl.InsertItem(m_csAlaType,hGrandSon,TVI_LAST);
												m_TreeCtrl.SetItemData(hGrandSon1,0);
											}


											/****************** hjq *********************/
											hGrandSon1 = m_TreeCtrl.InsertItem(m_csIODeviceName,hGrandSon,TVI_LAST);	//IO设备名称
											m_TreeCtrl.SetItemData(hGrandSon1,0);
											CombAddString(CombIODeviceName,m_csIODeviceName);

											hGrandSon1 = m_TreeCtrl.InsertItem(m_csIndexEx,hGrandSon,TVI_LAST);			//指标实例
											m_TreeCtrl.SetItemData(hGrandSon1,0);
											CombAddString(CombIndexEx,m_csIndexEx);

											if (m_csPointType == _T("告警"))
											{
												hGrandSon1 = m_TreeCtrl.InsertItem(m_csSourceID,hGrandSon,TVI_LAST);	//来源标识
												m_TreeCtrl.SetItemData(hGrandSon1,0);
												CombAddString(CombSourceID,m_csSourceID);

												hGrandSon1 = m_TreeCtrl.InsertItem(m_csOriAlarmLevel,hGrandSon,TVI_LAST);//原始告警级别
												m_TreeCtrl.SetItemData(hGrandSon1,0);
												CombAddString(CombOriAlarmLevel,m_csOriAlarmLevel);

												hGrandSon1 = m_TreeCtrl.InsertItem(m_csAlarmLevel,hGrandSon,TVI_LAST);	//告警级别
												m_TreeCtrl.SetItemData(hGrandSon1,0);
												CombAddString(CombAlarmLevel,m_csAlarmLevel);

												hGrandSon1 = m_TreeCtrl.InsertItem(m_csCompress,hGrandSon,TVI_LAST);	//压缩标识
												m_TreeCtrl.SetItemData(hGrandSon1,0);
												CombAddString(CombCompress,m_csCompress);
											}
											return;
										}
										hSon = m_TreeCtrl.GetNextSiblingItem(hSon);
									}
									hSon = m_TreeCtrl.InsertItem(m_csDeviceName,hSonRoom,TVI_LAST);
									m_TreeCtrl.SetItemData(hSon,1);
									CombAddString(CombDeviceName,m_csDeviceName);
									HTREEITEM hGrandSon1 = m_TreeCtrl.InsertItem(m_csDeviceId,hSon,TVI_LAST);
									m_TreeCtrl.SetItemData(hGrandSon1,0);
									CombAddString(CombDeviceID,m_csDeviceId);
									HTREEITEM  hGrandSun = m_TreeCtrl.InsertItem(m_csPointName,hSon,TVI_LAST);
									m_TreeCtrl.SetItemData(hGrandSun,1);

									hGrandSon1 = m_TreeCtrl.InsertItem(m_csPath,hGrandSun,TVI_LAST);
									m_TreeCtrl.SetItemData(hGrandSon1,0);
									hGrandSon1 = m_TreeCtrl.InsertItem(m_csPointType,hGrandSun,TVI_LAST);
									m_TreeCtrl.SetItemData(hGrandSon1,0);
									hGrandSon1 = m_TreeCtrl.InsertItem(m_csIndex,hGrandSun,TVI_LAST);
									m_TreeCtrl.SetItemData(hGrandSon1,0);
									hGrandSon1 = m_TreeCtrl.InsertItem(m_csTypeNum,hGrandSun,TVI_LAST);
									m_TreeCtrl.SetItemData(hGrandSon1,0);
									hGrandSon1 = m_TreeCtrl.InsertItem(m_csItemEnglish,hGrandSun,TVI_LAST);
									m_TreeCtrl.SetItemData(hGrandSon1,0);
									hGrandSon1 = m_TreeCtrl.InsertItem(m_csType,hGrandSun,TVI_LAST);
									m_TreeCtrl.SetItemData(hGrandSon1,0);
									hGrandSon1 = m_TreeCtrl.InsertItem(m_csContext,hGrandSun,TVI_LAST);
									m_TreeCtrl.SetItemData(hGrandSon1,0);
									if (m_csPointType == _T("告警"))
									{
										hGrandSon1 = m_TreeCtrl.InsertItem(m_csAlaCause,hGrandSun,TVI_LAST);
										m_TreeCtrl.SetItemData(hGrandSon1,0);
										CombAddString(CombAlmCause,m_csAlaCause);
										hGrandSon1 = m_TreeCtrl.InsertItem(m_csAlaColor,hGrandSun,TVI_LAST);
										m_TreeCtrl.SetItemData(hGrandSon1,3);
										hGrandSon1 = m_TreeCtrl.InsertItem(m_csAlaType,hGrandSun,TVI_LAST);
										m_TreeCtrl.SetItemData(hGrandSon1,0);
									}

									/****************** hjq *********************/
									hGrandSon1 = m_TreeCtrl.InsertItem(m_csIODeviceName,hGrandSun,TVI_LAST);	//IO设备名称
									m_TreeCtrl.SetItemData(hGrandSon1,0);
									CombAddString(CombIODeviceName,m_csIODeviceName);

									hGrandSon1 = m_TreeCtrl.InsertItem(m_csIndexEx,hGrandSun,TVI_LAST);			//指标实例
									m_TreeCtrl.SetItemData(hGrandSon1,0);
									CombAddString(CombIndexEx,m_csIndexEx);

									if (m_csPointType == _T("告警"))
									{
										hGrandSon1 = m_TreeCtrl.InsertItem(m_csSourceID,hGrandSun,TVI_LAST);	//来源标识
										m_TreeCtrl.SetItemData(hGrandSon1,0);
										CombAddString(CombSourceID,m_csSourceID);

										hGrandSon1 = m_TreeCtrl.InsertItem(m_csOriAlarmLevel,hGrandSun,TVI_LAST);//原始告警级别
										m_TreeCtrl.SetItemData(hGrandSon1,0);
										CombAddString(CombOriAlarmLevel,m_csOriAlarmLevel);

										hGrandSon1 = m_TreeCtrl.InsertItem(m_csAlarmLevel,hGrandSun,TVI_LAST);	//告警级别
										m_TreeCtrl.SetItemData(hGrandSon1,0);
										CombAddString(CombAlarmLevel,m_csAlarmLevel);

										hGrandSon1 = m_TreeCtrl.InsertItem(m_csCompress,hGrandSun,TVI_LAST);	//压缩标识
										m_TreeCtrl.SetItemData(hGrandSon1,0);
										CombAddString(CombCompress,m_csCompress);
									}
									return;
								}
								hSonRoom = m_TreeCtrl.GetNextSiblingItem(hSonRoom);
							}
							hSonRoom = m_TreeCtrl.InsertItem(m_csRoomName,hSonFloor,TVI_LAST);
							m_TreeCtrl.SetItemData(hSonRoom,1);
							HTREEITEM hSon = m_TreeCtrl.InsertItem(m_csDeviceName,hSonRoom,TVI_LAST);
							m_TreeCtrl.SetItemData(hSon,1);
							CombAddString(CombDeviceName,m_csDeviceName);
							HTREEITEM hGrandSon1 = m_TreeCtrl.InsertItem(m_csDeviceId,hSon,TVI_LAST);
							m_TreeCtrl.SetItemData(hGrandSon1,0);
							CombAddString(CombDeviceID,m_csDeviceId);
							HTREEITEM  hGrandSun = m_TreeCtrl.InsertItem(m_csPointName,hSon,TVI_LAST);
							m_TreeCtrl.SetItemData(hGrandSun,1);

							//m_csChildId = csChangJing + m_csDeviceName + m_csPointName;
							//hGrandSon1 = m_TreeCtrl.InsertItem(m_csChildId,hGrandSun,TVI_LAST);					
							//m_TreeCtrl.SetItemData(hGrandSon1,0);

							hGrandSon1 = m_TreeCtrl.InsertItem(m_csPath,hGrandSun,TVI_LAST);
							m_TreeCtrl.SetItemData(hGrandSon1,0);
							hGrandSon1 = m_TreeCtrl.InsertItem(m_csPointType,hGrandSun,TVI_LAST);
							m_TreeCtrl.SetItemData(hGrandSon1,0);
							hGrandSon1 = m_TreeCtrl.InsertItem(m_csIndex,hGrandSun,TVI_LAST);
							m_TreeCtrl.SetItemData(hGrandSon1,0);
							hGrandSon1 = m_TreeCtrl.InsertItem(m_csTypeNum,hGrandSun,TVI_LAST);
							m_TreeCtrl.SetItemData(hGrandSon1,0);
							hGrandSon1 = m_TreeCtrl.InsertItem(m_csItemEnglish,hGrandSun,TVI_LAST);
							m_TreeCtrl.SetItemData(hGrandSon1,0);
							hGrandSon1 = m_TreeCtrl.InsertItem(m_csType,hGrandSun,TVI_LAST);
							m_TreeCtrl.SetItemData(hGrandSon1,0);
							//hGrandSon1 = m_TreeCtrl.InsertItem(m_csDataType,hGrandSun,TVI_LAST);
							//m_TreeCtrl.SetItemData(hGrandSon1,0);
							hGrandSon1 = m_TreeCtrl.InsertItem(m_csContext,hGrandSun,TVI_LAST);
							m_TreeCtrl.SetItemData(hGrandSon1,0);
							if (m_csPointType == _T("告警"))
							{
								hGrandSon1 = m_TreeCtrl.InsertItem(m_csAlaCause,hGrandSun,TVI_LAST);
								m_TreeCtrl.SetItemData(hGrandSon1,0);
								CombAddString(CombAlmCause,m_csAlaCause);
								hGrandSon1 = m_TreeCtrl.InsertItem(m_csAlaColor,hGrandSun,TVI_LAST);
								m_TreeCtrl.SetItemData(hGrandSon1,3);
								hGrandSon1 = m_TreeCtrl.InsertItem(m_csAlaType,hGrandSun,TVI_LAST);
								m_TreeCtrl.SetItemData(hGrandSon1,0);
							}

							/****************** hjq *********************/
							hGrandSon1 = m_TreeCtrl.InsertItem(m_csIODeviceName,hGrandSun,TVI_LAST);	//IO设备名称
							m_TreeCtrl.SetItemData(hGrandSon1,0);
							CombAddString(CombIODeviceName,m_csIODeviceName);

							hGrandSon1 = m_TreeCtrl.InsertItem(m_csIndexEx,hGrandSun,TVI_LAST);			//指标实例
							m_TreeCtrl.SetItemData(hGrandSon1,0);
							CombAddString(CombIndexEx,m_csIndexEx);

							if (m_csPointType == _T("告警"))
							{
								hGrandSon1 = m_TreeCtrl.InsertItem(m_csSourceID,hGrandSun,TVI_LAST);	//来源标识
								m_TreeCtrl.SetItemData(hGrandSon1,0);
								CombAddString(CombSourceID,m_csSourceID);

								hGrandSon1 = m_TreeCtrl.InsertItem(m_csOriAlarmLevel,hGrandSun,TVI_LAST);//原始告警级别
								m_TreeCtrl.SetItemData(hGrandSon1,0);
								CombAddString(CombOriAlarmLevel,m_csOriAlarmLevel);

								hGrandSon1 = m_TreeCtrl.InsertItem(m_csAlarmLevel,hGrandSun,TVI_LAST);	//告警级别
								m_TreeCtrl.SetItemData(hGrandSon1,0);
								CombAddString(CombAlarmLevel,m_csAlarmLevel);

								hGrandSon1 = m_TreeCtrl.InsertItem(m_csCompress,hGrandSun,TVI_LAST);	//压缩标识
								m_TreeCtrl.SetItemData(hGrandSon1,0);
								CombAddString(CombCompress,m_csCompress);
							}
							return;
						}
						hSonFloor = m_TreeCtrl.GetNextSiblingItem(hSonFloor);
					}
					hSonFloor = m_TreeCtrl.InsertItem(m_csFloorName,hSonBuild,TVI_LAST);
					m_TreeCtrl.SetItemData(hSonFloor,1);
					HTREEITEM hSonRoom = m_TreeCtrl.InsertItem(m_csRoomName,hSonFloor,TVI_LAST);
					m_TreeCtrl.SetItemData(hSonRoom,1);
					HTREEITEM hSon = m_TreeCtrl.InsertItem(m_csDeviceName,hSonRoom,TVI_LAST);
					m_TreeCtrl.SetItemData(hSon,1);
					CombAddString(CombDeviceName,m_csDeviceName);
					HTREEITEM hGrandSon1 = m_TreeCtrl.InsertItem(m_csDeviceId,hSon,TVI_LAST);
					m_TreeCtrl.SetItemData(hGrandSon1,0);
					CombAddString(CombDeviceID,m_csDeviceId);
					HTREEITEM  hGrandSun = m_TreeCtrl.InsertItem(m_csPointName,hSon,TVI_LAST);
					m_TreeCtrl.SetItemData(hGrandSun,1);

					//m_csChildId = csChangJing + m_csDeviceName + m_csPointName;
					//hGrandSon1 = m_TreeCtrl.InsertItem(m_csChildId,hGrandSun,TVI_LAST);					
					//m_TreeCtrl.SetItemData(hGrandSon1,0);

					hGrandSon1 = m_TreeCtrl.InsertItem(m_csPath,hGrandSun,TVI_LAST);
					m_TreeCtrl.SetItemData(hGrandSon1,0);
					hGrandSon1 = m_TreeCtrl.InsertItem(m_csPointType,hGrandSun,TVI_LAST);
					m_TreeCtrl.SetItemData(hGrandSon1,0);
					hGrandSon1 = m_TreeCtrl.InsertItem(m_csIndex,hGrandSun,TVI_LAST);
					m_TreeCtrl.SetItemData(hGrandSon1,0);
					hGrandSon1 = m_TreeCtrl.InsertItem(m_csTypeNum,hGrandSun,TVI_LAST);
					m_TreeCtrl.SetItemData(hGrandSon1,0);
					hGrandSon1 = m_TreeCtrl.InsertItem(m_csItemEnglish,hGrandSun,TVI_LAST);
					m_TreeCtrl.SetItemData(hGrandSon1,0);
					hGrandSon1 = m_TreeCtrl.InsertItem(m_csType,hGrandSun,TVI_LAST);
					m_TreeCtrl.SetItemData(hGrandSon1,0);
					//hGrandSon1 = m_TreeCtrl.InsertItem(m_csDataType,hGrandSun,TVI_LAST);
					//m_TreeCtrl.SetItemData(hGrandSon1,0);
					hGrandSon1 = m_TreeCtrl.InsertItem(m_csContext,hGrandSun,TVI_LAST);
					m_TreeCtrl.SetItemData(hGrandSon1,0);
					if (m_csPointType == _T("告警"))
					{
						hGrandSon1 = m_TreeCtrl.InsertItem(m_csAlaCause,hGrandSun,TVI_LAST);
						m_TreeCtrl.SetItemData(hGrandSon1,0);
						CombAddString(CombAlmCause,m_csAlaCause);
						hGrandSon1 = m_TreeCtrl.InsertItem(m_csAlaColor,hGrandSun,TVI_LAST);
						m_TreeCtrl.SetItemData(hGrandSon1,3);
						hGrandSon1 = m_TreeCtrl.InsertItem(m_csAlaType,hGrandSun,TVI_LAST);
						m_TreeCtrl.SetItemData(hGrandSon1,0);
					}

					/****************** hjq *********************/
					hGrandSon1 = m_TreeCtrl.InsertItem(m_csIODeviceName,hGrandSun,TVI_LAST);	//IO设备名称
					m_TreeCtrl.SetItemData(hGrandSon1,0);
					CombAddString(CombIODeviceName,m_csIODeviceName);

					hGrandSon1 = m_TreeCtrl.InsertItem(m_csIndexEx,hGrandSun,TVI_LAST);			//指标实例
					m_TreeCtrl.SetItemData(hGrandSon1,0);
					CombAddString(CombIndexEx,m_csIndexEx);

					if (m_csPointType == _T("告警"))
					{
						hGrandSon1 = m_TreeCtrl.InsertItem(m_csSourceID,hGrandSun,TVI_LAST);	//来源标识
						m_TreeCtrl.SetItemData(hGrandSon1,0);
						CombAddString(CombSourceID,m_csSourceID);

						hGrandSon1 = m_TreeCtrl.InsertItem(m_csOriAlarmLevel,hGrandSun,TVI_LAST);//原始告警级别
						m_TreeCtrl.SetItemData(hGrandSon1,0);
						CombAddString(CombOriAlarmLevel,m_csOriAlarmLevel);

						hGrandSon1 = m_TreeCtrl.InsertItem(m_csAlarmLevel,hGrandSun,TVI_LAST);	//告警级别
						m_TreeCtrl.SetItemData(hGrandSon1,0);
						CombAddString(CombAlarmLevel,m_csAlarmLevel);

						hGrandSon1 = m_TreeCtrl.InsertItem(m_csCompress,hGrandSun,TVI_LAST);	//压缩标识
						m_TreeCtrl.SetItemData(hGrandSon1,0);
						CombAddString(CombCompress,m_csCompress);
					}
					return;
				}
				hSonBuild = m_TreeCtrl.GetNextSiblingItem(hSonBuild);
			}
			hSonBuild = m_TreeCtrl.InsertItem(m_csBuildName,hRoot,TVI_LAST);
			m_TreeCtrl.SetItemData(hSonBuild,1);
			HTREEITEM hSonFloor = m_TreeCtrl.InsertItem(m_csFloorName,hSonBuild,TVI_LAST);
			m_TreeCtrl.SetItemData(hSonFloor,1);
			HTREEITEM hSonRoom = m_TreeCtrl.InsertItem(m_csRoomName,hSonFloor,TVI_LAST);
			m_TreeCtrl.SetItemData(hSonRoom,1);
			HTREEITEM hSon = m_TreeCtrl.InsertItem(m_csDeviceName,hSonRoom,TVI_LAST);
			m_TreeCtrl.SetItemData(hSon,1);
			CombAddString(CombDeviceName,m_csDeviceName);
			HTREEITEM hGrandSon1 = m_TreeCtrl.InsertItem(m_csDeviceId,hSon,TVI_LAST);
			m_TreeCtrl.SetItemData(hGrandSon1,0);
			CombAddString(CombDeviceID,m_csDeviceId);
			HTREEITEM  hGrandSun = m_TreeCtrl.InsertItem(m_csPointName,hSon,TVI_LAST);
			m_TreeCtrl.SetItemData(hGrandSun,1);

			//m_csChildId = csChangJing + m_csDeviceName + m_csPointName;
			//hGrandSon1 = m_TreeCtrl.InsertItem(m_csChildId,hGrandSun,TVI_LAST);					
			//m_TreeCtrl.SetItemData(hGrandSon1,0);

			hGrandSon1 = m_TreeCtrl.InsertItem(m_csPath,hGrandSun,TVI_LAST);
			m_TreeCtrl.SetItemData(hGrandSon1,0);
			hGrandSon1 = m_TreeCtrl.InsertItem(m_csPointType,hGrandSun,TVI_LAST);
			m_TreeCtrl.SetItemData(hGrandSon1,0);
			hGrandSon1 = m_TreeCtrl.InsertItem(m_csIndex,hGrandSun,TVI_LAST);
			m_TreeCtrl.SetItemData(hGrandSon1,0);
			hGrandSon1 = m_TreeCtrl.InsertItem(m_csTypeNum,hGrandSun,TVI_LAST);
			m_TreeCtrl.SetItemData(hGrandSon1,0);
			hGrandSon1 = m_TreeCtrl.InsertItem(m_csItemEnglish,hGrandSun,TVI_LAST);
			m_TreeCtrl.SetItemData(hGrandSon1,0);
			hGrandSon1 = m_TreeCtrl.InsertItem(m_csType,hGrandSun,TVI_LAST);
			m_TreeCtrl.SetItemData(hGrandSon1,0);
			//hGrandSon1 = m_TreeCtrl.InsertItem(m_csDataType,hGrandSun,TVI_LAST);
			//m_TreeCtrl.SetItemData(hGrandSon1,0);
			hGrandSon1 = m_TreeCtrl.InsertItem(m_csContext,hGrandSun,TVI_LAST);
			m_TreeCtrl.SetItemData(hGrandSon1,0);
			if (m_csPointType == _T("告警"))
			{
				hGrandSon1 = m_TreeCtrl.InsertItem(m_csAlaCause,hGrandSun,TVI_LAST);
				m_TreeCtrl.SetItemData(hGrandSon1,0);
				CombAddString(CombAlmCause,m_csAlaCause);
				hGrandSon1 = m_TreeCtrl.InsertItem(m_csAlaColor,hGrandSun,TVI_LAST);
				m_TreeCtrl.SetItemData(hGrandSon1,3);
				hGrandSon1 = m_TreeCtrl.InsertItem(m_csAlaType,hGrandSun,TVI_LAST);
				m_TreeCtrl.SetItemData(hGrandSon1,0);
			}

			/****************** hjq *********************/
			hGrandSon1 = m_TreeCtrl.InsertItem(m_csIODeviceName,hGrandSun,TVI_LAST);	//IO设备名称
			m_TreeCtrl.SetItemData(hGrandSon1,0);
			CombAddString(CombIODeviceName,m_csIODeviceName);

			hGrandSon1 = m_TreeCtrl.InsertItem(m_csIndexEx,hGrandSun,TVI_LAST);			//指标实例
			m_TreeCtrl.SetItemData(hGrandSon1,0);
			CombAddString(CombIndexEx,m_csIndexEx);

			if (m_csPointType == _T("告警"))
			{
				hGrandSon1 = m_TreeCtrl.InsertItem(m_csSourceID,hGrandSun,TVI_LAST);	//来源标识
				m_TreeCtrl.SetItemData(hGrandSon1,0);
				CombAddString(CombSourceID,m_csSourceID);

				hGrandSon1 = m_TreeCtrl.InsertItem(m_csOriAlarmLevel,hGrandSun,TVI_LAST);//原始告警级别
				m_TreeCtrl.SetItemData(hGrandSon1,0);
				CombAddString(CombOriAlarmLevel,m_csOriAlarmLevel);

				hGrandSon1 = m_TreeCtrl.InsertItem(m_csAlarmLevel,hGrandSun,TVI_LAST);	//告警级别
				m_TreeCtrl.SetItemData(hGrandSon1,0);
				CombAddString(CombAlarmLevel,m_csAlarmLevel);

				hGrandSon1 = m_TreeCtrl.InsertItem(m_csCompress,hGrandSun,TVI_LAST);	//压缩标识
				m_TreeCtrl.SetItemData(hGrandSon1,0);
				CombAddString(CombCompress,m_csCompress);
			}
			return;
		}
		hRoot = m_TreeCtrl.GetNextSiblingItem(hRoot);
	}
	//场景
	HTREEITEM  hSon = m_TreeCtrl.InsertItem(m_csSceneName,0,TVI_LAST);
	m_TreeCtrl.SetItemData(hSon,1);
	CombAddString(CombSceneName,m_csSceneName);
	//楼宇
	hSon = m_TreeCtrl.InsertItem(m_csBuildName,hSon,TVI_LAST);
	m_TreeCtrl.SetItemData(hSon,1);
	CombAddString(CombBuildName,m_csBuildName);
	//楼层
	hSon = m_TreeCtrl.InsertItem(m_csFloorName,hSon,TVI_LAST);
	m_TreeCtrl.SetItemData(hSon,1);
	CombAddString(CombFloorName,m_csFloorName);
	//房间
	hSon = m_TreeCtrl.InsertItem(m_csRoomName,hSon,TVI_LAST);
	m_TreeCtrl.SetItemData(hSon,1);
	CombAddString(CombRoomName,m_csRoomName);
	//设备
	hSon = m_TreeCtrl.InsertItem(m_csDeviceName,hSon,TVI_LAST);
	m_TreeCtrl.SetItemData(hSon,1);
	CombAddString(CombDeviceName,m_csDeviceName);
	HTREEITEM hGrandSon1 = m_TreeCtrl.InsertItem(m_csDeviceId,hSon,TVI_LAST);
	m_TreeCtrl.SetItemData(hGrandSon1,0);
	CombAddString(CombDeviceID,m_csDeviceId);
	HTREEITEM  hGrandSun = m_TreeCtrl.InsertItem(m_csPointName,hSon,TVI_LAST);
	m_TreeCtrl.SetItemData(hGrandSun,1);

	//m_csChildId = m_csSceneName + m_csDeviceName + m_csPointName;
	//hGrandSon1 = m_TreeCtrl.InsertItem(m_csChildId,hGrandSun,TVI_LAST);					
	//m_TreeCtrl.SetItemData(hGrandSon1,0);

	hGrandSon1 = m_TreeCtrl.InsertItem(m_csPath,hGrandSun,TVI_LAST);
	m_TreeCtrl.SetItemData(hGrandSon1,0);
	hGrandSon1 = m_TreeCtrl.InsertItem(m_csPointType,hGrandSun,TVI_LAST);
	m_TreeCtrl.SetItemData(hGrandSon1,0);
	hGrandSon1 = m_TreeCtrl.InsertItem(m_csIndex,hGrandSun,TVI_LAST);
	m_TreeCtrl.SetItemData(hGrandSon1,0);
	hGrandSon1 = m_TreeCtrl.InsertItem(m_csTypeNum,hGrandSun,TVI_LAST);
	m_TreeCtrl.SetItemData(hGrandSon1,0);
	hGrandSon1 = m_TreeCtrl.InsertItem(m_csItemEnglish,hGrandSun,TVI_LAST);
	m_TreeCtrl.SetItemData(hGrandSon1,0);
	hGrandSon1 = m_TreeCtrl.InsertItem(m_csType,hGrandSun,TVI_LAST);
	m_TreeCtrl.SetItemData(hGrandSon1,0);
	//hGrandSon1 = m_TreeCtrl.InsertItem(m_csDataType,hGrandSun,TVI_LAST);
	//m_TreeCtrl.SetItemData(hGrandSon1,0);
	hGrandSon1 = m_TreeCtrl.InsertItem(m_csContext,hGrandSun,TVI_LAST);
	m_TreeCtrl.SetItemData(hGrandSon1,0);
	if (m_csPointType == _T("告警"))
	{
		hGrandSon1 = m_TreeCtrl.InsertItem(m_csAlaCause,hGrandSun,TVI_LAST);
		m_TreeCtrl.SetItemData(hGrandSon1,0);
		CombAddString(CombAlmCause,m_csAlaCause);
		hGrandSon1 = m_TreeCtrl.InsertItem(m_csAlaColor,hGrandSun,TVI_LAST);
		m_TreeCtrl.SetItemData(hGrandSon1,3);
		hGrandSon1 = m_TreeCtrl.InsertItem(m_csAlaType,hGrandSun,TVI_LAST);
		m_TreeCtrl.SetItemData(hGrandSon1,0);
	}

	/****************** hjq *********************/
	hGrandSon1 = m_TreeCtrl.InsertItem(m_csIODeviceName,hGrandSun,TVI_LAST);	//IO设备名称
	m_TreeCtrl.SetItemData(hGrandSon1,0);
	CombAddString(CombIODeviceName,m_csIODeviceName);

	hGrandSon1 = m_TreeCtrl.InsertItem(m_csIndexEx,hGrandSun,TVI_LAST);			//指标实例
	m_TreeCtrl.SetItemData(hGrandSon1,0);
	CombAddString(CombIndexEx,m_csIndexEx);

	if (m_csPointType == _T("告警"))
	{
		hGrandSon1 = m_TreeCtrl.InsertItem(m_csSourceID,hGrandSun,TVI_LAST);	//来源标识
		m_TreeCtrl.SetItemData(hGrandSon1,0);
		CombAddString(CombSourceID,m_csSourceID);

		hGrandSon1 = m_TreeCtrl.InsertItem(m_csOriAlarmLevel,hGrandSun,TVI_LAST);//原始告警级别
		m_TreeCtrl.SetItemData(hGrandSon1,0);
		CombAddString(CombOriAlarmLevel,m_csOriAlarmLevel);

		hGrandSon1 = m_TreeCtrl.InsertItem(m_csAlarmLevel,hGrandSun,TVI_LAST);	//告警级别
		m_TreeCtrl.SetItemData(hGrandSon1,0);
		CombAddString(CombAlarmLevel,m_csAlarmLevel);

		hGrandSon1 = m_TreeCtrl.InsertItem(m_csCompress,hGrandSun,TVI_LAST);	//压缩标识
		m_TreeCtrl.SetItemData(hGrandSon1,0);
		CombAddString(CombCompress,m_csCompress);
	}
	
}
//文件保存
void CInterface3DDlg::NodeToFile(void)
{
	CMarkup xml;

	UpdateData(TRUE);
	if(m_csDeviceName.IsEmpty() || m_csSceneName.IsEmpty() || m_csDeviceId.IsEmpty() ||
		m_csPointName.IsEmpty()||m_csType.IsEmpty())
	{
		CString csRes;
		csRes.LoadString(IDS_STRING_EMPTY);
		AfxMessageBox(csRes);
		return;
	}
	if(m_csContext.IsEmpty())
	{
		m_csContext = _T("无");
	}
	m_csChildId = m_csSceneName + m_csDeviceName + m_csDeviceId + m_csPointName;
	UpDateTree();
	
	TCHAR tcPath[100];
	::GetModuleFileName(NULL,tcPath,100);
	CString csPath = tcPath;
	csPath = csPath.Left( csPath.ReverseFind('\\')+1) + _T("data.xml");

	CString csSceneNameNoNum = _T("SCENE_");
	csSceneNameNoNum += m_csSceneName;
	CString csFloorNameNoNum = _T("FLOOR_");
	csFloorNameNoNum += m_csFloorName;
	if(GetFileAttributes(csPath) == 0xffffffff) //文件不存在时  
	{  
		xml.SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n"));
		xml.AddElem(_T("Root"));
		xml.AddChildElem(csSceneNameNoNum);
		xml.IntoElem();
		xml.AddChildElem(m_csBuildName);
		xml.IntoElem();
		xml.AddChildElem(csFloorNameNoNum);
		xml.IntoElem();
		xml.AddChildElem(m_csRoomName);
		xml.IntoElem();
		xml.AddChildElem(m_csDeviceName);
		xml.IntoElem();
		xml.AddChildElem(_T("id"),m_csDeviceId);
		xml.AddChildElem(m_csPointName);
		xml.IntoElem();		
		//xml.AddChildElem(_T("ChildId"),m_csChildId);
		xml.AddChildElem(_T("path"),m_csPath);
		xml.AddChildElem(_T("ptype"),m_csPointType);
		xml.AddChildElem(_T("bigtype"),m_csIndex);
		xml.AddChildElem(_T("bigtypenum"),m_csTypeNum);
		xml.AddChildElem(_T("bigtypeng"),m_csItemEnglish);
		xml.AddChildElem(_T("type"),m_csType);
		//xml.AddChildElem(_T("data_type"),m_csDataType);
		xml.AddChildElem(_T("context"),m_csContext);
		if (m_csPointType == _T("告警"))
		{
			xml.AddChildElem(_T("alacause"),m_csAlaCause);
			xml.AddChildElem(_T("alacolor"),m_csAlaColor);
			xml.AddChildElem(_T("alatype"),m_csAlaType);
		}

		/****************** hjq *********************/	
		xml.AddChildElem(_T("SourceCIName"),m_csIODeviceName);			//IO设备名称
		xml.AddChildElem(_T("instance"),m_csIndexEx);					//指标实例
		if (m_csPointType == _T("告警"))
		{
			xml.AddChildElem(_T("SourceID"),m_csSourceID);				//来源标识
			xml.AddChildElem(_T("SourceSeverity"),m_csOriAlarmLevel);	//原始告警级别
			xml.AddChildElem(_T("Severity"),m_csAlarmLevel);			//告警级别
			xml.AddChildElem(_T("SourceIdentifier"),m_csCompress);		//压缩标识
		}
		/****************** hjq end *********************/
		xml.OutOfElem();
		xml.OutOfElem();
		xml.OutOfElem();
		xml.OutOfElem();
		xml.OutOfElem();
		xml.OutOfElem();
		xml.Save(csPath);
	} 
	else
	{
		BOOL bLoadXml =xml.Load(csPath); //加载xml文件  
		if (bLoadXml) 
		{
			xml.ResetMainPos();	//将指针定义到第一个顶级标签的上一个位置<文本>  
			xml.FindElem();		//将将指针定义到第一个顶级标签 

			if(xml.FindChildElem(csSceneNameNoNum))//场景
			{
				xml.IntoElem();
				if (xml.FindChildElem(m_csBuildName))//楼宇
				{
					xml.IntoElem();
					if (xml.FindChildElem(csFloorNameNoNum))//楼层
					{
						xml.IntoElem();
						if (xml.FindChildElem(m_csRoomName))//房间
						{
							xml.IntoElem();
							if(xml.FindChildElem(m_csDeviceName))
							{
								xml.IntoElem();
								if (!xml.FindChildElem(m_csPointName))//点不存在时才保存
								{
									xml.AddChildElem(m_csPointName);
									xml.IntoElem();	
									xml.AddChildElem(_T("path"),m_csPath);
									xml.AddChildElem(_T("ptype"),m_csPointType);
									xml.AddChildElem(_T("bigtype"),m_csIndex);
									xml.AddChildElem(_T("bigtypenum"),m_csTypeNum);
									xml.AddChildElem(_T("bigtypeng"),m_csItemEnglish);
									xml.AddChildElem(_T("type"),m_csType);
									xml.AddChildElem(_T("context"),m_csContext);
									if (m_csPointType == _T("告警"))
									{
										xml.AddChildElem(_T("alacause"),m_csAlaCause);
										xml.AddChildElem(_T("alacolor"),m_csAlaColor);
										xml.AddChildElem(_T("alatype"),m_csAlaType);
									}
									/****************** hjq *********************/	
									xml.AddChildElem(_T("SourceCIName"),m_csIODeviceName);			//IO设备名称
									xml.AddChildElem(_T("instance"),m_csIndexEx);					//指标实例
									if (m_csPointType == _T("告警"))
									{
										xml.AddChildElem(_T("SourceID"),m_csSourceID);				//来源标识
										xml.AddChildElem(_T("SourceSeverity"),m_csOriAlarmLevel);	//原始告警级别
										xml.AddChildElem(_T("Severity"),m_csAlarmLevel);			//告警级别
										xml.AddChildElem(_T("SourceIdentifier"),m_csCompress);		//压缩标识
									}
									/****************** hjq end *********************/
								}
/*								else{
									xml.AddChildElem(m_csPointName+"_2");
									xml.IntoElem();	
									xml.AddChildElem(_T("path"),m_csPath);
									xml.AddChildElem(_T("ptype"),m_csPointType);
									xml.AddChildElem(_T("bigtype"),m_csIndex);
									xml.AddChildElem(_T("bigtypenum"),m_csTypeNum);
									xml.AddChildElem(_T("bigtypeng"),m_csItemEnglish);
									xml.AddChildElem(_T("type"),m_csType);
									xml.AddChildElem(_T("context"),m_csContext);
									if (m_csPointType == _T("告警"))
									{
										xml.AddChildElem(_T("alacause"),m_csAlaCause);
										xml.AddChildElem(_T("alacolor"),m_csAlaColor);
										xml.AddChildElem(_T("alatype"),m_csAlaType);
									}

									xml.AddChildElem(_T("SourceCIName"),m_csIODeviceName);			//IO设备名称
									xml.AddChildElem(_T("instance"),m_csIndexEx);					//指标实例
									if (m_csPointType == _T("告警"))
									{
										xml.AddChildElem(_T("SourceID"),m_csSourceID);				//来源标识
										xml.AddChildElem(_T("SourceSeverity"),m_csOriAlarmLevel);	//原始告警级别
										xml.AddChildElem(_T("Severity"),m_csAlarmLevel);			//告警级别
										xml.AddChildElem(_T("SourceIdentifier"),m_csCompress);		//压缩标识
									}

								}
*/
								xml.OutOfElem();
								xml.OutOfElem();
							}
							else
							{
								//xml.IntoElem();
								xml.AddChildElem(m_csDeviceName);
								xml.IntoElem();
								xml.AddChildElem(_T("id"),m_csDeviceId);
								xml.AddChildElem(m_csPointName);
								xml.IntoElem();	
								xml.AddChildElem(_T("path"),m_csPath);
								xml.AddChildElem(_T("ptype"),m_csPointType);
								xml.AddChildElem(_T("bigtype"),m_csIndex);
								xml.AddChildElem(_T("bigtypenum"),m_csTypeNum);
								xml.AddChildElem(_T("bigtypeng"),m_csItemEnglish);
								xml.AddChildElem(_T("type"),m_csType);
								//xml.AddChildElem(_T("data_type"),m_csDataType);
								xml.AddChildElem(_T("context"),m_csContext);
								if (m_csPointType == _T("告警"))
								{
									xml.AddChildElem(_T("alacause"),m_csAlaCause);
									xml.AddChildElem(_T("alacolor"),m_csAlaColor);
									xml.AddChildElem(_T("alatype"),m_csAlaType);
								}
								/****************** hjq *********************/	
								xml.AddChildElem(_T("SourceCIName"),m_csIODeviceName);			//IO设备名称
								xml.AddChildElem(_T("instance"),m_csIndexEx);					//指标实例
								if (m_csPointType == _T("告警"))
								{
									xml.AddChildElem(_T("SourceID"),m_csSourceID);				//来源标识
									xml.AddChildElem(_T("SourceSeverity"),m_csOriAlarmLevel);	//原始告警级别
									xml.AddChildElem(_T("Severity"),m_csAlarmLevel);			//告警级别
									xml.AddChildElem(_T("SourceIdentifier"),m_csCompress);		//压缩标识
								}
								/****************** hjq end *********************/
								xml.OutOfElem();
								xml.OutOfElem();
								//xml.OutOfElem();
							}
							xml.OutOfElem();
						} 
						else
						{
							xml.AddChildElem(m_csRoomName);
							xml.IntoElem();
							xml.AddChildElem(m_csDeviceName);
							xml.IntoElem();
							xml.AddChildElem(_T("id"),m_csDeviceId);
							xml.AddChildElem(m_csPointName);
							xml.IntoElem();	
							xml.AddChildElem(_T("path"),m_csPath);
							xml.AddChildElem(_T("ptype"),m_csPointType);
							xml.AddChildElem(_T("bigtype"),m_csIndex);
							xml.AddChildElem(_T("bigtypenum"),m_csTypeNum);
							xml.AddChildElem(_T("bigtypeng"),m_csItemEnglish);
							xml.AddChildElem(_T("type"),m_csType);
							//xml.AddChildElem(_T("data_type"),m_csDataType);
							xml.AddChildElem(_T("context"),m_csContext);
							if (m_csPointType == _T("告警"))
							{
								xml.AddChildElem(_T("alacause"),m_csAlaCause);
								xml.AddChildElem(_T("alacolor"),m_csAlaColor);
								xml.AddChildElem(_T("alatype"),m_csAlaType);
							}
							/****************** hjq *********************/	
							xml.AddChildElem(_T("SourceCIName"),m_csIODeviceName);			//IO设备名称
							xml.AddChildElem(_T("instance"),m_csIndexEx);					//指标实例
							if (m_csPointType == _T("告警"))
							{
								xml.AddChildElem(_T("SourceID"),m_csSourceID);				//来源标识
								xml.AddChildElem(_T("SourceSeverity"),m_csOriAlarmLevel);	//原始告警级别
								xml.AddChildElem(_T("Severity"),m_csAlarmLevel);			//告警级别
								xml.AddChildElem(_T("SourceIdentifier"),m_csCompress);		//压缩标识
							}
							/****************** hjq end *********************/
							xml.OutOfElem();
							xml.OutOfElem();
							xml.OutOfElem();
						}
						xml.OutOfElem();
					} 
					else
					{
						xml.AddChildElem(csFloorNameNoNum);
						xml.IntoElem();
						xml.AddChildElem(m_csRoomName);
						xml.IntoElem();
						xml.AddChildElem(m_csDeviceName);
						xml.IntoElem();
						xml.AddChildElem(_T("id"),m_csDeviceId);
						xml.AddChildElem(m_csPointName);
						xml.IntoElem();	
						xml.AddChildElem(_T("path"),m_csPath);
						xml.AddChildElem(_T("ptype"),m_csPointType);
						xml.AddChildElem(_T("bigtype"),m_csIndex);
						xml.AddChildElem(_T("bigtypenum"),m_csTypeNum);
						xml.AddChildElem(_T("bigtypeng"),m_csItemEnglish);
						xml.AddChildElem(_T("type"),m_csType);
						//xml.AddChildElem(_T("data_type"),m_csDataType);
						xml.AddChildElem(_T("context"),m_csContext);
						if (m_csPointType == _T("告警"))
						{
							xml.AddChildElem(_T("alacause"),m_csAlaCause);
							xml.AddChildElem(_T("alacolor"),m_csAlaColor);
							xml.AddChildElem(_T("alatype"),m_csAlaType);
						}
						/****************** hjq *********************/	
						xml.AddChildElem(_T("SourceCIName"),m_csIODeviceName);			//IO设备名称
						xml.AddChildElem(_T("instance"),m_csIndexEx);					//指标实例
						if (m_csPointType == _T("告警"))
						{
							xml.AddChildElem(_T("SourceID"),m_csSourceID);				//来源标识
							xml.AddChildElem(_T("SourceSeverity"),m_csOriAlarmLevel);	//原始告警级别
							xml.AddChildElem(_T("Severity"),m_csAlarmLevel);			//告警级别
							xml.AddChildElem(_T("SourceIdentifier"),m_csCompress);		//压缩标识
						}
						/****************** hjq end *********************/
						xml.OutOfElem();
						xml.OutOfElem();
						xml.OutOfElem();
						xml.OutOfElem();
					}
					xml.OutOfElem();
				} 
				else
				{
					xml.AddChildElem(m_csBuildName);
					xml.IntoElem();
					xml.AddChildElem(csFloorNameNoNum);
					xml.IntoElem();
					xml.AddChildElem(m_csRoomName);
					xml.IntoElem();
					xml.AddChildElem(m_csDeviceName);
					xml.IntoElem();
					xml.AddChildElem(_T("id"),m_csDeviceId);
					xml.AddChildElem(m_csPointName);
					xml.IntoElem();	
					xml.AddChildElem(_T("path"),m_csPath);
					xml.AddChildElem(_T("ptype"),m_csPointType);
					xml.AddChildElem(_T("bigtype"),m_csIndex);
					xml.AddChildElem(_T("bigtypenum"),m_csTypeNum);
					xml.AddChildElem(_T("bigtypeng"),m_csItemEnglish);
					xml.AddChildElem(_T("type"),m_csType);
					//xml.AddChildElem(_T("data_type"),m_csDataType);
					xml.AddChildElem(_T("context"),m_csContext);
					if (m_csPointType == _T("告警"))
					{
						xml.AddChildElem(_T("alacause"),m_csAlaCause);
						xml.AddChildElem(_T("alacolor"),m_csAlaColor);
						xml.AddChildElem(_T("alatype"),m_csAlaType);
					}
					/****************** hjq *********************/	
					xml.AddChildElem(_T("SourceCIName"),m_csIODeviceName);			//IO设备名称
					xml.AddChildElem(_T("instance"),m_csIndexEx);					//指标实例
					if (m_csPointType == _T("告警"))
					{
						xml.AddChildElem(_T("SourceID"),m_csSourceID);				//来源标识
						xml.AddChildElem(_T("SourceSeverity"),m_csOriAlarmLevel);	//原始告警级别
						xml.AddChildElem(_T("Severity"),m_csAlarmLevel);			//告警级别
						xml.AddChildElem(_T("SourceIdentifier"),m_csCompress);		//压缩标识
					}
					/****************** hjq end *********************/
					xml.OutOfElem();
					xml.OutOfElem();
					xml.OutOfElem();
					xml.OutOfElem();
					xml.OutOfElem();
				}
				xml.OutOfElem();
				//xml.Save(csPath);
			}
			else
			{
				xml.AddChildElem(csSceneNameNoNum);
				xml.IntoElem();
				xml.AddChildElem(m_csBuildName);
				xml.IntoElem();
				xml.AddChildElem(csFloorNameNoNum);
				xml.IntoElem();
				xml.AddChildElem(m_csRoomName);
				xml.IntoElem();
				xml.AddChildElem(m_csDeviceName);
				xml.IntoElem();
				xml.AddChildElem(_T("id"),m_csDeviceId);
				xml.AddChildElem(m_csPointName);
				xml.IntoElem();
				xml.AddChildElem(_T("path"),m_csPath);
				xml.AddChildElem(_T("ptype"),m_csPointType);
				xml.AddChildElem(_T("bigtype"),m_csIndex);
				xml.AddChildElem(_T("bigtypenum"),m_csTypeNum);
				xml.AddChildElem(_T("bigtypeng"),m_csItemEnglish);
				xml.AddChildElem(_T("type"),m_csType);
				//xml.AddChildElem(_T("data_type"),m_csDataType);
				xml.AddChildElem(_T("context"),m_csContext);
				if (m_csPointType == _T("告警"))
				{
					xml.AddChildElem(_T("alacause"),m_csAlaCause);
					xml.AddChildElem(_T("alacolor"),m_csAlaColor);
					xml.AddChildElem(_T("alatype"),m_csAlaType);
				}
				/****************** hjq *********************/	
				xml.AddChildElem(_T("SourceCIName"),m_csIODeviceName);			//IO设备名称
				xml.AddChildElem(_T("instance"),m_csIndexEx);					//指标实例
				if (m_csPointType == _T("告警"))
				{
					xml.AddChildElem(_T("SourceID"),m_csSourceID);				//来源标识
					xml.AddChildElem(_T("SourceSeverity"),m_csOriAlarmLevel);	//原始告警级别
					xml.AddChildElem(_T("Severity"),m_csAlarmLevel);			//告警级别
					xml.AddChildElem(_T("SourceIdentifier"),m_csCompress);		//压缩标识
				}
				/****************** hjq end *********************/
				xml.OutOfElem();
				xml.OutOfElem();
				xml.OutOfElem();
				xml.OutOfElem();
				xml.OutOfElem();
				xml.OutOfElem();
				//xml.Save(csPath);
			}
		}
		xml.Save(csPath);
	}
	
}


//文件解析
void CInterface3DDlg::NodeFromFile(void)
{
	CMarkup xml;
	BOOL bLoadXml = FALSE; 
	TCHAR tcPath[100];
	::GetModuleFileName(NULL,tcPath,100);
	CString csPath = tcPath;
	csPath = csPath.Left( csPath.ReverseFind('\\')+1) + _T("data.xml");
	bLoadXml = xml.Load(csPath); //加载xml文件  

	CString csTmp;
	csTmp.Format(_T("[hao]: %s"),csPath);
	OutputDebugString(csTmp);

	if (bLoadXml) 
	{
		xml.ResetMainPos();//将指针定义到第一个顶级标签的上一个位置<文本>  
		xml.FindElem();//将将指针定义到第一个顶级标签 
		
		while(xml.FindChildElem())//场景
		{
			Scene_para *pScene = new  Scene_para;
			pScene->csName = xml.GetChildTagName();
			CString csSceneNameNoNum = pScene->csName.Right(pScene->csName.GetLength() - 6);
			HTREEITEM hParrent = m_TreeCtrl.InsertItem(csSceneNameNoNum,TVI_ROOT);	
			m_TreeCtrl.SetItemData(hParrent,1);
			CombAddString(CombSceneName,csSceneNameNoNum);
			xml.IntoElem();
			while(xml.FindChildElem())//楼宇循环
			{
				Build_para *pBuild = new Build_para;
				pBuild->csName = xml.GetChildTagName();
				HTREEITEM  hSunBuild = m_TreeCtrl.InsertItem(pBuild->csName,hParrent);
				m_TreeCtrl.SetItemData(hSunBuild,1);
				CombAddString(CombBuildName,pBuild->csName);
				xml.IntoElem();
				while(xml.FindChildElem())//楼层循环
				{
					Floor_para *pFloor = new Floor_para;
					pFloor->csName = xml.GetChildTagName();
					CString csFloorNameNoNum = pFloor->csName.Right(pFloor->csName.GetLength() - 6);
					HTREEITEM  hSunFloor = m_TreeCtrl.InsertItem(csFloorNameNoNum,hSunBuild);
					m_TreeCtrl.SetItemData(hSunFloor,1);
					CombAddString(CombFloorName,csFloorNameNoNum);
					xml.IntoElem();
					while(xml.FindChildElem())//房间循环
					{
						Room_para *pRoom = new Room_para;
						pRoom->csName = xml.GetChildTagName();
						HTREEITEM  hSunRoom = m_TreeCtrl.InsertItem(pRoom->csName,hSunFloor);
						m_TreeCtrl.SetItemData(hSunRoom,1);
						CombAddString(CombRoomName,pRoom->csName);
						xml.IntoElem();
						while(xml.FindChildElem())//设备循环
						{
							Device *pDevice = new Device;
							pDevice->csName = xml.GetChildTagName();
							HTREEITEM  hSun = m_TreeCtrl.InsertItem(pDevice->csName,hSunRoom);
							m_TreeCtrl.SetItemData(hSun,1);
							CombAddString(CombDeviceName,pDevice->csName);
							xml.IntoElem();
							while(xml.FindChildElem())//
							{
								CString csTmp = xml.GetChildTagName();
								if(csTmp == _T("id"))
								{
									pDevice->csID = xml.GetChildData();
									HTREEITEM  hGrandSon = m_TreeCtrl.InsertItem(pDevice->csID,hSun);
									m_TreeCtrl.SetItemData(hGrandSon,0);
									CombAddString(CombDeviceID,pDevice->csID);
								}
								else
								{
									Point_DB *pPoint = new Point_DB;
									pPoint->nState = 0;//由于告警状态只有 0 和 1 ,次数设置一个初始值
									pPoint->csName = xml.GetChildTagName();
									HTREEITEM hGrandSun = m_TreeCtrl.InsertItem(pPoint->csName,hSun);
									m_TreeCtrl.SetItemData(hGrandSun,1);
									xml.IntoElem();
									while(xml.FindChildElem())
									{
										csTmp = xml.GetChildTagName();
										if(csTmp == _T("type"))
										{
											pPoint->csType = xml.GetChildData();
											HTREEITEM hGrandSon1 = m_TreeCtrl.InsertItem(pPoint->csType,hGrandSun);
											m_TreeCtrl.SetItemData(hGrandSon1,0);
										}
										else if(csTmp == _T("bigtype"))
										{
											pPoint->csBigType = xml.GetChildData();
											HTREEITEM hGrandSon1 = m_TreeCtrl.InsertItem(pPoint->csBigType,hGrandSun);
											m_TreeCtrl.SetItemData(hGrandSon1,0);
										}
										else if(csTmp == _T("bigtypenum"))
										{
											pPoint->csBigTypeNum = xml.GetChildData();
											HTREEITEM hGrandSon1 = m_TreeCtrl.InsertItem(pPoint->csBigTypeNum,hGrandSun);
											m_TreeCtrl.SetItemData(hGrandSon1,0);
										}
										else if(csTmp == _T("bigtypeng"))
										{
											pPoint->csBigTypeEng = xml.GetChildData();
											HTREEITEM hGrandSon1 = m_TreeCtrl.InsertItem(pPoint->csBigTypeEng,hGrandSun);
											m_TreeCtrl.SetItemData(hGrandSon1,0);
										}
										else if(csTmp == _T("path"))
										{
											pPoint->csPath = xml.GetChildData();
											HTREEITEM hGrandSon1 = m_TreeCtrl.InsertItem(pPoint->csPath,hGrandSun);
											m_TreeCtrl.SetItemData(hGrandSon1,0);
										}
										else if(csTmp == _T("ptype"))
										{
											//pPoint->csChildId = pScene->csName + pDevice->csName + pDevice->csID + pPoint->csName;
											//HTREEITEM hGrandSon1 = m_TreeCtrl.InsertItem(pPoint->csChildId,hGrandSun);
											//m_TreeCtrl.SetItemData(hGrandSon1,0);

											pPoint->csPointType = xml.GetChildData();
											HTREEITEM hGrandSon1 = m_TreeCtrl.InsertItem(pPoint->csPointType,hGrandSun);
											m_TreeCtrl.SetItemData(hGrandSon1,0);
										}
										else if(csTmp == _T("context"))
										{
											pPoint->csContext = xml.GetChildData();
											HTREEITEM hGrandSon1 = m_TreeCtrl.InsertItem(pPoint->csContext,hGrandSun);
											m_TreeCtrl.SetItemData(hGrandSon1,0);
										}
										else if(csTmp == _T("alacause"))
										{
											pPoint->csAlaCause = xml.GetChildData();
											HTREEITEM hGrandSon1 = m_TreeCtrl.InsertItem(pPoint->csAlaCause,hGrandSun);
											m_TreeCtrl.SetItemData(hGrandSon1,0);
											CombAddString(CombAlmCause,pPoint->csAlaCause);
										}
										else if(csTmp == _T("alacolor"))
										{
											pPoint->csAlaColor = xml.GetChildData();
											HTREEITEM hGrandSon1 = m_TreeCtrl.InsertItem(pPoint->csAlaColor,hGrandSun);
											m_TreeCtrl.SetItemData(hGrandSon1,3);
										}
										else if(csTmp == _T("alatype"))
										{
											pPoint->csAlaType = xml.GetChildData();
											HTREEITEM hGrandSon1 = m_TreeCtrl.InsertItem(pPoint->csAlaType,hGrandSun);
											m_TreeCtrl.SetItemData(hGrandSon1,0);
										}
										else if(csTmp == _T("alalevel"))
										{
											pPoint->csAlaLevel = xml.GetChildData();
											//HTREEITEM hGrandSon1 = m_TreeCtrl.InsertItem(pPoint->csAlaLevel,hGrandSun);
											//m_TreeCtrl.SetItemData(hGrandSon1,0);
										}

										/**************** hjq  ****************************/
										else if(csTmp == _T("SourceCIName"))	//IO设备名称
										{
											pPoint->csIODeviceName = xml.GetChildData();
											HTREEITEM hGrandSon1 = m_TreeCtrl.InsertItem(pPoint->csIODeviceName,hGrandSun);
											m_TreeCtrl.SetItemData(hGrandSon1,0);
										}
										else if(csTmp == _T("SourceID"))	//来源标识
										{
											pPoint->csSourceID = xml.GetChildData();
											HTREEITEM hGrandSon1 = m_TreeCtrl.InsertItem(pPoint->csSourceID,hGrandSun);
											m_TreeCtrl.SetItemData(hGrandSon1,0);
										}
										else if(csTmp == _T("SourceSeverity"))	//原始告警级别	
										{
											pPoint->csOriAlarmLevel = xml.GetChildData();
											HTREEITEM hGrandSon1 = m_TreeCtrl.InsertItem(pPoint->csOriAlarmLevel,hGrandSun);
											m_TreeCtrl.SetItemData(hGrandSon1,0);
										}
										else if(csTmp == _T("Severity"))	//告警级别
										{
											pPoint->csAlarmLevel = xml.GetChildData();
											HTREEITEM hGrandSon1 = m_TreeCtrl.InsertItem(pPoint->csAlarmLevel,hGrandSun);
											m_TreeCtrl.SetItemData(hGrandSon1,0);
										}
										else if(csTmp == _T("SourceIdentifier"))	//压缩标识
										{
											pPoint->csCompress = xml.GetChildData();
											HTREEITEM hGrandSon1 = m_TreeCtrl.InsertItem(pPoint->csCompress,hGrandSun);
											m_TreeCtrl.SetItemData(hGrandSon1,0);
										}
										else if(csTmp == _T("instance"))	//指标实例
										{
											pPoint->csIndexEx = xml.GetChildData();
											HTREEITEM hGrandSon1 = m_TreeCtrl.InsertItem(pPoint->csIndexEx,hGrandSun);
											m_TreeCtrl.SetItemData(hGrandSon1,0);
										}
									}
									xml.OutOfElem();
									if(pDevice->pPointList.IsEmpty())
									{
										pDevice->pPointList.AddHead(pPoint);
									}
									else
									{
										pDevice->pPointList.AddTail(pPoint);
									}
								}
							}
							xml.OutOfElem();
							if(pRoom->pDeviceList.IsEmpty())
							{
								pRoom->pDeviceList.AddHead(pDevice);
							}
							else
							{
								pRoom->pDeviceList.AddTail(pDevice);
							}
						}
						xml.OutOfElem();
						if(pFloor->pRoomList.IsEmpty())
						{
							pFloor->pRoomList.AddHead(pRoom);
						}
						else
						{
							pFloor->pRoomList.AddTail(pRoom);
						}
					}
					xml.OutOfElem();
					if(pBuild->pFloorList.IsEmpty())
					{
						pBuild->pFloorList.AddHead(pFloor);
					}
					else
					{
						pBuild->pFloorList.AddTail(pFloor);
					}
				}
				xml.OutOfElem();
				if(pScene->pBuildList.IsEmpty())
				{
					pScene->pBuildList.AddHead(pBuild);
				}
				else
				{
					pScene->pBuildList.AddTail(pBuild);
				}
			}

			xml.OutOfElem();
			if(m_pSceneList.IsEmpty())
			{
				m_pSceneList.AddHead(pScene);
			}
			else
			{
				m_pSceneList.AddTail(pScene);
			}
		}
	}
}
//命令行参数解析
void CInterface3DDlg::CmdLineHandle(void)
{
	BOOL bFlag = FALSE;
	TCHAR szBuff[2];
	CString csTemp;
	CString csLine = AfxGetApp()->m_lpCmdLine;
	int j = 0;
	csLine = _T("dir -1");
	for(int i = 0;i < csLine.GetLength();i++)
	{
		if(csLine[i]=='-')
		{
			bFlag = TRUE;
			j = 0;
		}
		else
		{
			if(bFlag)
			{
				szBuff[j++] = csLine[i];
				szBuff[j] = '\0';
				csTemp = szBuff;
				bFlag = FALSE;
				break;
			}
		}
	}
	int nState = _ttoi(csTemp);
	if(nState == 1)//代表运行态
	{
		//ShowWindow(SW_HIDE);
		CreateTray();
		m_trPara.bWorkMode = WORK_VIEW;
		if(m_threadNumber>0){
	//		m_trPara.pThre[0]->ResumeThread();
	//		m_trPara.pThre[1]->ResumeThread();
			for(int i = 0;i < m_threadNumber; i++){
				if(m_trPara.pThre[i]){
					m_trPara.pThre[i]->ResumeThread();
				}else{
					break;
				}
			}
		}
	}
	else
	{
		m_trPara.bWorkMode = WORK_DRAW;
		if(m_threadNumber>0){
	//		m_trPara.pThre[0]->ResumeThread();
	//		m_trPara.pThre[1]->ResumeThread();
			for(int i = 0;i < m_threadNumber; i++){
				if(m_trPara.pThre[i]){
					m_trPara.pThre[i]->ResumeThread();
				}else{
					break;
				}
			}
		}

	}
}

void CInterface3DDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//DoWork();
	CDialogEx::OnTimer(nIDEvent);
}


void CInterface3DDlg::OnLbnSelchangeListAllNode()
{
	// TODO: 在此添加控件通知处理程序代码
	//CStatic *pWnd = (CStatic *)GetDlgItem(IDC_STATIC1);
	int nCur = m_clAllNode.GetCurSel();
	VARIANT vtName;
	CString csPath;
	m_clAllNode.GetText(nCur,csPath);

	CString csTmp;
	csTmp.Format(_T("[hao]:csPath:-------%s"),csPath);
	OutputDebugString(csTmp);

	//csNodeID = m_csDeviceName.Right(m_csDeviceName.GetLength() - m_csDeviceName.Find('_'));
	CString  csNodeID = csPath.Mid(csPath.Find('_') + 1) ;
	//SetDlgItemText(IDC_EDIT_DEVICE_NAME,m_csDeviceName);
	int nNodeID = _ttoi(csNodeID);

	csTmp.Format(_T("[hao]:csNodeID:-------%s"),csNodeID);
	OutputDebugString(csTmp);

	vtName = m_dbCom.GetNodeAllTagName(nNodeID);
	m_clCurNode.ResetContent();

	if(vtName.vt == VT_NULL || vtName.vt == VT_EMPTY)
	{
		OutputDebugString(_T("[hao]:Error:------------> vtName.vt == VT_NULL"));
	}

	if(vtName.vt == VT_EMPTY)
	{
		OutputDebugString(_T("[hao]:Error:------------> vtName.vt == VT_EMPTY"));
	}

	if(vtName.vt != VT_NULL && vtName.vt != VT_EMPTY)
	{
		SAFEARRAY* pSafeArray = vtName.parray;
		//CString  csStrTemp;
		VARIANT HUGEP* pbstr;
		OutputDebugString(_T("[hao]:------------> vtName.vt != VT_NULL && vtName.vt != VT_EMPTY"));
		SafeArrayAccessData(pSafeArray, (void HUGEP*FAR*)&pbstr);
		for(UINT i = 0;i < pSafeArray->rgsabound->cElements;i++)
		{
			CString csName =  pbstr[i].bstrVal;
			//int nLen = csName.GetLength() - csName.ReverseFind('\\')-1;
			//csName = csName.Right(nLen);
			m_clCurNode.AddString(csName);
		}
		SafeArrayUnaccessData(pSafeArray);
		SafeArrayDestroy(pSafeArray);
	}
}


void CInterface3DDlg::OnLbnSelchangeListCurNode()
{
	// TODO: 在此添加控件通知处理程序代码
	int nCur  = m_clCurNode.GetCurSel();

	m_clCurNode.GetText(nCur,m_csPointName);
	int nPos = m_csPointName.Find('\\');
	m_csPath = m_csPointName.Left(nPos);
	m_csPointName = m_csPointName.Mid(nPos + 1);
	SetDlgItemText(IDC_STATIC1,m_csPointName);
}

//遍历所有树查找指定的节点
void CInterface3DDlg::SearchNode(HTREEITEM hTree)
{
	CStringList cslist;
	HTREEITEM hParent = hTree;
	do
	{
		CString csName = m_TreeCtrl.GetItemText(hParent);
		if(!csName.IsEmpty())
		{
			if(cslist.IsEmpty())
			{
				cslist.AddHead(csName);
			}
			else
			{
				cslist.AddTail(csName);
			}
		}
		hParent = m_TreeCtrl.GetParentItem(hParent);
	}while(hParent);

	CMarkup xml;

	TCHAR tcPath[100];
	::GetModuleFileName(NULL,tcPath,100);
	CString csPath = tcPath;
	csPath = csPath.Left( csPath.ReverseFind('\\')+1) + _T("data.xml");
	BOOL bLoadXml = xml.Load(csPath); //加载xml文件  
	if(bLoadXml)
	{
		xml.ResetMainPos();		//将指针定义到第一个顶级标签的上一个位置<文本>
		xml.FindElem();			//将将指针定义到第一个顶级标签 ROOT
		POSITION pos = cslist.GetTailPosition();
		CString csNodeName = cslist.GetPrev(pos);
		while(xml.FindChildElem())//场景
		{
			if(csNodeName == xml.GetChildTagName())
			{
				xml.IntoElem();
				if(pos == NULL)
				{
					BOOL bFlag = xml.RemoveNode();
					if(bFlag)
					{
						AfxMessageBox(_T("DELETE OK"));
					}
					break;
				}
				csNodeName = cslist.GetPrev(pos);
			}
		}
	}
	xml.Save(csPath);
}

void CInterface3DDlg::OnBnClickedDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	HTREEITEM hCur = m_TreeCtrl.GetSelectedItem();
	if(m_TreeCtrl.GetItemData(hCur) == 0)
	{
		CString csResourse;
		csResourse.LoadString(IDS_STRING_NodeDlete);
		AfxMessageBox(csResourse);
	}
	else
	{
		SearchNode(hCur);
		m_TreeCtrl.DeleteItem(hCur);
	}
	UpDateFile();
	//NodeToFile();
	
	//CDialogEx::OnCancel();
// 	POINT_DB pt;
// 	
// 	AddPointState(&pt);
}


void CInterface3DDlg::OnCbnSelchangeComboIndex()
{
	// TODO: 在此添加控件通知处理程序代码
	CString csType;
	m_cbIndex.GetWindowText(csType);

	m_nItemIndex = m_cbIndex.GetCurSel();//获取当前的 item 索引，方便查找对应的英文。

	if (csType.IsEmpty())
	{
		AfxMessageBox(_T("点类型不能为空!"));
		return ;
	}
	UpDateItem();
// 	int nCur = m_cbIndex.GetCurSel();
// 	m_cbType.ResetContent();
// 	for(int i = 0;i < 17;i++)
// 	{
// 		if(g_nStrid[nCur][i] == -1)
// 		{
// 			break;
// 		}
// 		CString csTmp;
// 		csTmp.LoadString(g_nStrid[nCur][i]);
// 		m_cbType.AddString(csTmp);
// 	}
// 	m_cbType.SetCurSel(0);
}

void CInterface3DDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CSetDlg dlg;
	dlg.m_csIP = m_csIP;
	dlg.m_csPort = m_csPort;
	dlg.m_nTime = m_nTime;
	if(dlg.DoModal() == IDOK)
	{
		m_csIP = dlg.m_csIP;
		m_csPort = dlg.m_csPort;
		m_nTime = dlg.m_nTime;

		CIniFile Ini;
		Ini.SetFileName(_T(".\\config.ini"));
		Ini.SetString(_T("SET"),_T("IP"),m_csIP); 
		Ini.SetString(_T("SET"),_T("PORT"),m_csPort); 
		Ini.SetInt(_T("SET"),_T("time"),m_nTime); 
	}
}


void CInterface3DDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_threadNumber>0)
	{
		if(m_bFlagStop)
		{
//			int len = sizeof(m_trPara.pThre) / sizeof(m_trPara.pThre[0]);
			for(int i = 0;i < m_threadNumber; i++){
				if(m_trPara.pThre[i]){
					m_trPara.pThre[i]->ResumeThread();
				}else{
					break;
				}
			}

			SetDlgItemText(IDC_BUTTON2,_T("暂停"));
			m_bFlagStop = FALSE;
		}
		else
		{
//			m_trPara.pThre[0]->SuspendThread();
//			m_trPara.pThre[1]->SuspendThread();
//			int len = sizeof(m_trPara.pThre) / sizeof(m_trPara.pThre[0]);
			for(int i = 0;i < m_threadNumber; i++){
				if(m_trPara.pThre[i]){
					m_trPara.pThre[i]->SuspendThread();
				}else{
					break;
				}
			}
			SetDlgItemText(IDC_BUTTON2,_T("继续"));
			m_bFlagStop = TRUE;
		}
	}
/*
	if(m_trPara.pThre2)
	{
		if(m_bFlagStop)
		{
			m_trPara.pThre2->ResumeThread();
			SetDlgItemText(IDC_BUTTON2,_T("暂停"));
			m_bFlagStop = FALSE;
		}
		else
		{
			m_trPara.pThre2->SuspendThread();
			SetDlgItemText(IDC_BUTTON2,_T("继续"));
			m_bFlagStop = TRUE;
		}
	}
*/
}

void CInterface3DDlg::CreateTray(void)
{
	m_nid.cbSize = sizeof(NOTIFYICONDATA);
	m_nid.hWnd = m_hWnd; 
	m_nid.uID = IDR_MAINFRAME; 
	m_nid.uFlags = NIF_MESSAGE|NIF_ICON|NIF_TIP;
	m_nid.uCallbackMessage = WM_TRAY;    //自定义消息
	m_nid.hIcon = m_hIcon;                                               
	_tcscpy (m_nid.szTip,_T("interface"));
	ShowWindow(SW_HIDE);
	::Shell_NotifyIcon(NIM_ADD, &m_nid);
}

LRESULT CInterface3DDlg::OnBnTray(WPARAM wparam,LPARAM lparam)
{
	
	if (lparam == WM_LBUTTONDBLCLK)
	{  
		ShowWindow(SW_SHOW);
		::Shell_NotifyIcon(NIM_DELETE, &m_nid);
	}
	return 0;
}

void CInterface3DDlg::OnCbnSelchangeComboInst()
{
	// TODO: 在此添加控件通知处理程序代码
}




void CInterface3DDlg::AddPointState(LPVOID pT)
{
// 	POINT_DB *pt = (POINT_DB *)pT;
// 	POSITION  pos = m_pSceneList.GetHeadPosition();
// 	while(pos != NULL)
// 	{
// 		Scene_para *pS= (Scene_para *)m_pSceneList.GetNext(pos);
// 		POSITION pos1 = pS->pDeviceList.GetHeadPosition();
// 
// 		while(pos1 != NULL)
// 		{		
// 			Device *pPd= (Device *)pS->pDeviceList.GetNext(pos1);
// 			POSITION pos2 = pPd->pPointList.GetHeadPosition();		
// 			while(pos2 != NULL)
// 			{
// 				double dbValue = 0;
// 				Point_DB  *pPt= (Point_DB *)pPd->pPointList.GetNext(pos2);
// 				if (pPt->csChildId == pt->csChildId)
// 				{
// 					pPt->nState = pt->nState;
// 				}				
// 			}
// 		}
// 	}

// 	POSITION  posa = m_pSceneList.GetHeadPosition();
// 	while(posa != NULL)
// 	{
// 		Scene_para *pSa= (Scene_para *)m_pSceneList.GetNext(posa);
// 		POSITION pos1a = pSa->pDeviceList.GetHeadPosition();
// 
// 		while(pos1a != NULL)
// 		{		
// 			Device *pPda= (Device *)pSa->pDeviceList.GetNext(pos1a);
// 			POSITION pos2a = pPda->pPointList.GetHeadPosition();		
// 			while(pos2a != NULL)
// 			{
// 				double dbValue = 0;
// 				Point_DB  *pPta= (Point_DB *)pPda->pPointList.GetNext(pos2a);
// 				if (pPta->csChildId == pt->csChildId)
// 				{
// 					int n = pPta->nState;
// 					if (n == 0)
// 					{
// 						n = 18;
// 					}
// 				}				
// 			}
// 		}
// 	}
}


void CInterface3DDlg::OnBnClickedBtnAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	m_csItem = "";
	CAddItem Addlg(this);
	Addlg.DoModal();
	CString csItem = m_csItem;
	csItem.Trim();
	CString csType;
	m_cbIndex.GetWindowText(csType);
	if (csType.IsEmpty() || csItem.IsEmpty())
	{
		AfxMessageBox(_T("点类型不能为空!"));
		return ;
	}

	//如果条目不存在;
	CMarkup xml;
	TCHAR tcPath[100];
	::GetModuleFileName(NULL,tcPath,100);
	CString csPath = tcPath;
	csPath = csPath.Left( csPath.ReverseFind('\\')+1) + _T("Item.xml");
	if(GetFileAttributes(csPath) == 0xffffffff) //文件不存在时  
	{
		xml.SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n"));
		xml.AddElem(_T("Root"));
		xml.AddChildElem(csType);
		xml.IntoElem();
		xml.AddChildElem(_T("TypeNum"),_T(" "));
		xml.AddChildElem(_T("TypeEnglish"),_T(" "));
		xml.AddChildElem(_T("Item"),csItem);
		xml.OutOfElem();
		xml.Save(csPath);
		UpDateItem(csItem);
	}
	else
	{
		BOOL bLoadXml =xml.Load(csPath); //加载xml文件  
		if (bLoadXml) 
		{
			xml.ResetMainPos();	//将指针定义到第一个顶级标签的上一个位置<文本>  
			xml.FindElem();		//将将指针定义到第一个顶级标签 
		
			if(xml.FindChildElem(csType))
			{				
					xml.IntoElem();
					while(xml.FindChildElem())
					{
						CString sonItem = xml.GetChildData();
						if (sonItem == csItem)
						{
							AfxMessageBox(_T("条目已存在，请勿重复添加！"));
							return;
						}
					}
					xml.AddChildElem(_T("Item"),csItem);
					xml.OutOfElem();
					xml.Save(csPath);
					UpDateItem(csItem);
					return;				
			}			

			xml.AddChildElem(csType);
			xml.IntoElem();
			xml.AddChildElem(_T("Item"),csItem);
			xml.OutOfElem();
			xml.Save(csPath);
			UpDateItem(csItem);
		}		
	}
}





void CInterface3DDlg::OnBnClickedBtnItemdel()
{
	// TODO: 在此添加控件通知处理程序代码
	CString csNodeName;
	GetDlgItem(IDC_COMBO_TYPE)->GetWindowText(csNodeName);
	CString csType;
	m_cbIndex.GetWindowText(csType);

	if (csNodeName.IsEmpty() || csType.IsEmpty())
	{
		return;
	}
	CMarkup xml;
	TCHAR tcPath[100];
	::GetModuleFileName(NULL,tcPath,100);
	CString csPath = tcPath;
	csPath = csPath.Left( csPath.ReverseFind('\\')+1) + _T("Item.xml");
	BOOL bLoadXml = xml.Load(csPath); //加载xml文件
	if(bLoadXml)
	{
		xml.ResetMainPos();		//将指针定义到第一个顶级标签的上一个位置<文本>
		xml.FindElem();			//将将指针定义到第一个顶级标签 ROOT	
		
		if(xml.FindChildElem(csType))//
		{
				xml.IntoElem();
				while(xml.FindChildElem())
				{
					CString xmlchild = xml.GetChildData();
					if(csNodeName == xmlchild)
					{
						BOOL bFlag = xml.RemoveChildElem();
						if(bFlag)
						{							
							xml.OutOfElem();
							xml.Save(csPath);
							UpDateItem();
							AfxMessageBox(_T("删除成功"));
						}
						return;
					}
				}				
		}
	}
	
}

void CInterface3DDlg::UpDateItem(CString type)
{
	//m_cbType.ResetContent();
	((CComboBox *)GetDlgItem(IDC_COMBO_TYPE))->ResetContent();
	CMarkup xml;
	BOOL bLoadXml = FALSE; 
	TCHAR tcPath[100];
	::GetModuleFileName(NULL,tcPath,100);
	CString csPath = tcPath;
	csPath = csPath.Left(csPath.ReverseFind('\\')+1) + _T("Item.xml");
	bLoadXml = xml.Load(csPath); //加载xml文件  
	CString csType;
	m_cbIndex.GetWindowText(csType);
	if (csType.IsEmpty())
	{
		//AfxMessageBox(_T("点类型不能为空!"));
		return ;
	}

	if (bLoadXml) 
	{
		xml.ResetMainPos();//将指针定义到第一个顶级标签的上一个位置<文本>  
		xml.FindElem();//将将指针定义到第一个顶级标签 	
		int i = 0,n = 0;
		if(xml.FindChildElem(csType))//场景
		{
			xml.IntoElem();
			
			while(xml.FindChildElem())//指标级循环
			{
				CString csName = xml.GetChildTagName();
				CString ItemData;
				if(csName == _T("Item"))
				{
					i++;
					ItemData = xml.GetChildData();
					if (ItemData == type)
					{
						n = i;
					}
					((CComboBox *)GetDlgItem(IDC_COMBO_TYPE))->AddString(ItemData);
				}
				else if (csName == _T("TypeEnglish"))
				{
					m_csItemEnglish = xml.GetChildData();
				}
				else if (csName == _T("TypeNum"))
				{
					m_csTypeNum = xml.GetChildData();
				}
			}
			if (n > 0)
			{
				((CComboBox *)GetDlgItem(IDC_COMBO_TYPE))->SetCurSel(n-1);
			}
			xml.OutOfElem();
		}
	}
}

void CInterface3DDlg::OnClose()
{
	m_trPara.bIsExit = FALSE;

	if(m_threadNumber>0){
		for(int i = 0;i < m_threadNumber; i++){
			
			WaitForSingleObject(m_trPara.pThre[i],100);
/*			if(WaitForSingleObject(m_trPara.pThre[i],INFINITE) == WAIT_OBJECT_0)  //等待退出
			{
//				m_trPara.pThre[i]->ResumeThread();
			}
*/
		}
	}

	try{  
		if( m_connection != NULL) 
		{
			m_connection->close(); 
			delete m_connection;  
		}
	}
	catch ( CMSException& e ) {
		e.printStackTrace();
	}  

	m_connection = NULL;  														      
	activemq::library::ActiveMQCPP::shutdownLibrary();



	CDialogEx::OnClose();
}


//告警颜色选择
void CInterface3DDlg::OnBnClickeBtnAlmColor()
{
	CColorDialog colorAlmDlg;
	colorAlmDlg.m_cc.Flags |= CC_FULLOPEN|CC_RGBINIT;   // CC_RGBINIT可以让上次选择的颜色作为初始颜色显示出来
	colorAlmDlg.m_cc.rgbResult = m_colorAla;			//记录上次选择的颜色
	if(IDOK ==colorAlmDlg.DoModal())
	{
		m_colorAla = colorAlmDlg.m_cc.rgbResult;        // 保存用户选择的颜色
	}
	m_MfcBtnAlmColor.SetFaceColor(m_colorAla);			//设置 button 颜色
	m_csAlaColor.Format(_T("#%X"),m_colorAla);
}

//设置字体为告警颜色
void CInterface3DDlg::OnCustomdrawTreeScene(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVCUSTOMDRAW pNMCD = reinterpret_cast<LPNMTVCUSTOMDRAW>(pNMHDR);

	switch (pNMCD->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
		*pResult = CDRF_NOTIFYITEMDRAW;
		return;
	case CDDS_ITEMPREPAINT:
		{
			HTREEITEM hTreeItem = (HTREEITEM)pNMCD->nmcd.dwItemSpec;
			// 这里做判断
			if   (m_TreeCtrl.GetItemData(hTreeItem) == 3) 
			{ 
				CString csColor = m_TreeCtrl.GetItemText(hTreeItem);
				csColor.Delete(0,1);
				CStringA csColorA = (CStringA)csColor;
				const char* chTmp = csColorA.GetString();
				DWORD dwColor;
				dwColor = strtoul(chTmp,NULL,16);
				pNMCD->clrText = dwColor;
			} 
		}
		break;
	}


	*pResult = 0;
}


//更新文件
void CInterface3DDlg::UpDateFile()
{
	CMarkup xml;
	TCHAR tcPath[100];
	::GetModuleFileName(NULL,tcPath,100);
	CString csPath = tcPath;
	csPath = csPath.Left( csPath.ReverseFind('\\')+1) + _T("data.xml");
	if(GetFileAttributes(csPath) == 0xffffffff) //文件不存在时  
	{  	
		xml.SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n"));
		xml.AddElem(_T("Root"));
	}
	else
	{
		BOOL bLoadXml =xml.Load(csPath); //加载xml文件  
		if (bLoadXml) 
		{
			xml.ResetMainPos();	//将指针定义到第一个顶级标签的上一个位置<文本>  
			xml.RemoveNode();
			xml.SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n"));
			xml.AddElem(_T("Root"));
		}
	}
	                                                                    
	HTREEITEM hRoot = m_TreeCtrl.GetRootItem();
	while(hRoot)//场景
	{
		CString csTmp = m_TreeCtrl.GetItemText(hRoot);
		CString csScene = _T("SCENE_");
		csScene += csTmp;
		xml.AddChildElem(csScene);
		xml.IntoElem();
		HTREEITEM hSonBuild = m_TreeCtrl.GetChildItem(hRoot);
		while(hSonBuild)//楼宇
		{
			csTmp = m_TreeCtrl.GetItemText(hSonBuild);
			xml.AddChildElem(csTmp);
			xml.IntoElem();
			HTREEITEM hSonFloor = m_TreeCtrl.GetChildItem(hSonBuild);
			while(hSonFloor)//楼层
			{
				csTmp = m_TreeCtrl.GetItemText(hSonFloor);
				CString csFloor = _T("FLOOR_");
				csFloor += csTmp;
				xml.AddChildElem(csFloor);
				xml.IntoElem();
				HTREEITEM hSonRoom = m_TreeCtrl.GetChildItem(hSonFloor);
				while(hSonRoom)//房间
				{
					csTmp = m_TreeCtrl.GetItemText(hSonRoom);
					xml.AddChildElem(csTmp);
					xml.IntoElem();
					HTREEITEM hSonDevice = m_TreeCtrl.GetChildItem(hSonRoom);
					while(hSonDevice)//设备
					{
						BOOL bIsDevNum = TRUE;//是否是设备号
						csTmp = m_TreeCtrl.GetItemText(hSonDevice);
						xml.AddChildElem(csTmp);
						xml.IntoElem();
						HTREEITEM hSonTag = m_TreeCtrl.GetChildItem(hSonDevice);
						while(hSonTag)//点
						{			
							csTmp = m_TreeCtrl.GetItemText(hSonTag);
							if ( bIsDevNum )
							{
								xml.AddChildElem(_T("id"),csTmp);
								bIsDevNum = FALSE;
							}
							else
							{
								xml.AddChildElem(csTmp);
								xml.IntoElem();
								HTREEITEM hTagInfo = m_TreeCtrl.GetChildItem(hSonTag);
								int n = m_TreeCtrl.GetCount();
								int nTagInfoNum = 0;
								CString csType;
								while(hTagInfo)
								{
									csTmp = m_TreeCtrl.GetItemText(hTagInfo);
									switch(nTagInfoNum)
									{
									case 0:
										{
											xml.AddChildElem(_T("path"),csTmp);
										}
										break;
									case 1:
										{
											xml.AddChildElem(_T("ptype"),csTmp);
											csType = csTmp;
										}
										break;
									case 2:		
										xml.AddChildElem(_T("bigtype"),csTmp);
										break;
									case 3:		
										xml.AddChildElem(_T("bigtypenum"),csTmp);
										break;
									case 4:		
										xml.AddChildElem(_T("bigtypeng"),csTmp);
										break;
									case 5:		
										xml.AddChildElem(_T("type"),csTmp);
										break;
									case 6:		
										xml.AddChildElem(_T("context"),csTmp);
										break;
									case 7:		
										if (csType == _T("告警"))
											xml.AddChildElem(_T("alacause"),csTmp);
										else if (csType == _T("监控"))
											xml.AddChildElem(_T("SourceCIName"),csTmp);
										break;
									case 8:		
										if (csType == _T("告警"))
											xml.AddChildElem(_T("alacolor"),csTmp);
										else if (csType == _T("监控"))
											xml.AddChildElem(_T("instance"),csTmp);
										break;
									case 9:
										if (csType == _T("告警"))
											xml.AddChildElem(_T("alatype"),csTmp);
										break;
									case 10:
										if (csType == _T("告警"))
											xml.AddChildElem(_T("SourceCIName"),csTmp);
										break;
									case 11:
										if (csType == _T("告警"))
											xml.AddChildElem(_T("instance"),csTmp);
										break;
									case 12:
										if (csType == _T("告警"))
											xml.AddChildElem(_T("SourceID"),csTmp);
										break;
									case 13:
										if (csType == _T("告警"))
											xml.AddChildElem(_T("SourceSeverity"),csTmp);
										break;
									case 14:
										if (csType == _T("告警"))
											xml.AddChildElem(_T("Severity"),csTmp);
										break;
									case 15:
										if (csType == _T("告警"))
											xml.AddChildElem(_T("SourceIdentifier"),csTmp);
										break;
									default:
										break;
									}
									nTagInfoNum++;
									hTagInfo = m_TreeCtrl.GetNextSiblingItem(hTagInfo);
								}
								xml.OutOfElem();
							}
							hSonTag = m_TreeCtrl.GetNextSiblingItem(hSonTag);
						}
						xml.OutOfElem();
						hSonDevice = m_TreeCtrl.GetNextSiblingItem(hSonDevice);
					}
					xml.OutOfElem();
					hSonRoom = m_TreeCtrl.GetNextSiblingItem(hSonRoom);
				}
				xml.OutOfElem();
				hSonFloor = m_TreeCtrl.GetNextSiblingItem(hSonFloor);
			}
			xml.OutOfElem();
			hSonBuild = m_TreeCtrl.GetNextSiblingItem(hSonBuild);
		}
		xml.OutOfElem();
		hRoot = m_TreeCtrl.GetNextSiblingItem(hRoot);
	}
	xml.Save(csPath);
}

void CInterface3DDlg::AlarmChangeDbcommocxctrlfc71(BOOL bInit, long lAlarmCount, const VARIANT& AlarmData)
{
	CString csDebug;
	csDebug.Format(_T("[hao]:	AlarmChangeDbcommocxctrlfc71   -- start"));
	if (AlarmData.vt != VT_NULL && AlarmData.vt != VT_EMPTY)
	{
		csDebug.Format(_T("[hao]:AlarmData.vt != VT_NULL && AlarmData.vt != VT_EMPTY"));
		CString csTagNameTmp,csTagStatus,csAlarmType,csAlarmStatus;
		double dbTagValue,dbLimitValue;
		int nTagNameIndex;
		long UBOUND;
		SAFEARRAY* pSafeArray= AlarmData.parray;
		VARIANT HUGEP* pbstrAla;
		VARIANT vtTagName;
		SafeArrayAccessData(pSafeArray, (void HUGEP*FAR*)&pbstrAla);
		HRESULT  lRet;
		lRet = SafeArrayGetUBound(pSafeArray,1,&UBOUND);
		for(int i = 0;i <= UBOUND;i++)
		{
			nTagNameIndex = 11 * (UBOUND + 1) + i;	//点数值
			if(pbstrAla[nTagNameIndex].vt == VT_R4)
				dbTagValue = pbstrAla[nTagNameIndex].fltVal;

			nTagNameIndex = 12 * (UBOUND + 1) + i;	//点限值
			if(pbstrAla[nTagNameIndex].vt == VT_R4)
				dbLimitValue = pbstrAla[nTagNameIndex].fltVal;

			nTagNameIndex = 13 * (UBOUND + 1) + i;	//点名
			if (pbstrAla[nTagNameIndex].vt == VT_BSTR)
			{
				csTagNameTmp = pbstrAla[nTagNameIndex].bstrVal;		
			}

			nTagNameIndex = 15 * (UBOUND + 1) + i;	//数字量报警逻辑
			if (pbstrAla[nTagNameIndex].vt == VT_BSTR)
			{
				csAlarmStatus = pbstrAla[nTagNameIndex].bstrVal;		
			}

			nTagNameIndex = 16 * (UBOUND + 1) + i;	//数字量报警逻辑
			if (pbstrAla[nTagNameIndex].vt == VT_BSTR)
			{
				csAlarmType = pbstrAla[nTagNameIndex].bstrVal;		
			}

			m_AlarmTagInfo.csTagName = csTagNameTmp;															//报警点点名
			vtTagName.bstrVal = csTagNameTmp.AllocSysString();
			m_AlarmTagInfo.bAlarmTagType = (BOOL)m_dbCom.GetTagType(&vtTagName.bstrVal);	//报警点类型

			nTagNameIndex = 14 * (UBOUND + 1) + i;	//报警类型
			if(pbstrAla[nTagNameIndex].vt == VT_BSTR)
			{
				csTagStatus = pbstrAla[nTagNameIndex].bstrVal;
				if(csTagStatus == _T("高报") || csTagStatus == _T("高高报") || csTagStatus == _T("高3报") || csTagStatus == _T("高4报") || csTagStatus == _T("高5报"))
				{
					if(dbTagValue >= dbLimitValue)
					{
						m_cslistTagName.AddTail(csTagNameTmp);

						m_AlarmTagInfo.bFlag = 1;							//报警标志位
						m_AlarmTagInfo.bLimitHiFlag = 1;				//模拟点高限值标志位
						m_AlarmTagInfo.dbLimitHi	=	dbLimitValue;	//模拟点高限值
						m_AlarmTagInfo.bLimitLoFlag	= 0;				//模拟点低限值标志位
						m_AlarmTagInfo.dbLimiLo	=	0;					//模拟点高限值
						m_AlarmTagInfo.dbValue	= dbTagValue;		//模拟点报警值
						m_AlarmTagInfo.bDigType = 0;					//数字点类型
						m_AlarmTagInfoList.AddTail(m_AlarmTagInfo);
					}
				}
				if(csTagStatus == _T("低报") || csTagStatus == _T("低低报") || csTagStatus == _T("低3报") || csTagStatus == _T("低4报") || csTagStatus == _T("低5报"))
				{
					if(dbTagValue <= dbLimitValue)
					{
						m_cslistTagName.AddTail(csTagNameTmp);

						m_AlarmTagInfo.bFlag = 1;							//报警标志位
						m_AlarmTagInfo.bLimitHiFlag = 0;				//模拟点高限值标志位
						m_AlarmTagInfo.dbLimitHi	=	0;					//模拟点高限值
						m_AlarmTagInfo.bLimitLoFlag	=1;				//模拟点低限值标志位
						m_AlarmTagInfo.dbLimiLo	=	dbLimitValue;	//模拟点高限值
						m_AlarmTagInfo.dbValue	= dbTagValue;		//模拟点报警值
						m_AlarmTagInfo.bDigType = 0;					//数字点类型
						m_AlarmTagInfoList.AddTail(m_AlarmTagInfo);
					}
				}
				if(csTagStatus == _T("开关量报警"))
				{
					if(csAlarmType == _T("关闭->打开") && csAlarmStatus == _T("打开"))
					{
						m_cslistTagName.AddTail(csTagNameTmp);

						m_AlarmTagInfo.bFlag = 1;							//报警标志位
						m_AlarmTagInfo.bLimitHiFlag = 0;				//模拟点高限值标志位
						m_AlarmTagInfo.dbLimitHi	=	0;					//模拟点高限值
						m_AlarmTagInfo.bLimitLoFlag	=0;				//模拟点低限值标志位
						m_AlarmTagInfo.dbLimiLo	=	0;					//模拟点高限值
						m_AlarmTagInfo.dbValue	= dbTagValue;		//模拟点报警值
						m_AlarmTagInfo.bDigType = 0;					//数字点类型
						m_AlarmTagInfoList.AddTail(m_AlarmTagInfo);
					}
					if(csAlarmType == _T("打开->关闭") && csAlarmStatus == _T("关闭"))
					{
						m_cslistTagName.AddTail(csTagNameTmp);

						m_AlarmTagInfo.bFlag = 1;							//报警标志位
						m_AlarmTagInfo.bLimitHiFlag = 0;				//模拟点高限值标志位
						m_AlarmTagInfo.dbLimitHi	=	0;					//模拟点高限值
						m_AlarmTagInfo.bLimitLoFlag	=0;				//模拟点低限值标志位
						m_AlarmTagInfo.dbLimiLo	=	0;					//模拟点高限值
						m_AlarmTagInfo.dbValue	= dbTagValue;		//模拟点报警值
						m_AlarmTagInfo.bDigType = 1;					//数字点类型
						m_AlarmTagInfoList.AddTail(m_AlarmTagInfo);
					}
				}
			}
			SysFreeString(vtTagName.bstrVal);
		}
	//	SysFreeString(vtTagName.bstrVal);
		/*SafeArrayUnaccessData(pSafeArray);
		if(pSafeArray != NULL)
			SafeArrayDestroy(pSafeArray);*/
	}
	csDebug.Format(_T("[hao]:	AlarmChangeDbcommocxctrlfc71   -- end"));
}
