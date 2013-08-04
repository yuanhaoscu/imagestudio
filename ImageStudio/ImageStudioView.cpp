// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// ImageStudioView.cpp : CImageStudioView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "ImageStudio.h"
#endif

#include "ImageStudioDoc.h"
#include "ImageStudioView.h"
#include "ImageManager.h"
#include "ImageYH.h"
#include "MainFrm.h"
#include "MfcClassManager.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageStudioView

IMPLEMENT_DYNCREATE(CImageStudioView, CScrollView)

BEGIN_MESSAGE_MAP(CImageStudioView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageStudioView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CImageStudioView 构造/析构
CImageStudioView *p_view=nullptr;

CImageStudioView::CImageStudioView()
{
	// TODO: 在此处添加构造代码
	
	p_view=this;
	Singleton<MfcClassManager>::GetInstance()->SetViewPtr(this);
}

CImageStudioView::~CImageStudioView()
{
}

BOOL CImageStudioView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CImageStudioView 绘制

void CImageStudioView::OnDraw(CDC* pDC)
{
	CImageStudioDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码
	shared_ptr<ImageYH> image=Singleton<ImageManager>::GetInstance()->GetOriginalImage();
	double zoom=Singleton<ImageManager>::GetInstance()->GetZoomNumber();
	
	if(!image->IsNull())
	{
		CRect rect;
		GetClientRect(&rect);
		rect.right = image->GetWidth();
		rect.bottom = image->GetHeight();
		CSize size = CSize(int(rect.right*zoom), int(rect.bottom*zoom));
		
		::SetStretchBltMode(pDC->m_hDC,HALFTONE);
		::SetBrushOrgEx(pDC->m_hDC,0,0,NULL);

		image->Draw(pDC->m_hDC,rect,zoom);
	    SetScrollSizes(MM_TEXT,size);
	}
}

void CImageStudioView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
	//Singleton<ViewManager>::GetInstance();
	//Singleton<ViewManager>::GetInstance()->p_view=this;
	
	
	
}


// CImageStudioView 打印


void CImageStudioView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageStudioView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CImageStudioView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CImageStudioView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CImageStudioView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImageStudioView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImageStudioView 诊断

#ifdef _DEBUG
void CImageStudioView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageStudioView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageStudioDoc* CImageStudioView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageStudioDoc)));
	return (CImageStudioDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageStudioView 消息处理程序


void CImageStudioView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	
}


void CImageStudioView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nChar==VK_SPACE)
	{
		Singleton<ImageManager>::GetInstance()->GetOriginalImage()->ChangeDrawMode();
	   Invalidate();
	}
	
	
	CScrollView::OnChar(nChar, nRepCnt, nFlags);
}
void CImageStudioView::ReDraw()
{
	Invalidate();
}

void CImageStudioView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
/*	CImage *img=Singleton<ImageManager>::GetInstance()->GetOriginalImage()->GetImage();
	if(!img->IsNull())
	{
		CDC* pdc=CDC::FromHandle(img->GetDC());
		pdc->MoveTo(point);
		img->ReleaseDC();
	}*/
	

	
	CScrollView::OnLButtonDown(nFlags, point);
}


void CImageStudioView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
/*	CImage *img=Singleton<ImageManager>::GetInstance()->GetOriginalImage()->GetImage();
	if(!img->IsNull())
	{
	  CDC* pdc=CDC::FromHandle(img->GetDC());
	  pdc->SelectObject(CPen());
	  pdc->LineTo(point);

	  img->ReleaseDC();
	}*/
	CScrollView::OnLButtonUp(nFlags, point);
}


void CImageStudioView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPoint pt = point;
	pt.x = point.x + GetScrollPos(SB_HORZ);
	pt.y = point.y + GetScrollPos(SB_VERT);
	double zoom=Singleton<ImageManager>::GetInstance()->GetZoomNumber();
	pt.x = int(pt.x /zoom);
	pt.y = int(pt.y /zoom);
	CString str;
	str.Format("坐标：X:%4d,Y:%4d",pt.x,pt.y);
	Singleton<MfcClassManager>::GetInstance()->GetframePtr()->m_wndStatusBar.SetPaneText(1,str);
	CDC *pDC = GetDC();
	COLORREF color = pDC->GetPixel(point);
	ReleaseDC(pDC);
	str.Format("颜色值 R:%4d G:%4d B:%4d",GetRValue(color),GetBValue(color),GetBValue(color));
	Singleton<MfcClassManager>::GetInstance()->GetframePtr()->m_wndStatusBar.SetPaneText(2,str);

	shared_ptr<ImageYH> image=Singleton<ImageManager>::GetInstance()->GetOriginalImage();
	if(!image->IsNull())
	{
		str.Format("图片大小: %6d * %6d ",image->GetWidth(),image->GetHeight());
		Singleton<MfcClassManager>::GetInstance()->GetframePtr()->m_wndStatusBar.SetPaneText(3,str);
	}
	CScrollView::OnMouseMove(nFlags, point);
}


void CImageStudioView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	CScrollView::OnTimer(nIDEvent);
}


BOOL CImageStudioView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	return CScrollView::OnEraseBkgnd(pDC);
}
