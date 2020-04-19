#ifndef ROS_DATA_HANDLE
#define ROS_DATA_HANDLE

#include "SynchronisedQueue.h"
#include "OSALThread.h"
#include "ros/ros.h"
#include "RosDataHandleBase.h"

#define PUB_QUEUE_SIZE 10

template< class T > 
class RosDataHandle : public RosDataHandleBase
{
public:

	RosDataHandle() {}
	virtual ~RosDataHandle() {}

	virtual void convert() = 0;

	void setNodeHandle(ros::NodeHandle* rosNodeHandlePtr)
	{
		if(!m_rosNodeHandlePtr)
		{
			m_rosNodeHandlePtr = rosNodeHandlePtr;
		}
	}

	virtual void publish()
	{
		if(ros::ok())
		{
			std::cout << "convert " << endl;
			convert();  // build T member (convert) in derived implementation 
            std::cout << "m_topicName in publish  " <<  m_topicName << endl;
			if (m_publishers.count(m_topicName))
			{
				std::cout << "--------- BORIS -------------" << endl;
				m_publishers[m_topicName].publish(m_rosMsg);
				// ros::spinOnce();
			}
			else
			{
				//error
			}
		}
		else
		{
			//ros isn't ok error
		}
		
		
	}

	void publisherInit()
	{
		//advertise to ros with T message
		//add pub to map in RoComMng
		if (m_publishers[m_topicName])
		{
			//do nothing;
		}
		else
		{
            std::cout << "m_rosNodeHandlePtr " << m_rosNodeHandlePtr << endl;
            std::cout << "m_publishers[m_topicName] " << m_publishers[m_topicName] << endl;
			m_publishers[m_topicName] = m_rosNodeHandlePtr->advertise<T>(m_topicName, PUB_QUEUE_SIZE);
            // m_publishers[m_topicName] = nh.advertise<T>(m_topicName, PUB_QUEUE_SIZE);
            std::cout << "m_publishers[m_topicName] " << m_publishers[m_topicName] << endl;
		}
	}

protected:

	T m_rosMsg;

private:

	static std::map<std::string, ros::Publisher> m_publishers;
	static ros::NodeHandle* m_rosNodeHandlePtr;

private:
};

template< class T > 
std::map<std::string, ros::Publisher> RosDataHandle <T>::m_publishers;

template< class T > 
ros::NodeHandle* RosDataHandle <T>::m_rosNodeHandlePtr = 0;

#endif // ROS_DATA_HANDLE
