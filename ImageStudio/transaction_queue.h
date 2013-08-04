#ifndef TRANSACTION_QUEUE_H_
#define TRANSACTION_QUEUE_H_

#include "thread.h"
#include "thread_execute-inl.h"
#include "lock-inl.h"

using std::deque;
using std::shared_ptr;
using std::function;
using std::string;



class BaseCommand;

class TransactionQueue : public ThreadExecute
{
protected:
	deque<shared_ptr<BaseCommand>> transaction_queue_;
	bool run_flag_;	//线程运行标志
	bool single_run_flag_;
	Thread thread_;
	EventVarible not_empty_;

public:
	TransactionQueue();
	virtual ~TransactionQueue();

	void AddTransaction(shared_ptr<BaseCommand> transaction);
	bool IsTransactionQueueEmpty(){return !single_run_flag_;}
	virtual void Run();

	

private:
	void Clear();

private:
	// 线程安全
	shared_ptr<BaseCommand> Take();
	Mutex mutex_;

	// 事务的回掉函数
	
};



#endif