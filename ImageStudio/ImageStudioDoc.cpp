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

// ImageStudioDoc.cpp : CImageStudioDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "ImageStudio.h"
#endif

#include "ImageStudioDoc.h"
#include "ImageStudioView.h"
#include <propkey.h>
#include "MainFrm.h"
#include "ImageManager.h"
#include "ImageYH.h"
#include "MfcClassManager.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageStudioDoc

IMPLEMENT_DYNCREATE(CImageStudioDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageStudioDoc, CDocument)
	ON_COMMAND(ID_FILE_OPEN, &CImageStudioDoc::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE_AS, &CImageStudioDoc::OnFileSaveAs)
END_MESSAGE_MAP()


// CImageStudioDoc ����/����

CImageStudioDoc::CImageStudioDoc()
{
	// TODO: �ڴ����һ���Թ������
	Singleton<MfcClassManager>::GetInstance()->SetDocPtr(this);

}

CImageStudioDoc::~CImageStudioDoc()
{
}

BOOL CImageStudioDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CImageStudioDoc ���л�

void CImageStudioDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CImageStudioDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CImageStudioDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CImageStudioDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageStudioDoc ���

#ifdef _DEBUG
void CImageStudioDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageStudioDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}

#endif //_DEBUG

void CImageStudioDoc::OnFileOpen()
{
	
	
	CFileDialog dlg(TRUE);
	if(IDOK!=dlg.DoModal())
		return;
	Singleton<ImageManager>::GetInstance()->LoadImageFile(dlg.GetPathName());
	UpdateAllViews(NULL);

}



void CImageStudioDoc::OnFileSaveAs()
{
	// TODO: �ڴ���������������
	
	CFileDialog dlg(FALSE,"jpg","���ͼ-1");
	if(IDOK!=dlg.DoModal())
		return;
	CImage *img=Singleton<ImageManager>::GetInstance()->GetOriginalImage()->GetImage();
	img->Save(dlg.GetPathName());
}
