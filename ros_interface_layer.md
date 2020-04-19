# Ros Interface Layer

## Overview

The ROS interface layer is an API for connecting to ROS using publishers and subscribers. It will support publishing any data you want and convert it to the ROS type that the user will choose. You also can subscribe to any message and implement how to handle the data as you wish.

---

## API

### ROS Manager

* ROS Manager class is a singleton. To use the class, you must get an instance.

    ```cpp
    RosComManager& rosComManagerRef = RosComManager::getInstance();
    ```

* Use `init` to initinitialize the ROS node with a node name the user specifies.

    ```cpp
    rosComManagerRef.init(argc, argv, "node_name");
    ```

---

### Subscriber

#### RosDataSubscribeHandle

* First you need to implement a data subscriber class that inherits from `RosDataSubscribeHandle<T>`. T is the ROS data type to receive.
* Implementing the constructor or the destructor is not a must.
* You must implement the virtual function `handle`:
  * Inside the function, the ROS data message is provided as the data member `m_rosMsg` (this is part of parent class `RosDataSubscribeHandle`). 
  * The user is responsible to implement any operation over the data such as copy to a buffer, convert to the application data type, calculations, etc.

* Example:

    ```cpp
    class DataSub: public RosDataSubscribeHandle <std_msgs::String>
    {
    public:
     DataSub(){}
     virtual ~DataSub() {}

     virtual void handle()
     {
       m_rfa_type_param = m_rosMsg.test.data;
       std::cout << "m_rfa_type_param " << m_rfa_type_param    << endl;
     }

     std::string m_rfa_type_param;
    };
    ```

  * In the example, std::string is the application data type and std_msgs::String is the ROS data type.
  * `handle` is responsible to convert between the two data types.

#### TopicPoolSubscribe

* Each topic has a static pool that allocates instances of the data subscriber class that the user created.
* Create this template class with data subscriber class first and ros type second:

    ```cpp
    TopicPoolSubscribe< data_subscriber_class, ros_type> ("topic_name");
    ```

  * The input for this instance is the topic name you want to subscribe to.

* Example:

    ```cpp
    dataSubscriberPool = new TopicPoolSubscribe<Data, std_msgs::String> ("string_data");
    ```

* Initialize the subscriber topic with:

    ```cpp
    rosComManagerRef.subscriberInit(TopicPoolSubscribe);
    ```

  * The only input is the topic pool pointer you want to subscribe to
* The subscriber is ready to start and listen to ros messages:

    ```cpp
    rosComManagerRef.start();
    ```

---

## Publisher

#### RosDataPublisherHandle

* First you need to implement a data Publisher class that inherits from `RosDataPublisherHandle<T>`, T is the ROS data type you are publishing.
* Implementing the constructor or the destructor is not a must.
* You must implement the virtual function `convert`:
  * Inside the function, the ROS data message is provided as the data member `m_rosMsg` (this is part of parent class `RosDataPublisherHandle`). 
  * The user is responsible to implement any operation over the data such as copy to a buffer, convert to the ROS data type, calculations, etc.

* Example:

    ```cpp
    class DataPub : public RosDataPublisherHandle <std_msgs::String>
    {
    public:
      DataPub(){}
      virtual ~ DataPub() {}

      virtual void convet()
      {
        m_rosMsg.test.data = m_rfa_type_param;
        std::cout << "m_rosMsg.test.data: " << m_rosMsg.test.data <<endl;
      }

      std::string m_rfa_type_param;
    };
    ```

#### TopicPoolPublisher

* Each topic has a static pool that allocates instances of the data publisher class that the user created.
* Create this template class with data publisher class"

    ```cpp
    TopicPoolPublisher< data publisher class > ("topic_name");
    ```

  * The input for this instance is the topic name you want to publish.
  
* Example:

    ```cpp
    dataPublisherPool = new TopicPoolPublish < DataPub, std_msgs::String>("string_data");
    ```

* Initialize the publisher topic with ():

    ```cpp
    rosComManagerRef.publisherInit(TopicPoolPublisher)
    ```

  * The only input is the topic pool pointer you want to publish to.

* The Publisher is ready to start:

    ```cpp
    rosComManagerRef.start();
    ```

* To publish:
  * Allocate an instance from the topic pool:

    ```cpp
    m_DataPub = dataPublisherPool->allocate();
    ```

  * Publish using the ROS Com Manager:

    ```cpp
    rosComManagerRef.publish(m_DataPub);
    ```
