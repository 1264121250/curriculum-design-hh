
// Gobang_FiveChess.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Gobang_FiveChess.h"
#include "Gobang_FiveChessDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGobang_FiveChessApp

BEGIN_MESSAGE_MAP(CGobang_FiveChessApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CGobang_FiveChessApp ����

CGobang_FiveChessApp::CGobang_FiveChessApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CGobang_FiveChessApp ����

CGobang_FiveChessApp theApp;


// CGobang_FiveChessApp ��ʼ��

BOOL CGobang_FiveChessApp::InitInstance()
{

	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;


	//����MFC�����ע�����ʼ�,���Ѷ�д ini �ļ��ĳ�Ա����ӳ�䵽��дע���
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CGobang_FiveChessDlg dlg;
	m_pMainWnd = &dlg;//�����ڱ���
	INT_PTR nResponse = dlg.DoModal();
	//����������ʹ��Dialogʱ��DoModal()���öԻ���ģ̬
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

