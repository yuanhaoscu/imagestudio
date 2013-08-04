#ifndef ISODATA_COMMAND_H
#define ISODATA_COMMAND_H

#include "BaseCommand.h"
#include <vector>
#include <map>
using namespace std;

using std::tr1::shared_ptr;
class ImageYH;

typedef struct yiq_
{
	double y;
	double i;
	double q;
}PointValue;

typedef struct point_
{
	int x;
	int y;
}point;

class IsoDataCommand:public BaseCommand
{
public:
	IsoDataCommand(shared_ptr<ImageYH> img);
	~IsoDataCommand();
	virtual void RunCommand();
	void ISODATA(double *clrdata,int w,int h,int num_of_class,double splite_diatance,double max_inner_distance);
	int findClass(map<int,PointValue> &center,PointValue pv);
private:
	shared_ptr<ImageYH> img_;




};




#endif