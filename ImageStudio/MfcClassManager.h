#ifndef MFC_CLASS_MANAGER_H
#define MFC_CLASS_MANAGER_H
class CMainFrame;
class CImageStudioDoc;
class CImageStudioView;

class MfcClassManager
{
public:
	MfcClassManager();
	~MfcClassManager();
	void SetViewPtr(CImageStudioView *pview)
	 {
		 pview_=pview;
	 };
	void SetDocPtr(CImageStudioDoc *pdoc)
	{
		pdoc_=pdoc;
	};
	void SetframePtr(CMainFrame *pfrm)
	{
		pfrm_=pfrm;
	};

	CImageStudioView * GetViewPtr()
	{
		return pview_;
	};
	CImageStudioDoc * GetDocPtr()
	{
		return pdoc_;
	};
	CMainFrame * GetframePtr()
	{
		return pfrm_;
	};

private:
    CMainFrame *pfrm_;
	CImageStudioDoc *pdoc_;
	CImageStudioView *pview_;

};

#endif