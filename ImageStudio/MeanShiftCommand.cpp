#include "stdafx.h"
#include "MeanShiftCommand.h"
#include "ImageYH.h"
#include "ImageStudioView.h"
#include "MainFrm.h"
#include "MfcClassManager.h"
#include "singleton-inl.h"
#include "Functions-inl.h"

MeanShiftCommand::MeanShiftCommand(shared_ptr<ImageYH> img ,double clr_distance,int  radius)
{
	image_=img;
	clr_distance_=clr_distance;
	radius_=radius;
	type_=BaseCommand::CommandType::NOTYPE;
}
MeanShiftCommand::~MeanShiftCommand()
{

}
void MeanShiftCommand::RunCommand()
{
	if(image_==nullptr) return;
	if(image_->IsNull()) return;


	int nrow=image_->GetImage()->GetPitch();
	BYTE * psrc=(BYTE*)image_->GetImage()->GetBits();
	int width=image_->GetImage()->GetWidth();
	int height=image_->GetImage()->GetHeight();
	double *YIQsrc=new double[width*height*3];
	double *YIQdes=new double[width*height*3];
	
	BYTE *bgr=new BYTE[width*height*3];
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
		{
			bgr[y*width*3+x*3]=psrc[y*nrow+x*3];
			bgr[y*width*3+x*3+1]=psrc[y*nrow+x*3+1];
			bgr[y*width*3+x*3+2]=psrc[y*nrow+x*3+2];
		
		}
		RGB2YIQ(bgr,YIQsrc,width,height);
		memcpy(YIQdes,YIQsrc,sizeof(double)*(width*height*3));
		MeanShift(YIQsrc,YIQdes,width,height,clr_distance_,radius_);
        YIQ2RGB(YIQdes,bgr,width,height);
	for(int x=0;x<width;x++)
	    for(int y=0;y<height;y++)
		{
	
			psrc[y*nrow+x*3]=bgr[y*width*3+x*3];
			psrc[y*nrow+x*3+1]=bgr[y*width*3+x*3+1];
			psrc[y*nrow+x*3+2]=bgr[y*width*3+x*3+2];
		}

  delete [] YIQsrc;
  delete [] YIQdes;
  delete [] bgr;
  CommandOver();
}

void MeanShiftCommand::MeanShift(double *YIQsrc,double *YIQdes,int w,int h,double clr_distance,int radius)
{
	int xOld,yOld;
	int tempX,tempY;

	double Yold,Iold,Qold;
	double Ytemp,Itemp,Qtemp;

	int repetition=0;
	double shift=0;
	int radius2=radius*radius;
	double clr_distance2=clr_distance*clr_distance;

	for(int x=0;x<w;x++)
		for(int y=0;y<h;y++)
		{
			tempX=x;
			tempY=y;
			Ytemp=YIQsrc[y*w*3+x*3];
			Itemp=YIQsrc[y*w*3+x*3+1];
			Qtemp=YIQsrc[y*w*3+x*3+2];
			repetition=0;
			do 
			{
				yOld=tempY;
				xOld=tempX;

				Yold=Ytemp;
				Iold=Ytemp;
				Qold=Qtemp;

				int mx=0,my=0;
				double mY=0,mI=0,mQ=0;
				int num=0;


				for(int xx=-radius;xx<=radius;xx++)
				{
					if( ((tempX+xx)>=0) && ((tempX+xx)<w))
					{

						for(int yy=-radius;yy<=radius;yy++)
						{
							if(((tempY+yy)>=0) &&((tempY+yy)<h) )
							{
								if((xx*xx+yy*yy)<=radius2)
								{
									double dY=YIQsrc[(tempY+yy)*w*3+(tempX+xx)*3]-Ytemp;
									double dI=YIQsrc[(tempY+yy)*w*3+(tempX+xx)*3+1]-Itemp;
									double dQ=YIQsrc[(tempY+yy)*w*3+(tempX+xx)*3+2]-Qtemp;
									if((dY*dY+dI*dI+dQ*dQ)<clr_distance2)
									{
										mx=mx+xx+tempX;
										my=my+yy+tempY;
										mY=mY+YIQsrc[(tempY+yy)*w*3+(tempX+xx)*3];
										mI=mI+YIQsrc[(tempY+yy)*w*3+(tempX+xx)*3+1];
										mQ=mQ+YIQsrc[(tempY+yy)*w*3+(tempX+xx)*3+2];
										num++;
									}

								}
							}
						}

				     }
				}
				double num_=1.0f/num;
				tempX=int(mx*num_+0.5);
				tempY=int(my*num_+0.5);
				Ytemp=mY*num_;
				Itemp=mI*num_;
				Qtemp=mQ*num_;

				double dx=tempX-xOld;
				double dy=tempY-yOld;
				double dY=Ytemp-Yold;
				double dI=Itemp-Iold;
				double dQ=Qtemp-Qold;

				shift=dx*dx+dy*dy+dY*dY+dI*dI+dQ*dQ;

				repetition++;


			} while (shift>3.0&&repetition<10);

			YIQdes[y*w*3+x*3]=Ytemp;
			YIQdes[y*w*3+x*3+1]=Itemp;
			YIQdes[y*w*3+x*3+2]=Qtemp;
			

		}
}