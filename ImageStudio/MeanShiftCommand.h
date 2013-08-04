#ifndef MEANSHIFT_COMMAND_H
#define MEANSHIFT_COMMAND_H

#include "BaseCommand.h"
using std::tr1::shared_ptr;
class ImageYH;
class MeanShiftCommand:public BaseCommand
{
public:
	MeanShiftCommand(shared_ptr<ImageYH>,double clr_distance,int  radius);
	~MeanShiftCommand();
	virtual void RunCommand();
private:
	shared_ptr<ImageYH> image_;
	double clr_distance_;
	int radius_;
	CommandType type_;
	void MeanShift(double *YIQsrc,double *YIQdes,int w,int h,double clr_distance,int radius);
};




#endif