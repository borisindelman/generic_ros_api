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
        std::cout << "m_rosNodeHandlePtr publisherInit " <<  m_rosNodeHandlePtr << endl;
		pool->setNodeHandle(m_rosNodeHandlePtr);
		m_topicName = pool->getTopicName();
        std::cout << "m_topicName publisherInit " <<  m_topicName << endl;
        std::cout << "pool->getTopicName()" <<  pool->getTopicName() << endl;
        rosMsgSender->setTopicName(m_topicName);
        std::cout << "m_publishers_map[m_topicName]1 " <<  m_publishers_map[m_topicName] << endl;
		if (m_publishers_map[m_topicName])
		{
            std::cout << "if m_publishers_map[m_topicName] " << endl;
			return;
		}
		else
		{
            std::cout << "else m_publishers_map[m_topicName] " << rosMsgSender << endl;
			m_publishers_map[m_topicName] = rosMsgSender;
		}

        std::cout << "m_publishers_map[m_topicName]2 " <<  m_publishers_map[m_topicName] << endl;

        
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