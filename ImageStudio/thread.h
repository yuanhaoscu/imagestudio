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

	// ����
	void Suspend()
	{
		SuspendThread(handle_);
		status_ = SUSPENDING;
	}

	// ����
	void Resume()
	{
		ResumeThread(handle_);
		status_ = RUNNING;
	}

	// �ȴ��߳̽���
	void Join()
	{
		Resume(); // �����߳����ߵ��²����˳�
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