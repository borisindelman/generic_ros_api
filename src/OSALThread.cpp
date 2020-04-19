#include "OSALThread.h"

#ifdef _WIN32
#include <Windows.h>
#endif

OSALThread::OSALThread()
 :m_startFlag(false)
{
	m_thread = new boost::thread(threadFunc, this);
}


OSALThread::~OSALThread()
{
	delete m_thread;
}


void OSALThread::threadFunc(OSALThread* this_ptr)
{
	boost::unique_lock<boost::mutex> lock(this_ptr->m_mutex);

	// wait for start
	while (this_ptr->m_startFlag == false) this_ptr->m_cond.wait(lock);

	// run OSALThread logic
	this_ptr->run();
}


void OSALThread::start()
{
	boost::unique_lock<boost::mutex> lock(m_mutex);

	m_startFlag = true;

	m_cond.notify_one();
}


bool OSALThread::setPrio(THREAD_PRIO priority)
{
	bool retVal = false;
#ifdef _WIN32
	retVal = SetThreadPriority(m_thread->native_handle(), priority);
#endif
	return retVal;
}

void OSALThread::join()
{
	m_thread->join();
}