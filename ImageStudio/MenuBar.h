#ifndef MENUBAR_H
#define MENUBAR_H

class MenuBar:public CCmdTarget
{
	DECLARE_DYNAMIC(MenuBar)
public:
	MenuBar();
	virtual ~MenuBar();
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	
	void CreateBar(CWnd * m_Parent);
	void AddButtons();
	

	DECLARE_MESSAGE_MAP()
	afx_msg void OnZoomin();
	afx_msg void OnZoomout();
	afx_msg void OnRealsize();
	afx_msg void OnOstu();
	afx_msg void OnFilterWave();
	afx_msg void OnMeanshift();
	afx_msg void OnDiceFilter();
	afx_msg void OnKmeans();
};



#endif