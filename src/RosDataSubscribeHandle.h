#ifndef ROS_DATA_SUBSCRIBE_HANDLE
#define ROS_DATA_SUBSCRIBE_HANDLE

#include "SynchronisedQueue.h"
#include "OSALThread.h"
#include "ros/ros.h"

template< class T > 
class RosDataSubscribeHandle
{
public:

	RosDataSubscribeHandle(){}
	virtual ~RosDataSubscribeHandle() {}

	// std::string getTopicName()
	// {
	// 	return m_topicName;
	// };

	void setTopicName(std::string topicName)
	{
		m_topicName = topicName;
	}

	virtual void handle() = 0;

	//default data set to rosmsg type
	virtual void setData(T* rosMsg)
	{
		std::cout << "rosMsg->test.data " << rosMsg->data << endl;
		m_rosMsg = *rosMsg;
		std::cout << "m_rosMsg->test.data " << m_rosMsg.data << endl;
	}

protected:

	T m_rosMsg;
	std::string m_topicName;

private:

};

#endif // ROS_DATA_SUBSCRIBE_HANDLE
