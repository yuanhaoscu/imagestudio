#include "stdafx.h"
#include "TestCommand.h"
#include "ImageYH.h"
#include "ImageStudioView.h"
#include "MainFrm.h"
#include "MfcClassManager.h"
#include "singleton-inl.h"
#include "Functions-inl.h"
#include <math.h>
#include <queue>
#include <map>
#include <fstream>
#include <stdio.h>
using namespace std;

typedef struct point
{
	int x;
	int y;
}point;
typedef struct rginfo
{
	double y;
	double i;
	double q;
	int num;
}rginfo;

#define  CHECK_BOUND(x,y,w,h)  ( ((x)>0)&&((x)<w)&&((y)>0)&&((y)<h))

TestCommand::TestCommand(shared_ptr<ImageYH> img)
{
	img_=img;
}

TestCommand::~TestCommand()
{

}

void TestCommand::RunCommand()
{
/*	int nrow=img_->GetImage()->GetPitch();

	BYTE * psrc=(BYTE*)img_->GetImage()->GetBits();
	int width=img_->GetImage()->GetWidth();
	int height=img_->GetImage()->GetHeight();

	BYTE *bgr=new BYTE[width*height*3];
	double *yiq=new double[width*height*3];
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
		{
			bgr[y*width*3+x*3]=psrc[y*nrow+x*3];
			bgr[y*width*3+x*3+1]=psrc[y*nrow+x*3+1];
			bgr[y*width*3+x*3+2]=psrc[y*nrow+x*3+2];
		}

		RGB2YIQ(bgr,yiq,width,height);

    	Func(yiq,width,height,bgr);
//		Func2(bgr,width,height);
//		YIQ2RGB(yiq,bgr,width,height);
		BYTE * player=(BYTE *)img_->GetLayer()->GetBits();
		nrow = img_->GetLayer()->GetPitch();
		for(int x=0;x<width;x++)
			for(int y=0;y<height;y++)
			{
				player[y*nrow+x*3]  =bgr[y*width*3+x*3];
				player[y*nrow+x*3+1]=bgr[y*width*3+x*3+1];
				player[y*nrow+x*3+2]=bgr[y*width*3+x*3+2];
			}



			delete [] bgr;
			delete [] yiq;
			CommandOver();*/
//	this->IntegrateMap(nullptr,10,10);
//	CommandOver();
	Func2();
}

void TestCommand::Func(double *yiq,int width,int height,BYTE *bgr)
{

	int *lablemap=new int[width*height];
	memset(lablemap,0,sizeof(int)*width*height);
	int lable=1;
	queue<point> Queue;
	BYTE * player=(BYTE *)img_->GetLayer()->GetBits();
	int nrow = img_->GetLayer()->GetPitch();

	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
		{
			if ( (lablemap[y*width+x]==0)&&(player[y*nrow+x*3+2]==255))
			{
				point pt;
				pt.x=x;
				pt.y=y;
				Queue.push(pt);
				lablemap[y*width+x]=lable;
			
			}
			else
			{
				continue;
			}

			while(!Queue.empty())
			{
				point pt=Queue.front();
				Queue.pop();
				double y1;
				double i1;
     			double q1;
		    	y1=yiq[pt.y*width*3+(pt.x)*3];
			    i1=yiq[pt.y*width*3+(pt.x)*3+1];
				q1=yiq[pt.y*width*3+(pt.x)*3+2];

				for(int xx=-1;xx<=1;xx++)
					for(int yy=-1;yy<=1;yy++)
					{
						if(CHECK_BOUND(pt.x+xx,pt.y+yy,width,height))
						{
							if( (lablemap[(pt.y+yy)*width+pt.x+xx]==0)&&(player[(pt.y+yy)*nrow+(pt.x+xx)*3+2]==255))
							{
								
					

								double y2=yiq[(pt.y+yy)*width*3+(pt.x+xx)*3];
								double i2=yiq[(pt.y+yy)*width*3+(pt.x+xx)*3+1];
								double q2=yiq[(pt.y+yy)*width*3+(pt.x+xx)*3+2];

								if(distance(y1,i1,q1,y2,i2,q2)<10)
								{

								lablemap[(pt.y+yy)*width+pt.x+xx]=lable;
								point tmp;
								tmp.x=pt.x+xx;
								tmp.y=pt.y+yy;
								Queue.push(tmp);
								}

							}
						}
					}

			}

			lable++;

		}


    BYTE * clr=new BYTE[lable*3];
	for(int i=0;i<lable;i++)
	{
		clr[i*3]=BYTE(rand()%256);
		clr[i*3+1]=BYTE(rand()%256);
		clr[i*3+2]=BYTE(rand()%256);
	}

	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
		{
			bgr[y*width*3+x*3]=clr[ lablemap[y*width+x]*3];
			bgr[y*width*3+x*3+1]=clr[ lablemap[y*width+x]*3+1];
			bgr[y*width*3+x*3+2]=clr[ lablemap[y*width+x]*3+2];
		}
	delete[] clr;
	delete [] lablemap;
}

void TestCommand::Func2()
{
	CImage saveimg;
	saveimg.Create(img_->GetWidth()/2,img_->GetHeight()/2,8);
	int steps=m_min(img_->GetWidth()/2,img_->GetHeight()/2);
	BYTE *psrc=(BYTE *)img_->GetImage()->GetBits();
	int nrowsrc=img_->GetImage()->GetPitch();
	BYTE *pdes=(BYTE *)saveimg.GetBits();
	int nrowdes=saveimg.GetPitch();
	for(int xi=0;xi<steps;xi++)
		for(int yi=0;yi<steps;yi++)
		{
			pdes[yi*nrowdes+xi]=(psrc[(yi*2)*nrowsrc+(xi*2)*3]+psrc[(yi*2)*nrowsrc+(xi*2)*3+1]+psrc[(yi*2)*nrowsrc+(xi*2)*3+2]
			                             +psrc[(yi*2)*nrowsrc+(2*xi+1)*3]+psrc[(yi*2)*nrowsrc+(2*xi+1)*3+1]+psrc[(yi*2)*nrowsrc+(2*xi+1)*3+2]
										 +psrc[(yi*2+1)*nrowsrc+(2*xi)*3]+psrc[(yi*2+1)*nrowsrc+(2*xi)*3+1]+psrc[(yi*2+1)*nrowsrc+(2*xi)*3+2]
										 +psrc[(yi*2+1)*nrowsrc+(2*xi+1)*3]+psrc[(yi*2+1)*nrowsrc+(2*xi+1)*3]+psrc[(yi*2+1)*nrowsrc+(2*xi+1)*3])/12;

		}
		saveimg.SetColorTable(0,255,ImageYH::GetColorTable());
		saveimg.Save("d:\\testImg\\lena256.bmp");
}

void TestCommand::IntegrateMap(BYTE *gray,int width,int height)
{
	int arr[10][10];
	int brr[10][10];
	for(int x=0;x<10;x++)
		for(int y=0;y<10;y++)
		{
			brr[y][x]=arr[y][x]=rand()%10;
		}
	for(int x=1;x<10;x++)
	{
		brr[0][x]=brr[0][x]+brr[0][x-1];
		brr[x][0]=brr[x][0]+brr[x-1][0];
	}

	for(int y=1;y<10;y++)
		for(int x=1;x<10;x++)
		{
			brr[y][x]=brr[y][x]+brr[y-1][x]+brr[y][x-1]-brr[y-1][x-1];
		}
	 ofstream otf("d://output20130529.txt");
	 for(int y=0;y<10;y++)
	 {
		 for(int x=0;x<10;x++)
		 {
			static  char str[20];
			sprintf_s(str,"%-10d",arr[y][x]);
			otf<<str;

		 }
		 otf<<"\r\n";
	 }
	 otf<<"result:\r\n";

	 for(int y=0;y<10;y++)
	 {
		 for(int x=0;x<10;x++)
		 {
			 static  char str[20];
			 sprintf_s(str,"%-10d",brr[y][x]);
			 otf<<str;

		 }
		 otf<<"\r\n";
	 }

	 otf.close();
}