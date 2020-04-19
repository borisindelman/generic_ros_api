#include "ROSMsgSender.h"
#include "RosDataHandleBase.h"

RosMsgSender::RosMsgSender()
{
}

RosMsgSender::~RosMsgSender()
{
}

void RosMsgSender::init()
{
	//advertise to ros with T message
	//m_pub = ros.advertise<T>(m_topicName, QUEUE_SIZE);
}

void RosMsgSender::setTopicName(const std::string& topic)
{
	m_topicName = topic;
}

void RosMsgSender::enqueue(RosDataHandleBase* rosDataHandleBasePtr)
{
	m_queue.enqueue(rosDataHandleBasePtr);
}

void RosMsgSender::send()
{
	RosDataHandleBase* RosDataHandleBasePtr;
	RosDataHandleBasePtr = m_queue.dequeue();
	RosDataHandleBasePtr->publish();
}

void RosMsgSender::run()
{
	while (1)
	{
		send();
	}
}