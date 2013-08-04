#include "stdafx.h"
#include "KmeansCommand.h"
#include "ImageYH.h"
#include "ImageStudioView.h"
#include "MainFrm.h"
#include "MfcClassManager.h"
#include "singleton-inl.h"
#include "Functions-inl.h"




KmeansCommand::KmeansCommand(shared_ptr<ImageYH> img)
{
	img_=img;
	k_num_=2;
}
void KmeansCommand::RunCommand()
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

		RGB2YIQ(bgr,yiq,width,height);

		Kmeans(yiq,width,height,k_num_);

		YIQ2RGB(yiq,bgr,width,height);

		for(int x=0;x<width;x++)
			for(int y=0;y<height;y++)
			{
				psrc[y*nrow+x*3]  =bgr[y*width*3+x*3];
				psrc[y*nrow+x*3+1]=bgr[y*width*3+x*3+1];
				psrc[y*nrow+x*3+2]=bgr[y*width*3+x*3+2];
			}
		


			delete [] bgr;
			delete [] yiq;
	   CommandOver();
}

void KmeansCommand::Kmeans(double *src,int width,int height,int k)
{
	vector<Elemt> elems;//所有元素

	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
		{
			Elemt elm;
			elm.y=src[y*width*3+x*3];
			elm.i=src[y*width*3+x*3+1];
			elm.q=src[y*width*3+x*3+2];
			elm.pt.x=x;
			elm.pt.y=y;
			elems.push_back(elm);
		}
    
	vector<Elemt> mCenter;//各类的聚类中心
	mCenter.resize(k);
	vector< vector<Elemt> > Elemclass;//分别存放每个类的元素集合
	Elemclass.resize(k);

	for(int i=0;i<k;i++)
	{
		mCenter[i]=elems[i];//初始化聚类中心
	}
	//////////////////初始分类
	BYTE * Cmap=new BYTE[width*height];
	for(int i=0;i<elems.size();i++)
	{
		int idx=GetNearestClass(elems[i],mCenter,k);
		Elemclass[idx].push_back(elems[i]);
		Cmap[ (elems[i].pt.x) +(elems[i].pt.y )*width ]=idx;
	}


	bool flag=true;
	int rept=0;
	while(rept<50&&flag)
	{
		flag=false;
		rept++;

		for(int i=0;i<k;i++)
		{
			vector<Elemt> & velm=Elemclass[i];
			Elemt csum;
			csum.y=0;
			csum.i=0;
			csum.q=0;
			for(auto itr=velm.begin();itr!=velm.end();itr++)
			{
				csum.y+=itr->y;
				csum.i+=itr->i;
				csum.q+=itr->q;
			}

			if(velm.size()!=0)
			{
				mCenter[i].y=csum.y/velm.size();
				mCenter[i].i=csum.i/velm.size();
				mCenter[i].q=csum.q/velm.size();
			}
			else
			{
				mCenter[i].y=0;
				mCenter[i].i=0;
				mCenter[i].q=0;
			}

		}

		for(int i=0;i<k;i++)
			{
				Elemclass[i].clear();
		    }

		for(int i=0;i<elems.size();i++)
		{
			int idx=GetNearestClass(elems[i],mCenter,k);
			Elemclass[idx].push_back(elems[i]);

			if(idx!=Cmap[ (elems[i].pt.x) +(elems[i].pt.y )*width ])
				flag=true;

			Cmap[ (elems[i].pt.x) +(elems[i].pt.y )*width ]=idx;

		}



	}


	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
		{
			int idx=Cmap[y*width+x];
			Elemt elm=mCenter[idx];
			src[y*width*3+x*3]=elm.y;
			src[y*width*3+x*3+1]=elm.i;
			src[y*width*3+x*3+2]=elm.q;
		}


  delete [] Cmap;
}

int KmeansCommand::GetNearestClass(Elemt &elm,vector<Elemt> & center,int k)
{
	double mindis=(elm.y-center[0].y)*(elm.y-center[0].y)
			+(elm.i-center[0].i)*(elm.i-center[0].i)
			+(elm.q-center[0].q)*(elm.q-center[0].q);
	int idx=0;
	for(int i=1;i<k;i++)
	{
		double dis=(elm.y-center[i].y)*(elm.y-center[i].y)
			+(elm.i-center[i].i)*(elm.i-center[i].i)
			+(elm.q-center[i].q)*(elm.q-center[i].q);
		if(dis<mindis) 
		{
			mindis=dis;
			idx=i;
		}
	}
	return idx;
}