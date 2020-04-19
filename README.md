ROS Com Framework

---

### What is the ROS COM Framework?
The ROS com Framework provides an abstraction layer for cpp projects that require communication with the ROS framework. All the ROS declerations, initializations and mesage buffers are implemented in the framework and are hidden away from the user. The framework is agnostic to the type of message by clevelry wrapping the data type of the ROS message and the data type used inside the program.

---

### How to use the ROS COM Framework?
A good example can be found in the `ros_com_interface_harness.cpp`

First instasiate the RosComManger which is a singleton and will always point to the same instance anywhere in the code. Provide a Topic name, which should be unique to the program.
```cpp
//Ros Com Framework init
RosComManager& rosComManagerRef = RosComManager::getInstance();
rosComManagerRef.init(argc, argv, "Topic Name");
```
Next, instasiate subscribers and publishers by creating static pools and providing them to the manager. 
```cpp
// Subscribers init
TopicPoolSubscribe<StringDataSub, std_msgs::String > stringDataSubPool("subscribe_node_name");
rosComManagerRef.subscriberInit(&stringDataSubPool);

// Publisher init
TopicPoolPublish<StringDataPub, std_msgs::String > stringDataPubPool("publisher_node_name");	
rosComManagerRef.publisherInit(&stringDataPubPool);
```
Now, the ROS COM Framework can be started.
```cpp
// Start the framework
rosComManagerRef.start();
```
Here's an example of how to publish:
```cpp
//publish
StringDataPub* stringData = stringDataPubPool.allocate();
stringData->m_rfa_type_param = "Hello World";
rosComManagerRef.publish(stringData);
```

Don't forget to make sure the main thread is alive, or else the thread will die and the manager with it. This can be simply done by:
```cpp
while(1)
	{
		ros::spin();
	}
```

The `StringDataSub` and `StringDataPub` in the examples are intermediate classes that provide the framework with the type of the message (`std_msgs::String`), the type of the data used in the program (`std::string`) and the way to convert between them.

This is how `StringDataSub` is implemented:
```cpp
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
```
This is how `StringDataPub` is implemented:
```cpp
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
```