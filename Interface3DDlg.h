
// Interface3DDlg.h : ͷ�ļ�
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

//comb�ؼ�ö��
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

//�½�����������
typedef struct SCENE_PARA
{
	CString csName ;
	CPtrList pBuildList;
}Scene_para;

//¥��
typedef struct BUILD_PARA
{
	CString csName ;
	CPtrList pFloorList;
}Build_para;

//¥��
typedef struct FLOOR_PARA
{
	CString csName ;
	CPtrList pRoomList;
}Floor_para;

//����
typedef struct ROOM_PARA
{
	CString csName ;
	CPtrList pDeviceList;
}Room_para;

//DB  �豸������
typedef struct DEVICE
{
	CString csName;       //�豸����
	CString csID;	       //id
	CPtrList  pPointList;
}Device;

//DB  �豸������
typedef struct POINT_DB
{
	CString csName;			//����
	CString csPath;			//���ݿ�ڵ���
	CString csPointType;    //������  �����ͼ��
	CString csBigType;		//�豸����
	CString csBigTypeNum;	//�豸���ͱ��
	CString csBigTypeEng;	//�豸����Ӣ����
	CString csType;			//����    �¶� ʪ��
	CString csChildId;
	CString csDataType;   //��ֵ  ״̬
	CString csPara;		 //������pvֵ
	CString csContext;		 //������pvֵ
	CString csAlaCause;		//����ԭ��
	CString csAlaColor;		//������ɫ
	CString csAlaType;		//��������
	CString csAlaLevel;		//�����ȼ�
	int nState;//����״̬

	/************** hjq **********************/
	CString	csIODeviceName;	//IO�豸����
	CString	csSourceID;		//��Դ��ʶ
	CString	csOriAlarmLevel;//ԭʼ�澯����	
	CString	csAlarmLevel;	//�澯����	
	CString	csCompress;		//ѹ����ʶ	
	CString	csIndexEx;		//ָ��ʵ��
	CString csLongTagName;
	CString csParDESC;		//������+����desc
	CString csTagDESC;		//������
}Point_DB;

typedef struct AMQ
{
	static Connection  * connection;  //����
	static Session * session; //�Ự
	Destination  * destination;  //Ŀ��
	MessageProducer * producer; //������
	MessageConsumer * consumer;	//������
}Amq;

struct AlarmTagInfo
{
	BOOL bFlag;				//������־λ
	CString csTagName;	//����
	BOOL bAlarmTagType;	//����������. 0:ģ����. 1:������
	BOOL bLimitHiFlag;	//ģ������ֵ��־λ
	double dbLimitHi;		//ģ������ֵ
	BOOL bLimitLoFlag;	//ģ������ֵ��־λ
	double dbLimiLo;		//ģ������ֵ
	BOOL bDigType;		//���ֵ�����	0:�ر�->��. 1:��->�ر�
	double dbValue;			//����ֵ
	/*AlarmTagInfo()
	{
		memset(this,0,sizeof(AlarmTagInfo));
	}
	~AlarmTagInfo(){}*/
};


// CInterface3DDlg �Ի���
class CInterface3DDlg : public CDialogEx
{
// ����
public:
	CInterface3DDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CInterface3DDlg();
	int  m_threadNumber;
// �Ի�������
	enum { IDD = IDD_INTERFACE3D_DIALOG };
	enum {WORK_DRAW = 0,WORK_VIEW};
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
public:  
	CDbcommocxctrlfc71 m_dbCom;
	CString m_csNodeName; //��ʾ�ڵ������
	//CString m_csNodeName; //��ʾ�ڵ��id
	CListBox m_clAllNode;
	CListBox m_clCurNode;
	CComboBox m_cbIndex;
	CComboBox m_cbPointType;
	CComboBox m_cbType;
	CComboBox m_cbDataType;

	CComboBox m_cbSceneName;//������
	CComboBox m_cbDeviceName;//�豸��
	CComboBox m_cbDeviceID;//�豸ID
	CComboBox m_cbBuildName;//¥��
	CComboBox m_cbFloorName;//¥��
	CComboBox m_cbRoomName;//����
	CComboBox m_cbAlaCause;//�澯ԭ��
	CComboBox m_cbAlaType;//�澯����

	CString	m_csBuildName;//¥����
	CString	m_csFloorName;//¥����
	CString m_csRoomName;//������

	CStringList  m_ctList;
	Thread_para	m_trPara;

	NOTIFYICONDATA m_nid;  //����

	CString m_csIndex;   //�豸����
	CString m_csContext;  //��������
	CString m_csSceneName;//��������
	CString m_csDeviceName;
	CString m_csDeviceId;//����id
	CString m_csPointName;
	CString m_csChildId;
	CString m_csPath;
	CString m_csPointType;
	CString m_csType;
	CString m_csDataType;
	int m_nTime;//����ʱ����
	CString m_csIP;
	CString m_csPort;
	Json::Value Jroot_M[20];//JSON STRING 
	Json::Value Jroot_A[20];//JSON STRING 
	CTreeCtrl m_TreeCtrl;
	//BOOL m_bIsAlarm;  //�Ƿ񱨾�
	CPtrList m_pSceneList;  //��������
	Connection  * m_connection;


	BOOL  m_bFlagAmq;    //amq����
	BOOL  m_bFlagSend;	//����
	BOOL  m_bFlagStop;
	CLogFile m_log;
	int  m_nStateus;

//	CStringList m_cslitItem;
	CString m_csItem;
	int	m_nItemIndex;//����������
	CString m_csItemEnglish;//������Ӣ������
	CString m_csTypeNum;//�����ͱ��
	CString m_csAlaCause;//�澯ԭ��
	CString m_csAlaColor;//�澯��ɫ
	CString	m_csAlaType;  //�澯���� 1. �ʲ��澯 2.�����澯 3.���ܸ澯
	CString	m_csAlaLevel; //�澯�ȼ�

	COLORREF m_colorAla;//�澯RGB ��ɫֵ

	long	m_nAlaCount;//DB�б�����¼������

	long	m_nTagType;//���ݿ������
	BOOL	m_bSendAlarm;//�Ƿ��ͱ�������
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
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLbnSelchangeListAllNode();
	afx_msg void OnLbnSelchangeListCurNode();
    afx_msg void OnBnClickedDelete();   ///ɾ��
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
	CComboBox	m_cbIODeviceName;	//IO�豸����
	CString		m_csIODeviceName;
	CComboBox	m_cbSourceID;		//��Դ��ʶ
	CString		m_csSourceID;
	CComboBox	m_cbOriAlarmLevel;	//ԭʼ�澯����
	CString		m_csOriAlarmLevel;
	CComboBox	m_cbAlarmLevel;		//�澯����
	CString		m_csAlarmLevel;
	CComboBox	m_cbCompress;		//ѹ����ʶ
	CString		m_csCompress;
	CComboBox	m_cbIndexEx;		//ָ��ʵ��
	CString		m_csIndexEx;
	void AlarmChangeDbcommocxctrlfc71(BOOL bInit, long lAlarmCount, const VARIANT& AlarmData);
	CStringList m_cslistTagName;

	CList<AlarmTagInfo,AlarmTagInfo> m_AlarmTagInfoList;		//����������
	AlarmTagInfo m_AlarmTagInfo;
};
