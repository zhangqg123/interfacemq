
// Interface3DDlg.h : 头文件
//

#pragma once
#include "dbcommocxctrlfc71.h"
#include "afxwin.h"
#include "IniFile.h"
#include "LogFile.h"
#include <afxtempl.h>
/**********************amq***********************************/
#include <activemq/library/ActiveMQCPP.h>
//#include <decaf/lang/Thread.h> 
//#include <decaf/lang/Runnable.h>
//#include <decaf/util/concurrent/CountDownLatch.h>
//#include <decaf/lang/Integer.h>  
//#include <decaf/lang/Long.h>  
//#include <decaf/lang/System.h>  
#include <activemq/core/ActiveMQConnectionFactory.h>  
//#include <activemq/util/Config.h>  
#include <cms/Connection.h>  
#include <cms/Session.h>  
#include <cms/TextMessage.h>  
#include <cms/BytesMessage.h>  
#include <cms/MapMessage.h>  
#include <cms/ExceptionListener.h>  
#include <cms/MessageListener.h>
#include "json\\json.h"
#include "afxcolorbutton.h"
#include "afxbutton.h"

using namespace decaf::util::concurrent;  
using namespace decaf::util;  
using namespace decaf::lang;  
using namespace cms;
using namespace std;

//comb控件枚举
enum emComb
{
	CombSceneName = 0,
	CombBuildName = 1,
	CombFloorName = 2,
	CombRoomName = 3,
	CombDeviceName = 4,
	CombDeviceID = 5,
	CombAlmCause = 6,
	CombIODeviceName = 7,
	CombSourceID = 8,
	CombOriAlarmLevel = 9,
	CombAlarmLevel = 10,
	CombCompress = 11,
	CombIndexEx = 12
};
typedef struct THREAD_PARA
{
	BOOL bIsExit;
	BOOL bWorkMode;
	CWinThread *pThre[20];
//	CWinThread *pThre2;
}Thread_para; 

//新建场景的属性
typedef struct SCENE_PARA
{
	CString csName ;
	CPtrList pBuildList;
}Scene_para;

//楼宇
typedef struct BUILD_PARA
{
	CString csName ;
	CPtrList pFloorList;
}Build_para;

//楼层
typedef struct FLOOR_PARA
{
	CString csName ;
	CPtrList pRoomList;
}Floor_para;

//房间
typedef struct ROOM_PARA
{
	CString csName ;
	CPtrList pDeviceList;
}Room_para;

//DB  设备的属性
typedef struct DEVICE
{
	CString csName;       //设备名字
	CString csID;	       //id
	CPtrList  pPointList;
}Device;

//DB  设备的属性
typedef struct POINT_DB
{
	CString csName;			//点名
	CString csPath;			//数据库节点名
	CString csPointType;    //点类型  报警和监控
	CString csBigType;		//设备类型
	CString csBigTypeNum;	//设备类型编号
	CString csBigTypeEng;	//设备类型英文名
	CString csType;			//类型    温度 湿度
	CString csChildId;
	CString csDataType;   //数值  状态
	CString csPara;		 //关联的pv值
	CString csContext;		 //关联的pv值
	CString csAlaCause;		//报警原因
	CString csAlaColor;		//报警颜色
	CString csAlaType;		//报警类型
	CString csAlaLevel;		//报警等级
	int nState;//报警状态

	/************** hjq **********************/
	CString	csIODeviceName;	//IO设备名称
	CString	csSourceID;		//来源标识
	CString	csOriAlarmLevel;//原始告警级别	
	CString	csAlarmLevel;	//告警级别	
	CString	csCompress;		//压缩标识	
	CString	csIndexEx;		//指标实例
	CString csLongTagName;
	CString csParDESC;		//长点名+参数desc
	CString csTagDESC;		//点描述
}Point_DB;

typedef struct AMQ
{
	static Connection  * connection;  //连接
	static Session * session; //会话
	Destination  * destination;  //目的
	MessageProducer * producer; //生产者
	MessageConsumer * consumer;	//消费者
}Amq;

struct AlarmTagInfo
{
	BOOL bFlag;				//报警标志位
	CString csTagName;	//点名
	BOOL bAlarmTagType;	//报警点类型. 0:模拟量. 1:数字量
	BOOL bLimitHiFlag;	//模拟点高限值标志位
	double dbLimitHi;		//模拟点高限值
	BOOL bLimitLoFlag;	//模拟点低限值标志位
	double dbLimiLo;		//模拟点低限值
	BOOL bDigType;		//数字点类型	0:关闭->打开. 1:打开->关闭
	double dbValue;			//报警值
	/*AlarmTagInfo()
	{
		memset(this,0,sizeof(AlarmTagInfo));
	}
	~AlarmTagInfo(){}*/
};


// CInterface3DDlg 对话框
class CInterface3DDlg : public CDialogEx
{
// 构造
public:
	CInterface3DDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CInterface3DDlg();
	int  m_threadNumber;
// 对话框数据
	enum { IDD = IDD_INTERFACE3D_DIALOG };
	enum {WORK_DRAW = 0,WORK_VIEW};
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
public:  
	CDbcommocxctrlfc71 m_dbCom;
	CString m_csNodeName; //显示节点的名字
	//CString m_csNodeName; //显示节点的id
	CListBox m_clAllNode;
	CListBox m_clCurNode;
	CComboBox m_cbIndex;
	CComboBox m_cbPointType;
	CComboBox m_cbType;
	CComboBox m_cbDataType;

	CComboBox m_cbSceneName;//场景名
	CComboBox m_cbDeviceName;//设备名
	CComboBox m_cbDeviceID;//设备ID
	CComboBox m_cbBuildName;//楼宇
	CComboBox m_cbFloorName;//楼层
	CComboBox m_cbRoomName;//房间
	CComboBox m_cbAlaCause;//告警原因
	CComboBox m_cbAlaType;//告警类型

	CString	m_csBuildName;//楼宇编号
	CString	m_csFloorName;//楼层编号
	CString m_csRoomName;//房间编号

	CStringList  m_ctList;
	Thread_para	m_trPara;

	NOTIFYICONDATA m_nid;  //托盘

	CString m_csIndex;   //设备大类
	CString m_csContext;  //报警内容
	CString m_csSceneName;//场景名字
	CString m_csDeviceName;
	CString m_csDeviceId;//场景id
	CString m_csPointName;
	CString m_csChildId;
	CString m_csPath;
	CString m_csPointType;
	CString m_csType;
	CString m_csDataType;
	int m_nTime;//推送时间间隔
	CString m_csIP;
	CString m_csPort;
	Json::Value Jroot_M[20];//JSON STRING 
	Json::Value Jroot_A[20];//JSON STRING 
	CTreeCtrl m_TreeCtrl;
	//BOOL m_bIsAlarm;  //是否报警
	CPtrList m_pSceneList;  //场景链表
	Connection  * m_connection;


	BOOL  m_bFlagAmq;    //amq连接
	BOOL  m_bFlagSend;	//推送
	BOOL  m_bFlagStop;
	CLogFile m_log;
	int  m_nStateus;

//	CStringList m_cslitItem;
	CString m_csItem;
	int	m_nItemIndex;//点类型索引
	CString m_csItemEnglish;//点类型英文名称
	CString m_csTypeNum;//点类型编号
	CString m_csAlaCause;//告警原因
	CString m_csAlaColor;//告警颜色
	CString	m_csAlaType;  //告警类型 1. 资产告警 2.动环告警 3.网管告警
	CString	m_csAlaLevel; //告警等级

	COLORREF m_colorAla;//告警RGB 颜色值

	long	m_nAlaCount;//DB中报警记录条数。

	long	m_nTagType;//数据库点类型
	BOOL	m_bSendAlarm;//是否发送报警数据
	//Amq  amq[2]; 
public:
	void ThreadBegin(void);
	void UpdateList(void);
	void NodeToFile(void);
	void NodeFromFile(void);
	void CmdLineHandle(void);
	void DoWork(Scene_para* pS,int tn,string StrQueue,Session* m_session, MessageProducer* m_producer);
	void InitActiveMQ(void);
	void MonitorJsonString(LPVOID pS,LPVOID pB,LPVOID pF,LPVOID pR,PVOID pD,LPVOID pT,double pv,int tn);
	void AlarmJsonString(LPVOID pS,LPVOID pB,LPVOID pF,LPVOID pR,LPVOID pD,LPVOID pT,double pv,int tn);
	string CStrToStr(CString str);
	void UpDateTree(void);
	void SearchNode(HTREEITEM hTree);
	void SendTextMessage(string StrQueue,int tn,Session* m_session, MessageProducer* m_producer);
	void GetSetting(void);
	void UpDateItem(CString type = _T(""));
	string UnicodetoUTF_8(string &pstrOut);
	void CInterface3DDlg::CreateTray(void);
	void CombAddString(emComb combAdd,CString csItemName);
	void UpDateFile();
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLbnSelchangeListAllNode();
	afx_msg void OnLbnSelchangeListCurNode();
    afx_msg void OnBnClickedDelete();   ///删除
	afx_msg void OnCbnSelchangeComboIndex();
	afx_msg void OnBnClickedButton1();
	afx_msg LRESULT OnBnTray(WPARAM wparam,LPARAM lparam);
	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	void StatusChangeDbcommocxctrlfc71(long Status);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	afx_msg void OnBnClickedButton2();
	afx_msg void OnCbnSelchangeComboInst();
	void AddPointState(LPVOID pT);
	afx_msg void OnBnClickedBtnAdd();
	
	afx_msg void OnBnClickedBtnItemdel();
	afx_msg void OnClose();
	CMFCButton m_MfcBtnAlmColor;
	afx_msg void OnBnClickeBtnAlmColor();
	afx_msg void OnCustomdrawTreeScene(NMHDR *pNMHDR, LRESULT *pResult);

	/****************** hjq *********************/
public:
	CComboBox	m_cbIODeviceName;	//IO设备名称
	CString		m_csIODeviceName;
	CComboBox	m_cbSourceID;		//来源标识
	CString		m_csSourceID;
	CComboBox	m_cbOriAlarmLevel;	//原始告警级别
	CString		m_csOriAlarmLevel;
	CComboBox	m_cbAlarmLevel;		//告警级别
	CString		m_csAlarmLevel;
	CComboBox	m_cbCompress;		//压缩标识
	CString		m_csCompress;
	CComboBox	m_cbIndexEx;		//指标实例
	CString		m_csIndexEx;
	void AlarmChangeDbcommocxctrlfc71(BOOL bInit, long lAlarmCount, const VARIANT& AlarmData);
	CStringList m_cslistTagName;

	CList<AlarmTagInfo,AlarmTagInfo> m_AlarmTagInfoList;		//报警点链表
	AlarmTagInfo m_AlarmTagInfo;
};
