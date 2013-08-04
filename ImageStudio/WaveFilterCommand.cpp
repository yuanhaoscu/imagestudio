#include "stdafx.h"
#include "WaveFilterCommand.h"
#include "ImageYH.h"
#include <math.h>

WaveFilterCommand::WaveFilterCommand(shared_ptr<ImageYH> img,double wave_length,double peroid)
{
	image_=img;
	wave_length_=wave_length;
	peroid_=peroid;
	type_=CommandType::WAVE_FILTER;

}
WaveFilterCommand::~WaveFilterCommand()
{

}
void WaveFilterCommand::RunCommand()
{
	if(image_==nullptr) return;
	if(image_->IsNull()) return;

	int w=image_->GetImage()->GetWidth();
	int h=image_->GetImage()->GetHeight();
	int nrowsrc=image_->GetImage()->GetPitch();
	int nrowdes=image_->GetLayer()->GetPitch();

	BYTE *src=(BYTE*)image_->GetImage()->GetBits();
	BYTE *des=(BYTE*)image_->GetLayer()->GetBits();
	WaveGo(src,des,w,h,nrowsrc,nrowdes);

}
void WaveFilterCommand::WaveGo(BYTE *src,BYTE *des,int w,int h,int nrowsrc,int nrowdes)
{
	int xoffset=0;
	int yoffset=0;

	for(int x=0;x<w;x++)
		for(int y=0;y<h;y++)
		{
			des[y*nrowdes+x*3]=0;
			des[y*nrowdes+x*3+1]=0;
			des[y*nrowdes+x*3+2]=0;

			xoffset = (int)((double)wave_length_ * sin(2.0 * 3.14 * (float)x / peroid_));  
			yoffset = (int)((double)wave_length_ * cos(2.0 * 3.14 * (float)y / peroid_));
			xoffset+=y;
			yoffset+=x;

			if(xoffset>=0&&xoffset<h&&yoffset>0&&yoffset<w)
			{
				des[xoffset*nrowdes+yoffset*3]=src[y*nrowsrc+x*3]+1;
				des[xoffset*nrowdes+yoffset*3+1]=src[y*nrowsrc+x*3+1]+1;
				des[xoffset*nrowdes+yoffset*3+2]=src[y*nrowsrc+x*3+2]+1;
			}
			else
			{
				
			}
		}
}