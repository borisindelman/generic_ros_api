#ifndef _SYNCHRONISEDQUEUE_
#define _SYNCHRONISEDQUEUE_

#include <boost/thread.hpp>
//#include <boost/thread/thread.hpp>
//#include <boost/thread/mutex.hpp>
//#include <boost/thread/condition_variable.hpp>
//#include <boost/thread/condition.hpp>

#include <queue>

using namespace std;

template <typename T>
class SynchronisedQueue
{
public:
	SynchronisedQueue() :m_size(0) { }
	virtual ~SynchronisedQueue() throw () { }

	unsigned long size() { return m_size; }

	// Add data to the queue and notify others
	void enqueue(const T& data)
	{
		// Acquire lock on the queue
		boost::unique_lock<boost::mutex> lock(m_mutex);

		// Add the data to the queue
		m_queue.push(data);
		m_size++;

		// Notify others that data is ready
		m_cond.notify_one();

	}	 // Lock is automatically released here

	// Get data from the queue. Wait for data if not available
	T dequeue()
	{

		// Acquire lock on the queue
		boost::unique_lock<boost::mutex> lock(m_mutex);

		// When there is no data, wait till someone fills it.
		// Lock is automatically released in the wait and obtained 
		// again after the wait
		while (m_queue.size() == 0) m_cond.wait(lock);

		// Retrieve the data from the queue
		T result = m_queue.front();
		m_queue.pop();
		m_size--;

		return result;

	} // Lock is automatically released here

private:
	std::queue<T>	m_queue;	//	use STL queue to store data
	boost::mutex	m_mutex;	//	the mutex to assure container thread safety 
	boost::condition_variable	m_cond;		// the condition to wait for (thread synchronization)
	unsigned long	m_size;		// for help
};

#endif // _SYNCHRONISEDQUEUE_

