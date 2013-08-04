#include "stdafx.h"
#include "ImageManager.h"
#include "ImageYH.h"

ImageManager::ImageManager()
{
	orignal_image_=shared_ptr<ImageYH>( new ImageYH());
	zoom_=1.0;
	file_path_="";
}
ImageManager::~ImageManager()
{
	

}

shared_ptr<ImageYH> ImageManager::GetOriginalImage()
{
	return orignal_image_;
}
void ImageManager::LoadImageFile(CString filename)
{
	CString strTemp=filename.Right(3);
	if (strTemp=="jpg" || strTemp=="bmp" || strTemp=="JPG" || strTemp=="BMP")
	{
		file_path_=filename;
		orignal_image_->Load(filename);
	}
	else
	{
		AfxMessageBox(_T("只支持jpg或者bmp图，谢谢！"));
		return ;
	}
	
	


}
double ImageManager::GetZoomNumber()
{
	return zoom_;
}
void  ImageManager::SetZoomNumber(double zoom)
{
	zoom_=zoom;
}