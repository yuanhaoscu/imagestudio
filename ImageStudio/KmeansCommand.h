#ifndef KMEANS_COMMAND_H
#define KMEANS_COMMAND_H
#include "BaseCommand.h"
#include <vector>
using namespace std;

using std::tr1::shared_ptr;

typedef struct point_
{
	int x;
	int y;
}point;

typedef struct YIQ_
{
	double y;
	double i;
	double q;
	point pt;
}Elemt;


class ImageYH;

class KmeansCommand:public BaseCommand
{
public:
	KmeansCommand(shared_ptr<ImageYH> img);
	virtual void RunCommand();
private:
	shared_ptr<ImageYH> img_;
	int k_num_;
	void Kmeans(double *src,int width,int height,int k);
	int  GetNearestClass(Elemt &elm,vector<Elemt> & center,int k);
};







#endif