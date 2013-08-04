#include "stdafx.h"
#include "MfcClassManager.h"
#include "ImageStudioDoc.h"
#include "MainFrm.h"
#include "ImageStudioView.h"

MfcClassManager::MfcClassManager()
{
	pfrm_=nullptr;
	pview_=nullptr;
	pdoc_=nullptr;
}
MfcClassManager::~MfcClassManager()
{
	pfrm_=nullptr;
	pview_=nullptr;
	pdoc_=nullptr;
}