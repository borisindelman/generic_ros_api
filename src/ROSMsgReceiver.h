#ifndef ROS_MSG_RECEIVER
#define ROS_MSG_RECEIVER

#include "SynchronisedQueue.h"
#include "OSALThread.h"
#include "RosDataSubscribeHandle.h"
#include "TopicPool.h"

#define SUB_QUEUE_SIZE 100

class RosMsgReceiverBase : public OSALThread
{
public:
	RosMsgReceiverBase(){}
	virtual ~RosMsgReceiverBase(){}
};


template< class T >
class RosMsgReceiver : public RosMsgReceiverBase
{
public:
	RosMsgReceiver(std::string topicName, TopicPoolSubscribeBase<T>* pool) 
		:m_topicName(topicName),
			m_pool(pool) 
			{}
	virtual ~RosMsgReceiver() {}

	void init(ros::NodeHandle& nodeHandle)
	{
		//subscribe to ros
		m_sub = nodeHandle.subscribe(m_topicName, SUB_QUEUE_SIZE, &RosMsgReceiver::callback, this);
	}

	void setTopicName(const std::string& topic)
	{
		m_topicName = topic;
	}

	void callback(T RosMsg)
	{
		RosDataSubscribeHandle<T>* ptr = m_pool->allocate();
		if(!ptr)
		{
			std::cout << "Pool sub Allocate Error" << endl;
			return;
		}
		ptr->setData(&RosMsg);
		m_queue.enqueue(ptr);
	}

	virtual void run()
	{
		while (1)
		{
			receive();
		}
	}

private:
	typedef SynchronisedQueue< RosDataSubscribeHandle<T>* > SyncQueue;

	SyncQueue m_queue;
	std::string m_topicName;
	ros::Subscriber m_sub;
	TopicPoolSubscribeBase<T>* m_pool;

	void receive()
	{
		RosDataSubscribeHandle<T>* ptr;
		std::cout << "receive()" << endl;
		ptr = m_queue.dequeue();
		std::cout << "dequeue_rec" << endl;
		ptr->handle();
		m_pool->deallocate(ptr);
	}

};


#endif // ROS_MSG_RECEIVER