#ifndef ROS_COM_MANAGER
#define ROS_COM_MANAGER

//#include "RosDataHandle.h"
#include "ROSMsgSender.h"
#include "ROSMsgReceiver.h"
#include "ros/ros.h"
#include "TopicPool.h"

class RosDataHandleBase;
class RosMsgSender;

class RosComManager
{
public:
	
	~RosComManager();

	void init(int argc, char **argv, std::string node_name);

	void start();

	template< class T >
	void subscriberInit(TopicPoolSubscribeBase<T>* pool)
	{
		std::string topicName = pool->getTopicName();
		RosMsgReceiver<T>* rosMsgReceiverPtr;
		rosMsgReceiverPtr = new RosMsgReceiver<T>(topicName, pool);

		rosMsgReceiverPtr->init(*m_rosNodeHandlePtr);

		m_rosMsgReceiverBase_map[topicName] = rosMsgReceiverPtr;
	}

	template< class T >
	void publisherInit(TopicPoolPublishBase<T>* pool)
	{
		RosMsgSender* rosMsgSender;
		rosMsgSender = new RosMsgSender;
		pool->setNodeHandle(m_rosNodeHandlePtr);
		m_topicName = pool->getTopicName();
        rosMsgSender->setTopicName(m_topicName);
		if (m_publishers_map[m_topicName])
		{
			return;
		}
		else
		{
			m_publishers_map[m_topicName] = rosMsgSender;
		}        
	}

	void publish(RosDataHandleBase* RosDataHandleBasePtr);

	ros::NodeHandle* getNodeHandlePtr();

	static RosComManager& getInstance()
	{
		static RosComManager theRosComManager;
		return theRosComManager;
	}

private:

	RosComManager();
	RosComManager(const RosComManager& toCopy);

	ros::NodeHandle* m_rosNodeHandlePtr;
	std::map< std::string, RosMsgSender* > m_publishers_map;
	std::map< std::string, RosMsgReceiverBase* > m_rosMsgReceiverBase_map;
	std::string m_topicName;
};


#endif // ROS_COM_MANAGER