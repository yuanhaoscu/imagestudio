// PropertyPane.cpp : ʵ���ļ�
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



// PropertyPane ��Ϣ�������




int PropertyPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
//	dlg.Create(IDD_PANEDLG,this);
//	dlg.ShowWindow(SW_SHOW);

	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	CRect rectDummy;
	rectDummy.SetRectEmpty();
	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("δ�ܴ�����������\n");
		return -1;      // δ�ܴ���
	}
	//���Ե�����
	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
	
	return 0;
}


void PropertyPane::OnDestroy()
{
	CDockablePane::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
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
	// TODO: �ڴ˴������Ϣ����������
/*	if(dlg.GetSafeHwnd())
		    {
			   CRect rct;
			   GetClientRect(rct);
		       dlg.MoveWindow(rct);
		     }*/
}
