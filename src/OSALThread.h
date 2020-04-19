#ifndef _OSAL_THREAD_
#define _OSAL_THREAD_

#include <boost/thread.hpp>
//#include <boost/thread/thread.hpp>
//#include <boost/thread/mutex.hpp>
//#include <boost/thread/condition.hpp>


class OSALThread
{
public:
	//typedef enum RT_PRIO
	//{
	//	PRIO_MIN_7 = -7,
	//	PRIO_MIN_6 = -6,
	//	PRIO_MIN_5 = -5,
	//	PRIO_MIN_4 = -4,
	//	PRIO_MIN_3 = -3,
	//	PRIO_MIN_2 = -2,
	//	PRIO_MIN_1 = -1,
	//	PRIO_IDLE = 0,
	//	PRIO_PLUS_1 = 1,
	//	PRIO_PLUS_2 = 2,
	//	PRIO_PLUS_3 = 3,
	//	PRIO_PLUS_4 = 4,
	//	PRIO_PLUS_5 = 5,
	//	PRIO_PLUS_6 = 6
	//}RT_PRIO;

	typedef enum THREAD_PRIO
	{
		THREAD_PRIO_IDLE = -15,
		THREAD_PRIO_LOWEST = -2,
		THREAD_PRIO_BELOW_NORMAL = -1,
		THREAD_PRIO_NORMAL = 0,
		THREAD_PRIO_ABOVE_NORMAL = 1,
		THREAD_PRIO_HIGHEST = 2,
		THREAD_PRIO_TIME_CRITICAL = 15
	}THREAD_PRIO;

public:
	OSALThread();
	~OSALThread();

	void start();
	virtual void run() = 0;

	static void threadFunc(OSALThread* this_ptr);

	bool setPrio(THREAD_PRIO priority);

	void join();

private:
	bool						m_startFlag;
	boost::thread*				m_thread;
	boost::mutex				m_mutex;	//	the mutex to condition variable use
	boost::condition_variable	m_cond;		// the condition to wait for (thread synchronization)
};



#endif // _OSAL_THREAD_
