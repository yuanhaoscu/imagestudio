#ifndef WAVE_FILTER_COMMAND_H
#define WAVE_FILTER_COMMAND_H

#include "BaseCommand.h"
using std::tr1::shared_ptr;
class ImageYH;
class WaveFilterCommand:public BaseCommand
{
public:
	WaveFilterCommand(shared_ptr<ImageYH>,double wave_length,double peroid);
	~WaveFilterCommand();
	virtual void RunCommand();
private:
	shared_ptr<ImageYH> image_;
	CommandType type_;
	double wave_length_;
	double peroid_;
	void WaveGo(BYTE *src,BYTE *des,int width,int height,int nrowsrc,int nrowdes);
};




#endif