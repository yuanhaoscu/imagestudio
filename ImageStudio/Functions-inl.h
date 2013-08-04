#ifndef FUNCTIONS_INL
#define FUNCTIONS_INL

template<typename T>
T m_max(T a,T b)
{
	return a>b?a:b;
};

template<typename T>
T m_min(T a,T b)
{
	return a<b?a:b;
};

template<typename T>
void m_swap(T &a,T &b)
{
	T temp=a;
	a=b;
	b=temp;
};
template<typename T>
T find_mid(T *arr,int size)
{
	if(size==1) return arr[0];

	for(int i=0;i<(size/2+1);i++)
		for(int j=size-1;j>i;j--)
		{
			
			if(arr[j]<arr[j-1]) m_swap(arr[j],arr[j-1]);
		}

		return arr[size/2];
}


static void RGB2YIQ(BYTE* bgr,double* yiq,int width,int height)
{
	double Y,I,Q;
	if(bgr==nullptr||yiq==nullptr) return;
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
		{
			Y=double(bgr[y*width*3+x*3]*0.114f+bgr[y*width*3+x*3+1]*0.587f+bgr[y*width*3+x*3+2]*0.299f);
			I=double(-bgr[y*width*3+x*3]*0.321f-bgr[y*width*3+x*3+1]*0.275f+bgr[y*width*3+x*3+2]*0.596f);
			Q=double(bgr[y*width*3+x*3]*0.311f-bgr[y*width*3+x*3+1]*0.523f+bgr[y*width*3+x*3+2]*0.212f);
			yiq[y*width*3+x*3]=Y;
			yiq[y*width*3+x*3+1]=I;
			yiq[y*width*3+x*3+2]=Q;
		};

};

static void YIQ2RGB(double *YIQdes,BYTE * bgr,int width,int height)
{
	BYTE b,g,r;

	if(nullptr==YIQdes||nullptr==bgr) return;

	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
		{
			r=(BYTE)(YIQdes[y*width*3+x*3]*1.0f + YIQdes[y*width*3+x*3+1]*0.956f + YIQdes[y*width*3+x*3+2]*0.621f);
			g=(BYTE)(YIQdes[y*width*3+x*3]*1.0f - YIQdes[y*width*3+x*3+1]*0.272f - YIQdes[y*width*3+x*3+2]*0.321f);
			b=(BYTE)(YIQdes[y*width*3+x*3]*1.0f - YIQdes[y*width*3+x*3+1]*1.105f + YIQdes[y*width*3+x*3+2]*1.702f);
			bgr[y*width*3+x*3]=b;
			bgr[y*width*3+x*3+1]=g;
			bgr[y*width*3+x*3+2]=r;
		}
};

template<typename T>
static void median_filter(T * psrc,int width,int height,int depth,int rctsize=3)
{
	if(nullptr==psrc) return ;

	T * reslt=new T[width*height*depth];
	memcpy(reslt,psrc,sizeof(T)*width*height*depth);

	int nrow=width*depth;
	if(1==depth)
	{
		nrow=width;
	    T * arr=new T[rctsize*rctsize];

	    for(int x=rctsize/2;x<width-rctsize/2;x++)
		  for(int y=rctsize/2;y<height-rctsize/2;y++)
		   {
			    int i=0;
			    for(int xx=-rctsize/2;xx<=rctsize/2;xx++)
				    for(int yy=-rctsize/2;yy<=rctsize/2;yy++)
					 {
						arr[i]=psrc[y*nrow+x];
						i++;
				     }
				reslt[y*width+x]=find_mid(arr,rctsize*rctsize);
		   }
		  delete [] arr;
		  memcpy(psrc,reslt,sizeof(T)*width*height);
	}

	if(3==depth)
	{
		T * arr1=new T[rctsize*rctsize];
		T * arr2=new T[rctsize*rctsize];
		T * arr3=new T[rctsize*rctsize];
		nrow=width*3;
		for(int x=rctsize/2;x<width-rctsize/2;x++)
			for(int y=rctsize/2;y<height-rctsize/2;y++)
			{
				int i=0;
				for(int xx=-rctsize/2;xx<=rctsize/2;xx++)
					for(int yy=-rctsize/2;yy<=rctsize/2;yy++)
					{
						arr1[i]=psrc[y*nrow+x*3];
						arr2[i]=psrc[y*nrow+x*3+1];
						arr3[i]=psrc[y*nrow+x*3+2];
						i++;
					}
					reslt[y*nrow+x*3]=find_mid(arr1,rctsize*rctsize);
					reslt[y*nrow+x*3+1]=find_mid(arr2,rctsize*rctsize);
					reslt[y*nrow+x*3+2]=find_mid(arr3,rctsize*rctsize);
			}
			delete [] arr1;
			delete [] arr2;
			delete [] arr3;
			memcpy(psrc,reslt,sizeof(T)*width*height*depth);
	}

};




//////////////////////////////////////////
#endif