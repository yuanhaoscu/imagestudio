#include "stdafx.h"
#include "BaseCommand.h"
#include "MainFrm.h"
#include "MfcClassManager.h"
BaseCommand::BaseCommand()
{
	type_=NOTYPE;
}
BaseCommand::~BaseCommand()
{

}
void BaseCommand::CommandOver()
{
	  Singleton<MfcClassManager>::GetInstance()->GetframePtr()->PostMessage(WM_TASK_INFO,0,0);
}