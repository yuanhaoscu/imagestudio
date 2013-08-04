#include "stdafx.h"
#include "OstuCommand.h"
#include "ImageYH.h"

OstuCommand::OstuCommand(shared_ptr<ImageYH> img)
{
	type_=OSTU;
	image_=img;

}
OstuCommand::~OstuCommand()
{

}
void OstuCommand::RunCommand()
{
	if(image_==nullptr) return;
	if(image_->IsNull()) return;
	int nrowbyte=image_->GetImage()->GetPitch();

	int bpp=image_->GetImage()->GetBPP();
/*	CString str;
	str.Format(_T("%d"),n);
	AfxMessageBox(str);
	return;*/

	BYTE *pByte=(BYTE*)(image_->GetImage()->GetBits());
	int w=image_->GetWidth();
	int h=image_->GetHeight();
	BYTE *Gray=new BYTE[w*h];
	if(Gray==nullptr)
	{
		AfxMessageBox(_T("内存分配失败"));
		return;
	}
	BYTE *Bmap=new BYTE[w*h];
	if(Bmap==nullptr)
	{
		AfxMessageBox(_T("内存分配失败"));
		return;
	}
	if(bpp==8)
	{
		for(int x=0;x<w;x++)
			for(int y=0;y<h;y++)
			{
				Gray[y*w+x]=pByte[y*nrowbyte+x];
				Bmap[y*w+x]=0;	
			}
	}
	else if(bpp==24)
	{
	for(int x=0;x<w;x++)
		for(int y=0;y<h;y++)
		{
			Gray[y*w+x]=(pByte[y*nrowbyte+x*3]+pByte[y*nrowbyte+x*3+1]+pByte[y*nrowbyte+x*3+2])/3;
			Bmap[y*w+x]=0;	
		}
	}
	else
	{
		AfxMessageBox(_T("图片格式不对！"));
		delete [] Gray;
		delete [] Bmap;
		return;
	}
	Ostu(Gray,Bmap,w,h);

	int nrow=image_->GetLayer()->GetPitch();

	BYTE *pLayer=(BYTE*)(image_->GetLayer()->GetBits());
	for(int x=0;x<w;x++)
		for(int y=0;y<h;y++)
		{
			if(Bmap[y*w+x]==1)
			{
				pLayer[y*nrow+x*3]=0;
				pLayer[y*nrow+x*3+1]=0;
				pLayer[y*nrow+x*3+2]=255;
			}
			else
			{
				pLayer[y*nrow+x*3]=0;
				pLayer[y*nrow+x*3+1]=0;
				pLayer[y*nrow+x*3+2]=0;
			}
		}

delete [] Gray;
delete [] Bmap;
}
void OstuCommand::Ostu(BYTE *srcdata,BYTE *Bmap,int width,int height)
{
	double n0=0,n1=0;
	double w0=0,w1=0,u0=0,u1=0;
	int th=1;
	double sum0=0,sum1=0,sum=0;
	double g=-1;
	double maxg[256];
	int size=width*height;
	int histnum[256];
	memset(histnum,0,256*sizeof(int));
	for(int i=0;i<256;i++) maxg[i]=0;

	for(int i=0;i<size;i++)
	{
		if(srcdata[i]>255) srcdata[i]=255;
		if(srcdata[i]<0) srcdata[i]=0;

		histnum[srcdata[i]]++;


	}
	for(int i=0;i<256;i++) sum+=i*histnum[i];
	double u=double(sum)/size;
	for(int k=0;k<256;k++)
	{
		n0 += histnum[k]; 
		sum0 += k * histnum[k];
	
		n1=size-n0;
		w0=(n0+1)/size;
		w1=(n1+1)/size;
		u0 = sum0 / n0; 
		u1 = (sum -sum0) / n1; 
		g =w0*w1*(u1-u0)*(u1-u0);
		maxg[k]=g;




	}
	double imax=0;

	for(int i=0;i<256;i++)
	{
		if(maxg[i]>=imax)
		{
			imax=maxg[i];
			th=i;
		}

	}
	for(int i=0;i<size;i++)
	{
		if(srcdata[i]<=th) Bmap[i]=0;
		else Bmap[i]=1;
	}
}