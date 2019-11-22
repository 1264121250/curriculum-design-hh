// DialogMore.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Gobang_FiveChess.h"
#include "DialogMore.h"
#include "afxdialogex.h"


// CDialogMore �Ի���

IMPLEMENT_DYNAMIC(CDialogMore, CDialogEx)//ȷ������ʱ����������һ����

CDialogMore::CDialogMore(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogMore::IDD, pParent)
{
    m_pChess    = NULL;
}

CDialogMore::~CDialogMore()
{
}

void CDialogMore::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_AI, m_comboxAI);
    DDX_Control(pDX, IDC_COMBO_VS_MODE, m_comboxVSMode);
}

//�꿪ʼ��Ϣӳ�䣬Ϊÿ����Ϣ����������һ����ڣ�
BEGIN_MESSAGE_MAP(CDialogMore, CDialogEx)
    ON_BN_CLICKED(IDOK, &CDialogMore::OnBnClickedOk)//�û�������ťʱ,�򸸶�������Ϣ
END_MESSAGE_MAP()


// CDialogMore ��Ϣ�������,,
void CDialogMore::OnBnClickedOk()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    if(m_pChess)
    {
        m_pChess->SetAIDepth(m_comboxAI.GetCurSel());//��ѡ�����AI�ȼ�

        switch(m_comboxVSMode.GetCurSel())
        {
        case    0:
            m_pChess->SetVSMode(PERSON_VS_MACHINE);//�˻���ս
            break;
        case    1:
            m_pChess->SetVSMode(PERSON_VS_PERSON);//���˶�ս
            break;

        default:
            break;
        }       
    }
   
    CDialogEx::OnOK();//ȷ�ϼ���ʼ
}


BOOL CDialogMore::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��       
    m_comboxAI.SetCurSel(2);              // �м�
    m_comboxVSMode.SetCurSel(0);    // �˻�
    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}

//// ��������ָ��
void    CDialogMore::SetChess(CChess  *pChess)
{
    m_pChess    = pChess;
}