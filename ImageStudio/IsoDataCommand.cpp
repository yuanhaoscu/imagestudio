#include "stdafx.h"
#include "ImageYH.h"
#include "ImageStudioView.h"
#include "MainFrm.h"
#include "MfcClassManager.h"
#include "singleton-inl.h"
#include "Functions-inl.h"
#include "IsoDataCommand.h"



IsoDataCommand::IsoDataCommand(shared_ptr<ImageYH> img)
{
	img_=img;
	
}
IsoDataCommand::~IsoDataCommand()
{

}
void IsoDataCommand::RunCommand()
{
	int nrow=img_->GetImage()->GetPitch();

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
		median_filter(bgr,width,height,3);

		RGB2YIQ(bgr,yiq,width,height);


}

void IsoDataCommand::ISODATA(double *clrdata,int w,int h,int num_of_class,double splite_diatance,double max_inner_distance)
{
	map<int,PointValue> center;
    map<int,vector<point> > lablemap;
	map<int,int> classnum;
	int temp_class_lable=num_of_class;
	int  least_num_of_each_class=100;

	for(int i=0;i<num_of_class;i++)
	{
		PointValue pv;
		pv.y=clrdata[(h*w/num_of_class)*i*3];
		pv.i=clrdata[(h*w/num_of_class)*i*3+1];
		pv.q=clrdata[(h*w/num_of_class)*i*3+2];
		center[i]=pv;
	}

step1:
	for(int x=0;x<w;x++)
		for(int y=0;y<h;y++)
		{
			PointValue pv;
			point pt;
			pv.y=clrdata[y*w*3+x*3];
			pv.i=clrdata[y*w*3+x*3+1];
			pv.q=clrdata[y*w*3+x*3+2];
			int k=findClass(center,pv);
			lablemap[k].push_back(pt);
			classnum[k]++;
		}
step2:
		for(auto it=classnum.begin();it!=classnum.end();it++)
		{
			if(it->second<least_num_of_each_class)
			{
				classnum.erase(it);
			}
		}

}

int  IsoDataCommand::findClass(map<int,PointValue> &center,PointValue pv)
{
	double mindis=double(0xFFFFFFF);
	map<int,PointValue>::iterator it =center.begin();
	int key=it->first;
	for(auto iter=it;iter!=center.end();iter++)
	{
		PointValue tmpv=iter->second;
		double dis=(tmpv.y-pv.y)*(tmpv.y-pv.y)
			         +(tmpv.i-pv.i)*(tmpv.i-pv.i)
					 +(tmpv.q-pv.q)*(tmpv.q-pv.q);
		if(dis<mindis)
		{
			dis=mindis;
			key=iter->first;
		}
	}
	return key;
}