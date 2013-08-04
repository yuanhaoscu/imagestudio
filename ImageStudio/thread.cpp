#include "stdafx.h"
#include "thread.h"
#include "thread_execute-inl.h"


Thread::Thread( ThreadExecute * execute, unsigned initflag /*= 0*/ )
{
	execute_ = execute;
	handle_ = (HANDLE)_beginthreadex(nullptr, 0, StartAddress, this, initflag, nullptr);

	assert(handle_ != 0);
}

Thread::~Thread()
{
	CloseHandle(handle_);
}

unsigned __stdcall Thread::StartAddress( void * thread )
{
	Thread * thread_object = (Thread*)thread;

	thread_object->execute_->Run();

	_endthreadex(0);

	return 0;
}
