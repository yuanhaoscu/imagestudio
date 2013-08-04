#ifndef IMAGE_MANAGER_H
#define IMAGE_MANAGER_H
using std::shared_ptr;

class ImageYH;

class ImageManager
{
public:
	ImageManager();
	shared_ptr<ImageYH> GetOriginalImage();
	~ImageManager();
	void LoadImageFile(CString filename);
	double GetZoomNumber();
	void SetZoomNumber(double zoom);

	CString GetFilePath(){return file_path_;};
private:
	ImageManager(const ImageManager&);
	ImageManager& operator=(const ImageManager&);

	shared_ptr<ImageYH> orignal_image_;

	double zoom_;
	CString file_path_;
};


#endif