#include "stdafx.h"
#include "ImageYH.h"


ImageYH::ImageYH()
{
	image_=new CImage();
	layer_=new CImage();
	width_=0;
	height_=0;
	draw_mode_=LAYER_ON;
}

ImageYH::ImageYH(const ImageYH&img)
{
	

	image_=new CImage(*(img.image_));
	layer_=new CImage(*(img.layer_));
	width_=img.width_;
	height_=img.height_;
	draw_mode_=LAYER_ON;

}
ImageYH& ImageYH::operator =(const ImageYH&img)
{
	if(this==&img) return *this;

	if(image_!=nullptr)
	{
		if(!image_->IsNull())
		       image_->Destroy();

		delete image_;
	}
	if(layer_!=nullptr)
	{
		if(!layer_->IsNull())
		       layer_->Destroy();

		delete layer_;
	}
	image_=new CImage(*(img.image_));
	layer_=new CImage(*(img.layer_));
	width_=img.width_;
	height_=img.height_;
	draw_mode_=LAYER_ON;
	return *this;
}

ImageYH::~ImageYH()
{
	if(image_!=nullptr)
	{
		if(!image_->IsNull())
			image_->Destroy();
		delete image_;
	}
	if(layer_!=nullptr)
	{
		if(!layer_->IsNull())
			layer_->Destroy();
		delete layer_;
	}
}
bool ImageYH::Load(LPCTSTR filename)
{
	if(!image_->IsNull())
		image_->Destroy();

	if(!layer_->IsNull())
		layer_->Destroy();

	image_->Load(filename);
	

	width_=image_->GetWidth();
	height_=image_->GetHeight();
	
	layer_->Create(width_,height_,24);
	
	return true;


}

bool ImageYH::IsNull()
{
	return image_->IsNull();
}

bool ImageYH::Destroy()
{
	 image_->Destroy();
	 layer_->Destroy();
	 return true;
}

bool ImageYH::Draw(HDC hDestDC,const RECT& rectDest)
{
	COLORREF clr=RGB(0,0,0);
	image_->Draw(hDestDC,rectDest);
//	image_->StretchBlt(hDestDC,rectDest);
	if(draw_mode_)
        layer_->TransparentBlt(hDestDC,rectDest,clr);

	return true;
}

bool ImageYH::Draw(HDC hDestDC, RECT& rectDest,double zoom)
{
	COLORREF clr=RGB(0,0,0);
	rectDest.right=int(rectDest.right*zoom);
	rectDest.bottom=int(rectDest.bottom*zoom);

	image_->Draw(hDestDC,rectDest);

	if(draw_mode_)
		layer_->TransparentBlt(hDestDC,rectDest,clr);

	return true;
}

int ImageYH::GetWidth()
{
	return image_->GetWidth();
}
int ImageYH::GetHeight()
{
	return image_->GetHeight();
}

void ImageYH::SetDrawMode(DrawMode mode)
{
	

	draw_mode_=mode;
}
int ImageYH::GetDrawMode()
{
	return int(draw_mode_);
}
void ImageYH::ChangeDrawMode()
{
	if(draw_mode_==LAYER_ON)
		draw_mode_=LAYER_OFF;
	else
		draw_mode_=LAYER_ON;
}

void ImageYH::ClearLayer()
{
	if(!layer_->IsNull())
	{
		int nrowbyte=layer_->GetPitch();
	   BYTE *pByte=(BYTE*)layer_->GetBits();

	for(int x=0;x<width_;x++)
		for(int y=0;y<height_;y++)
		{
			pByte[y*nrowbyte+x*3]=0;
			pByte[y*nrowbyte+x*3+1]=0;
			pByte[y*nrowbyte+x*3+2]=0;
		}
	}
}
RGBQUAD *ImageYH::colortable=NULL;
RGBQUAD * ImageYH::GetColorTable()
{
	if(colortable==nullptr)
	{
		colortable=new RGBQUAD[256];
		for(int i=0;i<256;i++)
		{
			colortable[i].rgbRed = colortable[i].rgbGreen = colortable[i].rgbBlue = i;
			colortable[i].rgbReserved=0;
		}
		return colortable;
	}
	else
		return colortable;
}