#ifndef THREAD_THREAD_H_
#define THREAD_THREAD_H_

#include <windows.h>
#include <process.h>

class ThreadExecute;

class Thread
{
public:
	enum Status
	{
		SUSPENDING,
		RUNNING,
		ENDED,
	};

	Thread(ThreadExecute * execute, unsigned initflag = 0);

	virtual ~Thread();

	DWORD GetThreadId()
	{ 
		return ::GetThreadId(handle_); 
	}

	HANDLE GetRawHandle()
	{
		return handle_;
	}

	// 休眠
	void Suspend()
	{
		SuspendThread(handle_);
		status_ = SUSPENDING;
	}

	// 唤醒
	void Resume()
	{
		ResumeThread(handle_);
		status_ = RUNNING;
	}

	// 等待线程结束
	void Join()
	{
		Resume(); // 避免线程休眠导致不能退出
		WaitForSingleObject(handle_, INFINITE);		
		status_ = ENDED;
	}

	Status get_status() { return status_; }

private:
	static unsigned __stdcall StartAddress( void * thread );

private:
	HANDLE handle_;
	Status status_;
	ThreadExecute * execute_;
};

#endif