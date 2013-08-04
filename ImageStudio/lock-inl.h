#ifndef LOCK_LOCK_INL_H_
#define LOCK_LOCK_INL_H_

#include <windows.h>
#include <assert.h>
class noncopyable
{
protected:
	noncopyable() {}
	~noncopyable() {}
private:
	noncopyable(const noncopyable&);
	noncopyable& operator=(const noncopyable&);
};

class Mutex : private noncopyable
{
protected:
	CRITICAL_SECTION critical_;

public:
	Mutex()
	{
		InitializeCriticalSection(&critical_);
	}
	~Mutex()
	{
		DeleteCriticalSection(&critical_);
	}
	void Lock()
	{
		EnterCriticalSection(&critical_);
	}
	void UnLock()
	{
		LeaveCriticalSection(&critical_);
	}
};

class ScopedLock : private noncopyable
{
protected:
	Mutex &mutex_;
public:
	ScopedLock(Mutex & mutex)
	  : mutex_(mutex)
	{
		mutex_.Lock();
	}
	~ScopedLock()
	{
		mutex_.UnLock();
	}
};

class EventVarible : private noncopyable
{
protected:
	HANDLE handle_;

public:
	EventVarible(bool manual_reset, bool init_state)
	{
		handle_ = CreateEvent(nullptr, (BOOL)manual_reset, (BOOL)init_state, nullptr);

		assert(handle_);
	}
	~EventVarible()
	{
		CloseHandle(handle_);
	}
	void Set()
	{
		SetEvent(handle_);
	}
	void Reset()
	{
		ResetEvent(handle_);
	}
	void Wait()
	{
		WaitForSingleObject(handle_, INFINITE);
	}
	bool TimedWait(unsigned long time)
	{
		return 0 == WaitForSingleObject(handle_, time);
	}
};


#endif