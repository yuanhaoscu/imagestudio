// PropertyPane.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageStudio.h"
#include "PropertyPane.h"
#include "PaneDlg.h"

// PropertyPane

IMPLEMENT_DYNAMIC(PropertyPane, CDockablePane)

PropertyPane::PropertyPane()
{

}

PropertyPane::~PropertyPane()
{
}


BEGIN_MESSAGE_MAP(PropertyPane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// PropertyPane 消息处理程序




int PropertyPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
//	dlg.Create(IDD_PANEDLG,this);
//	dlg.ShowWindow(SW_SHOW);

	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	CRect rectDummy;
	rectDummy.SetRectEmpty();
	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("未能创建属性网格\n");
		return -1;      // 未能创建
	}
	//属性的设置
	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
	
	return 0;
}


void PropertyPane::OnDestroy()
{
	CDockablePane::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
//	dlg.DestroyWindow();
}


void PropertyPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
		if(m_wndPropList.GetSafeHwnd())
		    {
			   CRect rct;
			   GetClientRect(rct);
		       m_wndPropList.MoveWindow(rct);
		     }
	// TODO: 在此处添加消息处理程序代码
/*	if(dlg.GetSafeHwnd())
		    {
			   CRect rct;
			   GetClientRect(rct);
		       dlg.MoveWindow(rct);
		     }*/
}
