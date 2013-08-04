#ifndef DICE_PAINT_COMMAND_H
#define DICE_PAINT_COMMAND_H
#include "BaseCommand.h"
using std::tr1::shared_ptr;
class ImageYH;
class DicePaintCommand:public BaseCommand
{
public:
	DicePaintCommand(shared_ptr<ImageYH> img);
	~DicePaintCommand();
	virtual void RunCommand();
private:
	shared_ptr<ImageYH> img_;
	void Paint(BYTE *pimg,int nrow,int x,int y,int dicenum);
	

};





#endif