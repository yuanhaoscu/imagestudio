#pragma once


// PaneDlg �Ի���
#include "resource.h"
class PaneDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PaneDlg)

public:
	PaneDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PaneDlg();

// �Ի�������
	enum { IDD = IDD_PANEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_output_txt;
	CString m_file_name;
};
