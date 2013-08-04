// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// ImageStudioView.cpp : CImageStudioView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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

// CImageStudioView ����/����
CImageStudioView *p_view=nullptr;

CImageStudioView::CImageStudioView()
{
	// TODO: �ڴ˴���ӹ������
	
	p_view=this;
	Singleton<MfcClassManager>::GetInstance()->SetViewPtr(this);
}

CImageStudioView::~CImageStudioView()
{
}

BOOL CImageStudioView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CScrollView::PreCreateWindow(cs);
}

// CImageStudioView ����

void CImageStudioView::OnDraw(CDC* pDC)
{
	CImageStudioDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
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
	// TODO: �������ͼ�ĺϼƴ�С
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
	//Singleton<ViewManager>::GetInstance();
	//Singleton<ViewManager>::GetInstance()->p_view=this;
	
	
	
}


// CImageStudioView ��ӡ


void CImageStudioView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageStudioView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CImageStudioView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CImageStudioView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CImageStudioView ���

#ifdef _DEBUG
void CImageStudioView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageStudioView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageStudioDoc* CImageStudioView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageStudioDoc)));
	return (CImageStudioDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageStudioView ��Ϣ�������


void CImageStudioView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	
}


void CImageStudioView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CPoint pt = point;
	pt.x = point.x + GetScrollPos(SB_HORZ);
	pt.y = point.y + GetScrollPos(SB_VERT);
	double zoom=Singleton<ImageManager>::GetInstance()->GetZoomNumber();
	pt.x = int(pt.x /zoom);
	pt.y = int(pt.y /zoom);
	CString str;
	str.Format("���꣺X:%4d,Y:%4d",pt.x,pt.y);
	Singleton<MfcClassManager>::GetInstance()->GetframePtr()->m_wndStatusBar.SetPaneText(1,str);
	CDC *pDC = GetDC();
	COLORREF color = pDC->GetPixel(point);
	ReleaseDC(pDC);
	str.Format("��ɫֵ R:%4d G:%4d B:%4d",GetRValue(color),GetBValue(color),GetBValue(color));
	Singleton<MfcClassManager>::GetInstance()->GetframePtr()->m_wndStatusBar.SetPaneText(2,str);

	shared_ptr<ImageYH> image=Singleton<ImageManager>::GetInstance()->GetOriginalImage();
	if(!image->IsNull())
	{
		str.Format("ͼƬ��С: %6d * %6d ",image->GetWidth(),image->GetHeight());
		Singleton<MfcClassManager>::GetInstance()->GetframePtr()->m_wndStatusBar.SetPaneText(3,str);
	}
	CScrollView::OnMouseMove(nFlags, point);
}


void CImageStudioView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	CScrollView::OnTimer(nIDEvent);
}


BOOL CImageStudioView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	return CScrollView::OnEraseBkgnd(pDC);
}
