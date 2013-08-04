#pragma once


// PropertyPane
#include "PaneDlg.h"

class PropertyPane : public CDockablePane
{
	DECLARE_DYNAMIC(PropertyPane)

public:
	PropertyPane();
	virtual ~PropertyPane();
//	PaneDlg dlg;
	CMFCPropertyGridCtrl m_wndPropList;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


