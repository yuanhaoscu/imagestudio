// PaneDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ImageStudio.h"
#include "PaneDlg.h"
#include "afxdialogex.h"


// PaneDlg �Ի���

IMPLEMENT_DYNAMIC(PaneDlg, CDialogEx)

PaneDlg::PaneDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(PaneDlg::IDD, pParent)
	, m_output_txt(_T(""))
	, m_file_name(_T(""))
{

}

PaneDlg::~PaneDlg()
{
}

void PaneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_output_txt);
	DDX_Text(pDX, IDC_EDIT_FILENAME, m_file_name);
}


BEGIN_MESSAGE_MAP(PaneDlg, CDialogEx)
END_MESSAGE_MAP()


// PaneDlg ��Ϣ�������
