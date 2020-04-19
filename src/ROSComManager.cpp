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
    std::cout << "m_rosNodeHandlePtr in RosComManager " << m_rosNodeHandlePtr << endl;

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
	std::cout << "it_sub: " << counter << endl;
	counter = 0;
	for (it_pub=m_publishers_map.begin(); it_pub!=m_publishers_map.end(); ++it_pub)
	{
        std::cout << "in pub for: " << (it_pub->first) << endl;
		std::cout << "in pub for: " << (it_pub->second) << endl;
    	(it_pub->second)->start();
		std::cout << "after pub for" << endl;
		counter++;
	}
	std::cout << "it_pub: " << counter << endl;
}

void RosComManager::publish(RosDataHandleBase* RosDataHandleBasePtr)
{
	std::string topic_name; 
	topic_name = RosDataHandleBasePtr->getTopicName();
	std::cout << "Topic Name: " << topic_name << endl;
    std::cout << "Topic Name: " << m_publishers_map[topic_name] << endl;
	m_publishers_map[topic_name]->enqueue(RosDataHandleBasePtr);
}

ros::NodeHandle* RosComManager::getNodeHandlePtr()
{
	return m_rosNodeHandlePtr;
}
