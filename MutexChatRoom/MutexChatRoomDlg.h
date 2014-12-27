
// MutexChatRoomDlg.h : ͷ�ļ�
//

#pragma once

#define WM_RECVDATA WM_USER+1
// CMutexChatRoomDlg �Ի���
class CMutexChatRoomDlg : public CDialogEx
{
private:
	SOCKET m_socket;
	//���ڽ��������̴߳��ݲ����Ľṹ��
	struct RECVPARAM
	{
		SOCKET socket;
		HWND hwnd;
	};
// ����
public:
	CMutexChatRoomDlg(CWnd* pParent = NULL);	// ��׼���캯��
	BOOL InitSocket();
	static DWORD WINAPI RecvProc(LPVOID lpParameter);
// �Ի�������
	enum { IDD = IDD_MUTEXCHATROOM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧�� 



// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	//�Զ������Ϣ��Ӧ��������������
	LRESULT afx_msg OnRecvData(WPARAM wParam, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangerecvEdit2();
};
