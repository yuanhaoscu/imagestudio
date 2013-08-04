#ifndef IMAGEYH_H
#define IMAGEYH_H
//////////////////////////////////////////////////
/////Copyright By YuanHao 2013-3-27       ////////
////this class is used to show image by  /////////
////two layer,the image_ is the bottom   ////////
////layer,and the layer_ is the top layer.////////
////the top layer is mainly used to show //////////
////the processed image.                 ////////
/////////////////////////////////////////////////
using ATL::CImage;

class ImageYH
{
public:
	ImageYH();
	~ImageYH();
	ImageYH(const ImageYH&);
	ImageYH& operator=(const ImageYH&);

	enum DrawMode
	{
		LAYER_OFF=0,
		LAYER_ON=1

	};

	bool Load(LPCTSTR filename);

	bool Draw( HDC hDestDC,const RECT& rectDest);
	bool Draw(HDC hDestDC, RECT& rectDest,double zoom);

	bool IsNull();
	bool Destroy();
	void ClearLayer();

	int GetWidth();
	int GetHeight();

	CImage *GetImage(){return image_;};
	CImage *GetLayer(){return layer_;};

	void SetDrawMode(DrawMode mode);
	int  GetDrawMode();
	void ChangeDrawMode();
	static RGBQUAD * GetColorTable();
private:
	CImage * image_;
	CImage * layer_;
	int width_;
	int height_;
	DrawMode draw_mode_;
    static RGBQUAD *colortable;
};


#endif