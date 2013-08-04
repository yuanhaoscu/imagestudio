#include "stdafx.h"
#include "transaction_queue.h"
#include "lock-inl.h"
#include "BaseCommand.h"
#include "MfcClassManager.h"
#include "MainFrm.h"


TransactionQueue::TransactionQueue() 
  : run_flag_(true),
	thread_(this),
	single_run_flag_(false),
	not_empty_(false, false)
{
}

TransactionQueue::~TransactionQueue()
{
	Clear();
	thread_.Join();
}

void TransactionQueue::AddTransaction( shared_ptr<BaseCommand> transaction )
{
	CMainFrame *fm=Singleton<MfcClassManager>::GetInstance()->GetframePtr();
	fm->SetTimer(1,500,NULL);
 	ScopedLock lock(mutex_);
  	transaction_queue_.push_back(transaction);

	not_empty_.Set();
// try to resume the thread
// 	thread_.Resume();
}

void TransactionQueue::Run()
{
	volatile bool &run = run_flag_;
	while (run)
	{
		while (transaction_queue_.empty())
		{

			not_empty_.Wait();

			if (!run) return;
		}

		shared_ptr<BaseCommand> transacton = Take();

		if (transacton)
		{
			// 事务开始的时候，回掉指定函数
			transacton->RunCommand();
		}
	}
}

shared_ptr<BaseCommand> TransactionQueue::Take()
{
	shared_ptr<BaseCommand> task;
	ScopedLock lock(mutex_);
	if (!transaction_queue_.empty())
	{
		task = transaction_queue_.front();
		transaction_queue_.pop_front();
	}
	return task;
}

void TransactionQueue::Clear()
{
	if (!transaction_queue_.empty())
	{
		ScopedLock lock(mutex_);
		transaction_queue_.clear();
	}

	run_flag_ = false;

	not_empty_.Set();
}



