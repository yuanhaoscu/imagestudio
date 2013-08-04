#include "stdafx.h"
#include "DicePaintFilterCommand.h"
#include "ImageYH.h"
#include "ImageStudioView.h"
#include "MainFrm.h"
#include "MfcClassManager.h"
#include "singleton-inl.h"
#include "resource.h"
////////////////////////////////////////
//////number 6
BYTE dice6[8][8]={
	{0,1,1,0,0,1,1,0},
	{0,1,1,0,0,1,1,0},
	{0,0,0,0,0,0,0,0},
	{0,1,1,0,0,1,1,0},
	{0,1,1,0,0,1,1,0},
	{0,0,0,0,0,0,0,0},
	{0,1,1,0,0,1,1,0},
	{0,1,1,0,0,1,1,0}
};
//////number 5
BYTE dice5[8][8]={
	{0,0,0,0,0,0,0,0},
	{0,1,1,0,0,1,1,0},
	{0,1,1,0,0,1,1,0},
	{0,0,0,1,1,0,0,0},
	{0,0,0,1,1,0,0,0},
	{0,1,1,0,0,1,1,0},
	{0,1,1,0,0,1,1,0},
	{0,0,0,0,0,0,0,0}
};
///////number 4
BYTE dice4[8][8]={
	{0,0,0,0,0,0,0,0},
	{0,1,1,0,0,1,1,0},
	{0,1,1,0,0,1,1,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,1,1,0,0,1,1,0},
	{0,1,1,0,0,1,1,0},
	{0,0,0,0,0,0,0,0}
};
///////number 3
BYTE dice3[8][8]={
	{0,0,0,1,1,0,0,0},
	{0,0,0,1,1,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,1,1,0,0,0},
	{0,0,0,1,1,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,1,1,0,0,0},
	{0,0,0,1,1,0,0,0}
};
///////number 2
BYTE dice2[8][8]={
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,0,0},
	{0,0,0,0,1,1,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,1,1,0,0,0,0},
	{0,0,1,1,0,0,0,0},
	{0,0,0,0,0,0,0,0}
};
///////number 1
BYTE dice1[8][8]={
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,1,1,0,0,0},
	{0,0,0,1,1,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0}
};
//////////////////////////////////
DicePaintCommand::DicePaintCommand(shared_ptr<ImageYH> img)
{
	this->img_=img;
	this->type_=DICE_PAINT;
}
DicePaintCommand::~DicePaintCommand()
{

}
void DicePaintCommand::RunCommand()
{
	
	int width=img_->GetLayer()->GetWidth();
	int height=img_->GetLayer()->GetHeight();
	BYTE *pdes=(BYTE*)img_->GetImage()->GetBits();
	BYTE *psrc=(BYTE*)img_->GetLayer()->GetBits();
	int nrow=img_->GetLayer()->GetPitch();
	int nirow=img_->GetImage()->GetPitch();
	int dice_num_width=width/8;
	int dice_num_height=height/8;
	int maxg=0;
	int ming=255;
	for(int x=0;x<dice_num_width;x++)
		for(int y=0;y<dice_num_height;y++)
		{
			int sum=0;
			for(int w=x*8;w<x*8+8;w++)
				for(int h=y*8;h<y*8+8;h++)
				{
					sum+=(pdes[h*nirow+w*3]+psrc[h*nirow+w*3+1]+psrc[h*nirow+w*3+2])/3;
				}
				sum=sum/64;
				if(sum>maxg) maxg=sum;
				if(sum<ming) ming=sum;
		}


	for(int x=0;x<dice_num_width;x++)
		for(int y=0;y<dice_num_height;y++)
		{
			int sum=0;
			for(int w=x*8;w<x*8+8;w++)
				for(int h=y*8;h<y*8+8;h++)
				{
					sum+=(pdes[h*nirow+w*3]+psrc[h*nirow+w*3+1]+psrc[h*nirow+w*3+2])/3;
				}
			sum=sum/64;
			if(sum<(ming+(maxg-ming)/6))
			{
				Paint(psrc,nrow,x*8,y*8,1);
			}
			else if(sum<(ming+(maxg-ming)*2/6))
			{
				Paint(psrc,nrow,x*8,y*8,2);
			}
			else if(sum<(ming+(maxg-ming)*3/6))
			{
				Paint(psrc,nrow,x*8,y*8,3);
			}
			else if(sum<(ming+(maxg-ming)*4/6))
			{
				Paint(psrc,nrow,x*8,y*8,4);
			}
			else if(sum<(ming+(maxg-ming)*5/6))
			{
				Paint(psrc,nrow,x*8,y*8,5);
			}
			else
			{
				Paint(psrc,nrow,x*8,y*8,6);
			}
		}

	Singleton<MfcClassManager>::GetInstance()->GetframePtr()->PostMessage(WM_TASK_INFO,0,0);

}

void DicePaintCommand::Paint(BYTE *pimg,int nrow,int x,int y,int dicenum)
{
	switch(dicenum)
	{
	case 1:
		{
			for(int w=0;w<8;w++)
				for(int h=0;h<8;h++)
				{
					pimg[(y+h)*nrow+(x+w)*3]=dice1[h][w]*254+1;
					pimg[(y+h)*nrow+(x+w)*3+1]=dice1[h][w]*254+1;
					pimg[(y+h)*nrow+(x+w)*3+2]=dice1[h][w]*254+1;
				}
		}
		break;
	case 2:
		{
			for(int w=0;w<8;w++)
				for(int h=0;h<8;h++)
				{
					pimg[(y+h)*nrow+(x+w)*3]=dice2[h][w]*254+1;
					pimg[(y+h)*nrow+(x+w)*3+1]=dice2[h][w]*254+1;
					pimg[(y+h)*nrow+(x+w)*3+2]=dice2[h][w]*254+1;
				}
		}
		break;
	case 3:
		{
			for(int w=0;w<8;w++)
				for(int h=0;h<8;h++)
				{
					pimg[(y+h)*nrow+(x+w)*3]=dice3[h][w]*254+1;
					pimg[(y+h)*nrow+(x+w)*3+1]=dice3[h][w]*254+1;
					pimg[(y+h)*nrow+(x+w)*3+2]=dice3[h][w]*254+1;
				}
		}
		break;
	case 4:
		{
			for(int w=0;w<8;w++)
				for(int h=0;h<8;h++)
				{
					pimg[(y+h)*nrow+(x+w)*3]=dice4[h][w]*254+1;
					pimg[(y+h)*nrow+(x+w)*3+1]=dice4[h][w]*254+1;
					pimg[(y+h)*nrow+(x+w)*3+2]=dice4[h][w]*254+1;
				}
		}
		break;
	case 5:
		{
			for(int w=0;w<8;w++)
				for(int h=0;h<8;h++)
				{
					pimg[(y+h)*nrow+(x+w)*3]=dice5[h][w]*254+1;
					pimg[(y+h)*nrow+(x+w)*3+1]=dice5[h][w]*254+1;
					pimg[(y+h)*nrow+(x+w)*3+2]=dice5[h][w]*254+1;
				}
		}
		break;
	case 6:
		{
			for(int w=0;w<8;w++)
				for(int h=0;h<8;h++)
				{
					pimg[(y+h)*nrow+(x+w)*3]=dice6[h][w]*254+1;
					pimg[(y+h)*nrow+(x+w)*3+1]=dice6[h][w]*254+1;
					pimg[(y+h)*nrow+(x+w)*3+2]=dice6[h][w]*254+1;
				}
		}
		break;
	default:
		break;
	}
}