#include <iostream>

#include "ROSComManager.h"
#include "RosDataHandle.h"
#include "RosDataSubscribeHandle.h"
#include "TopicPool.h"

#include "ros/ros.h"
#include "std_msgs/String.h"

class StringDataPub : public RosDataHandle < std_msgs::String >
{
public:
	StringDataPub(){}
	~StringDataPub() {}

	virtual void convert()
	{
		m_rosMsg.data = m_rfa_type_param;
	}

	std::string m_rfa_type_param;
private:
};

class StringDataSub : public RosDataSubscribeHandle < std_msgs::String >
{
public:
	StringDataSub(){}
	virtual ~StringDataSub() {}

	virtual void handle()
	{
		m_rfa_type_param = m_rosMsg.data;
	}

	std::string m_rfa_type_param;
private:
};

int main(int argc, char **argv)
{
	//Ros Com Framework init
	RosComManager& rosComManagerRef = RosComManager::getInstance();
	rosComManagerRef.init(argc, argv, "Topic Name");

    // Subscribers init
	TopicPoolSubscribe<StringDataSub, std_msgs::String > stringDataSubPool("subscribe_node_name");
    rosComManagerRef.subscriberInit(&stringDataSubPool);

    // Publisher init
	TopicPoolPublish<StringDataPub, std_msgs::String > stringDataPubPool("publisher_node_name");	
	rosComManagerRef.publisherInit(&stringDataPubPool);
	
    // Start the framework
	rosComManagerRef.start();

	//publish
    StringDataPub* stringData = stringDataPubPool.allocate();
	stringData->m_rfa_type_param = "Hello World";
	rosComManagerRef.publish(stringData);

	while(1)
	{
		ros::spin();
	}
	// rosMsgReceiverPtr->join();

	return 0;
}