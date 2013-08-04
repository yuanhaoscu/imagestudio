#ifndef SINGLETON_H_
#define SINGLETON_H_

#include "lock-inl.h"

template <typename T>
class Singleton
{
private:
	Singleton(){};
	//DISALLOW_COPY_AND_ASSIGN(Singleton);
	Singleton(const Singleton&);
	Singleton& operator= (const Singleton&);
public:
	struct AutoRelease
	{
	public:
		~AutoRelease()
		{
			if (GetInstance() != nullptr)
			{
				delete GetInstance();
				GetInstance() = nullptr;
			}
		}
	};

private:
	static Mutex mutex_;
	static T * instance_;

public:
	static T *&GetInstance()
	{
		if (instance_ == nullptr)
		{
			ScopedLock lock(mutex_);
			if (instance_ == nullptr)
			{
				static AutoRelease auto_release_singleton;
				instance_ = new T;
			}
		}
		return instance_;
	}
};

template <typename T>
T * Singleton<T>::instance_ = nullptr;

template <typename T>
Mutex Singleton<T>::mutex_;

#endif
