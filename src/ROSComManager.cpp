#include "ROSComManager.h"
#include "RosDataHandle.h"

RosComManager::RosComManager()  {}
RosComManager::RosComManager(const RosComManager& toCopy) {}

RosComManager::~RosComManager()
{
    std::map< std::string, RosMsgReceiverBase* >::iterator it_sub;
	std::map< std::string, RosMsgSender* >::iterator it_pub;

	for (it_sub=m_rosMsgReceiverBase_map.begin(); it_sub!=m_rosMsgReceiverBase_map.end(); ++it_sub)
	{
        delete [] (it_sub->second);
	}

	for (it_pub=m_publishers_map.begin(); it_pub!=m_publishers_map.end(); ++it_pub)
    {
    	delete [] (it_pub->second);
    }
}

void RosComManager::init(int argc, char **argv, std::string node_name)
{
	ros::init(argc, argv, node_name);

	m_rosNodeHandlePtr = new ros::NodeHandle;
	ROS_INFO("[ %s ] initialized", node_name.c_str());
}

void RosComManager::start()
{
	std::map< std::string, RosMsgReceiverBase* >::iterator it_sub;
	std::map< std::string, RosMsgSender* >::iterator it_pub;
	int counter=0;

	for (it_sub=m_rosMsgReceiverBase_map.begin(); it_sub!=m_rosMsgReceiverBase_map.end(); ++it_sub)
	{
    	(it_sub->second)->start();
		counter++;
	}
	counter = 0;
	for (it_pub=m_publishers_map.begin(); it_pub!=m_publishers_map.end(); ++it_pub)
	{
    	(it_pub->second)->start();
		counter++;
	}
}

void RosComManager::publish(RosDataHandleBase* RosDataHandleBasePtr)
{
	std::string topic_name; 
	topic_name = RosDataHandleBasePtr->getTopicName();
	m_publishers_map[topic_name]->enqueue(RosDataHandleBasePtr);
}

ros::NodeHandle* RosComManager::getNodeHandlePtr()
{
	return m_rosNodeHandlePtr;
}
