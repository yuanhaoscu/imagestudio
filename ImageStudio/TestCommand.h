#ifndef TEST_COMMAND_H
#define TEST_COMMAND_H
#include "BaseCommand.h"
using std::shared_ptr;

class ImageYH;

class TestCommand:public BaseCommand
{
public:
	TestCommand(shared_ptr<ImageYH> img);
	virtual void RunCommand();
	~TestCommand();
private:
	shared_ptr<ImageYH> img_;
	double Distance;
	void Func(double *yiq,int width,int height,BYTE * bgr);
	void Func2();
	void IntegrateMap(BYTE *gray,int width,int  height);
	double distance(double y1,double i1,double q1,double y2,double i2,double q2)
	{
		return (y2-y1)*(y2-y1)+(i2-i1)*(i2-i1)+(q2-q1)*(q2-q1);
	}
};














#endif