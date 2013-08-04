#include "Stdafx.h"
#include "MenuBar.h"
#include "ImageStudio.h"
#include "resource.h"
#include "ImageStudioView.h"
#include "ImageYH.h"

#include "ImageManager.h"
#include "BaseCommand.h"
#include "OstuCommand.h"
#include "WaveFilterCommand.h"
#include "MeanShiftCommand.h"
#include "DicePaintFilterCommand.h"
#include "transaction_queue.h"
#include "Functions-inl.h"
#include "KmeansCommand.h"
#include "TestCommand.h"
IMPLEMENT_DYNAMIC(MenuBar, CCmdTarget)

MenuBar::MenuBar()
{
	
}
MenuBar::~MenuBar()
{
	
}
void MenuBar::CreateBar(CWnd * m_Parent)
{
	m_wndRibbonBar.Create(m_Parent);

	AddButtons();
}
void MenuBar::AddButtons()
{
	m_MainButton.SetImage(IDB_MAIN);
	m_MainButton.SetText(_T("\nf"));
	m_MainButton.SetToolTipText(_T("YUANHAO"));
	m_wndRibbonBar.SetApplicationButton(&m_MainButton, CSize (32,32));

	CMFCRibbonMainPanel* pMainPanel = m_wndRibbonBar.AddMainCategory(_T("主面板"), IDB_FILESMALL, IDB_FILELARGE, 
		CSize(16, 16), CSize(32, 32));
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_OPEN, _T("打开"), 1, 1));
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_SAVE_AS, _T("另存为"), 1, 2));
	pMainPanel->AddRecentFilesList(_T("最近打开的文档"));
	pMainPanel->AddToBottom(new CMFCRibbonMainPanelButton(ID_APP_EXIT, _T("退出"), 10));
	// 添加快速访问工具栏命令:
	CList<UINT, UINT> lstQATCmds;
	lstQATCmds.AddTail(ID_FILE_OPEN);
	m_wndRibbonBar.SetQuickAccessCommands(lstQATCmds);
	CMFCRibbonButton* pVisualStyleButton = new CMFCRibbonButton(-1, _T("程序外观"), -1, -1);
	pVisualStyleButton->SetMenu(IDR_THEME_MENU, FALSE /* 无默认命令*/, TRUE /* 右对齐*/);
	m_wndRibbonBar.AddToTabs(pVisualStyleButton);
	/////////////////////////////////////////////////////////////
	CMFCRibbonCategory* pToolCategory = m_wndRibbonBar.AddCategory(_T("视图"), IDB_WRITESMALL, IDB_WRITELARGE);
	CMFCRibbonPanel* pToolPane11 = pToolCategory->AddPanel(_T("查看"));
	pToolPane11->Add(new CMFCRibbonButton(ID_ZOOMIN, _T("放大"), -1, 0));
	pToolPane11->Add(new CMFCRibbonButton(ID_ZOOMOUT, _T("缩小"), -1, 1));
	pToolPane11->Add(new CMFCRibbonButton(ID_REALSIZE, _T("原图大小"), -1, 2));
	////////////////////////////////////////////////////////////
	CMFCRibbonCategory* pProcessCategory = m_wndRibbonBar.AddCategory(_T("图像处理"), IDB_WRITESMALL, IDB_WRITELARGE);
	CMFCRibbonPanel* pToolPane21= pProcessCategory ->AddPanel(_T("目标提取"));
	pToolPane21->Add(new CMFCRibbonButton(ID_OSTU, _T("OSTU二值化"), -1, 0));
	pToolPane21->Add(new CMFCRibbonButton(ID_MEANSHIFT, _T("MeanShift"), -1, 1));
	pToolPane21->Add(new CMFCRibbonButton(ID_KMEANS, _T("K_Means"), -1, 2));
	////////////////////////////////////////////////////////////
	CMFCRibbonCategory* pFilterCategory = m_wndRibbonBar.AddCategory(_T("滤镜"), IDB_WRITESMALL, IDB_WRITELARGE);
	CMFCRibbonPanel* pToolPane31= pFilterCategory ->AddPanel(_T("滤镜"));
	pToolPane31->Add(new CMFCRibbonButton(ID_FILTER_WAVE, _T("波纹化"), -1, 0));
	pToolPane31->Add(new CMFCRibbonButton(ID_DICE_FILTER, _T("测试"), -1, 1));

}
BEGIN_MESSAGE_MAP(MenuBar, CCmdTarget)
	ON_COMMAND(ID_ZOOMIN, &MenuBar::OnZoomin)
	ON_COMMAND(ID_ZOOMOUT, &MenuBar::OnZoomout)
	ON_COMMAND(ID_REALSIZE, &MenuBar::OnRealsize)
	ON_COMMAND(ID_OSTU, &MenuBar::OnOstu)
	ON_COMMAND(ID_FILTER_WAVE, &MenuBar::OnFilterWave)
	ON_COMMAND(ID_MEANSHIFT, &MenuBar::OnMeanshift)
	ON_COMMAND(ID_DICE_FILTER, &MenuBar::OnDiceFilter)
	ON_COMMAND(ID_KMEANS, &MenuBar::OnKmeans)
END_MESSAGE_MAP()


void MenuBar::OnZoomin()
{
	// TODO: 在此添加命令处理程序代码
	double zoom=Singleton<ImageManager>::GetInstance()->GetZoomNumber();
	zoom*=1.2;
	Singleton<ImageManager>::GetInstance()->SetZoomNumber(zoom);
	p_view->ReDraw();
}


void MenuBar::OnZoomout()
{
	// TODO: 在此添加命令处理程序代码
	double zoom=Singleton<ImageManager>::GetInstance()->GetZoomNumber();
	zoom*=0.8;
	Singleton<ImageManager>::GetInstance()->SetZoomNumber(zoom);
	p_view->ReDraw();
		
}


void MenuBar::OnRealsize()
{
	// TODO: 在此添加命令处理程序代码
	
	
	Singleton<ImageManager>::GetInstance()->SetZoomNumber(1.0);
	p_view->ReDraw();
}



void MenuBar::OnOstu()
{
	// TODO: 在此添加命令处理程序代码
	shared_ptr<ImageYH> img=Singleton<ImageManager>::GetInstance()->GetOriginalImage();
	shared_ptr<BaseCommand> cmd=shared_ptr<OstuCommand>(new OstuCommand(img));
	cmd->RunCommand();
	img->SetDrawMode(ImageYH::LAYER_ON);
	p_view->ReDraw();
}


void MenuBar::OnFilterWave()
{
	// TODO: 在此添加命令处理程序代码
	shared_ptr<ImageYH> img=Singleton<ImageManager>::GetInstance()->GetOriginalImage();
	if(img->GetImage()->GetBPP()!=24)
	{
		AfxMessageBox(_T("对不起，暂时只支持24位的图，稍后会支持的，请等等！"));
		return;
	}
	shared_ptr<BaseCommand> cmd=shared_ptr<WaveFilterCommand>(new WaveFilterCommand(img,10.0,64.0));
	cmd->RunCommand();
	img->SetDrawMode(ImageYH::LAYER_ON);
	p_view->ReDraw();
}


void MenuBar::OnMeanshift()
{
	// TODO: 在此添加命令处理程序代码
    
	shared_ptr<ImageYH> img=Singleton<ImageManager>::GetInstance()->GetOriginalImage();
	if(img->GetImage()->GetBPP()!=24)
	{
		AfxMessageBox(_T("对不起，暂时只支持24位的图，稍后会支持的，请等等！"));
		return;
	}
	img->ClearLayer();
	shared_ptr<BaseCommand> cmd=shared_ptr<MeanShiftCommand>(new MeanShiftCommand(img,100.0,5));
	Singleton<TransactionQueue>::GetInstance()->AddTransaction(cmd);
}


void MenuBar::OnDiceFilter()
{
	// TODO: 在此添加命令处理程序代码

	shared_ptr<ImageYH> image_=Singleton<ImageManager>::GetInstance()->GetOriginalImage();
	shared_ptr<BaseCommand> cmd=shared_ptr<BaseCommand>(new TestCommand(image_));
	cmd->RunCommand();
	
}


void MenuBar::OnKmeans()
{
	// TODO: 在此添加命令处理程序代码
	shared_ptr<ImageYH> image_=Singleton<ImageManager>::GetInstance()->GetOriginalImage();
	shared_ptr<BaseCommand> cmd=shared_ptr<KmeansCommand>(new KmeansCommand(image_));
	Singleton<TransactionQueue>::GetInstance()->AddTransaction(cmd);
}
