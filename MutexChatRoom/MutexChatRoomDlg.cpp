
// MutexChatRoomDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MutexChatRoom.h"
#include "MutexChatRoomDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define MAXN 100000
#define WM_RECVDATA WM_USER+1

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMutexChatRoomDlg �Ի���



CMutexChatRoomDlg::CMutexChatRoomDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMutexChatRoomDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMutexChatRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMutexChatRoomDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CMutexChatRoomDlg ��Ϣ�������

BOOL CMutexChatRoomDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MINIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	InitSocket();

	RECVPARAM *pRecvParam = new RECVPARAM;
	//Ҫ���ݸ����������̵߳��׽��ֺʹ��ھ��

	pRecvParam->socket=m_socket;
	//�����봰���йص��඼��һ�����ݳ�Ա��m_hWnd�����������������صĴ��ھ��
	pRecvParam->hwnd = m_hWnd;

	//���������߳�
	//�߳���Ӧ�������ڴ����̺߳���ִ�е�ʱ���Զ����õģ����Բ��ܴ���Ϊһ����Ա����
	//��Ϊ��Ա�����Ǳ���Ҫ�ö��������õġ�Ϊ�˱�֤��������̵ķ�װ�ԣ����Խ������ĺ�������Ϊ��̬��Ա����
	//��̬��Ա�ĺ���ֻ�����࣬�������κζ���
	//֮�������µ����߳���ִ�н������ݣ�������Ϊ�������ݵĺ������û�н��ܵ����ݻ�������ʹ�������������ֹͣ���У��������ʹ���ն�Ҳ�Ƿ��Ͷˣ��κ�һ���ֵĹ��ܶ�����Ӱ�쵽����һ����
	HANDLE hThread = CreateThread(NULL,0,RecvProc,(LPVOID)pRecvParam,0,NULL);
	CloseHandle(hThread);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMutexChatRoomDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMutexChatRoomDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMutexChatRoomDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CMutexChatRoomDlg::InitSocket()
{
	//�����׽��֣�ʹ��UDPЭ���е����ݱ��׽���
	m_socket = socket(AF_INET,SOCK_DGRAM,0);

	//����׽����Ƿ񴴽�ʧ��
	if(INVALID_SOCKET == m_socket) 
	{
		MessageBox("�׽��ִ���ʧ��");
		return FALSE;
	}
	//
	SOCKADDR_IN addrSock;
	addrSock.sin_family = AF_INET;
	addrSock.sin_port = htons(6000);
	//��ip��ַ��Ϊ���з�������������ip��ַ��Ҳ����˵������ͨ�����з�������������ip��ַ�����ܺͷ�������
	addrSock.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	int retval;
	//�󶨶˿�
	retval = bind(m_socket,(SOCKADDR*)&addrSock,sizeof(SOCKADDR));
	if(retval == SOCKET_ERROR)
	{
		closesocket(m_socket);
		MessageBox("��ʧ��");
		return FALSE;
	}
	return TRUE;

}

DWORD WINAPI CMutexChatRoomDlg::RecvProc(LPVOID lpParameter)
{
	//��ȡ���ݽ����ĺ���
	SOCKET sock = ((RECVPARAM*)lpParameter)->socket;
	HWND hwnd = ((RECVPARAM*)lpParameter)->hwnd;
	delete lpParameter;

	//��Ҫ�����洢���ͷ��󶨵ĵ�ַ��Ϣ
	SOCKADDR_IN addrFrom;
	int len = sizeof(SOCKADDR);
	char recvbuff[MAXN] = {0};
	char tempbuff[MAXN] = {0};

	int retval;

	//��ΪҪһֱ׼���ڽ������ݣ����ԣ�����������Ҫ���ܴ���Ҫ���ϵ�ѭ��ִ��
	while(TRUE)
	{
		//���ܷ���������
		retval = recvfrom(sock,recvbuff,MAXN,0,(SOCKADDR*)&addrFrom,&len);
		if(SOCKET_ERROR == retval)
		{
			break;
		}
		//��ʽ���洢���뵽tempbuff��������
		sprintf(tempbuff,"%s˵�� %s",inet_ntoa(addrFrom.sin_addr),0,(LPARAM)recvbuff);

		::PostMessage(hwnd,WM_RECVDATA,0,(LPARAM)tempbuff);
	}
}