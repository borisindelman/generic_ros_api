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

	void setTopicName(std::string topicName)
	{
		m_topicName = topicName;
	}

	virtual void handle() = 0;

	//default data set to rosmsg type
	virtual void setData(T* rosMsg)
	{
		m_rosMsg = *rosMsg;
	}

protected:

	T m_rosMsg;
	std::string m_topicName;

private:

};

#endif // ROS_DATA_SUBSCRIBE_HANDLE
