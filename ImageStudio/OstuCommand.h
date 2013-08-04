#ifndef OSTU_COMMAND_H
#define OSTU_COMMAND_H
#include "BaseCommand.h"
using std::tr1::shared_ptr;
class ImageYH;
class OstuCommand:public BaseCommand
{
public:
	virtual void RunCommand();
	OstuCommand(shared_ptr<ImageYH> img);
	~OstuCommand();
private:
	shared_ptr<ImageYH> image_;
	void Ostu(BYTE *srcdata,BYTE *Bmap,int width,int height);
};


#endif