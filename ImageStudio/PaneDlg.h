#pragma once


// PaneDlg 对话框
#include "resource.h"
class PaneDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PaneDlg)

public:
	PaneDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PaneDlg();

// 对话框数据
	enum { IDD = IDD_PANEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_output_txt;
	CString m_file_name;
};
