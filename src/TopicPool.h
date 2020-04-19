#ifndef _STATIC_POOL_
#define _STATIC_POOL_

#include <boost/pool/singleton_pool.hpp>

#include "ros/ros.h"

#include "RosDataSubscribeHandle.h"
#include "RosDataHandle.h"


using namespace std;

template <typename T>
class TopicPoolSubscribeBase
{
public:
	TopicPoolSubscribeBase(std::string topicName) :m_topicName(topicName) { }
	virtual ~TopicPoolSubscribeBase() { }

	virtual RosDataSubscribeHandle<T>* allocate() = 0;

	virtual void deallocate(RosDataSubscribeHandle<T>* ptr) = 0;

	const std::string& getTopicName()
	{
		return m_topicName;
	}
protected:
	std::string m_topicName;
};


template <typename R, typename T>
class TopicPoolSubscribe : public TopicPoolSubscribeBase <T>
{
public:
	TopicPoolSubscribe(std::string topicName) :TopicPoolSubscribeBase<T>(topicName){}
	virtual ~TopicPoolSubscribe() { }

	virtual RosDataSubscribeHandle<T>* allocate()
	{
		R* temp_r_ptr;
		temp_r_ptr = (R*)StaticPool::malloc();
		temp_r_ptr = new(temp_r_ptr) R();
		temp_r_ptr->setTopicName(this->m_topicName);
		return temp_r_ptr;
	}

	virtual void deallocate(RosDataSubscribeHandle<T>* ptr)
	{
		ptr->~RosDataSubscribeHandle();
		StaticPool::free(ptr);
	}

private:
	 typedef boost::singleton_pool<R, sizeof(R)> StaticPool;
	 
};

template <typename T>
class TopicPoolPublishBase
{
public:
	TopicPoolPublishBase(std::string topicName) :m_topicName(topicName) { }
	virtual ~TopicPoolPublishBase() { }

	// virtual RosDataHandle<T>* allocate() = 0;

	// virtual void deallocate(RosDataHandle<T>* ptr) = 0;

	void setNodeHandle(ros::NodeHandle* rosNodeHandlePtr)
	{
		m_rosNodeHandlePtr = rosNodeHandlePtr;
	}

	const std::string& getTopicName()
	{
		return m_topicName;
	}
protected:
	std::string m_topicName;
	ros::NodeHandle* m_rosNodeHandlePtr;
};


template <typename R, typename T>
class TopicPoolPublish : public TopicPoolPublishBase <T>
{
public:
	TopicPoolPublish(std::string topicName) :TopicPoolPublishBase<T>(topicName){}
	virtual ~TopicPoolPublish() { }

	R* allocate()
	{
		R* temp_r_ptr;
		std::cout << "BULBUL1" << endl;
		temp_r_ptr = (R*)StaticPool::malloc();
		if(!temp_r_ptr)
		{
			std::cout << "Allocation error" << endl;
			return NULL;
		}
		std::cout << "temp_r_ptr " <<  temp_r_ptr << endl;
		std::cout << "this->m_topicName: " << this->m_topicName << endl;
		temp_r_ptr = new(temp_r_ptr) R();
		// std::cout << "BULBUL3" << endl;
		temp_r_ptr->setTopicName(this->m_topicName);
		std::cout << "this->m_rosNodeHandlePtr " <<  this->m_rosNodeHandlePtr << endl;
		temp_r_ptr->setNodeHandle(this->m_rosNodeHandlePtr);
        std::cout << "BULBUL3" << endl;
		temp_r_ptr->publisherInit();
		std::cout << "BULBUL4" << endl;
		return temp_r_ptr;
	}

	void deallocate(R* ptr)
	{
		ptr->~R();
		StaticPool::free(ptr);
	}

private:
	 typedef boost::singleton_pool<R, sizeof(R)> StaticPool;
	 
};

#endif // _STATIC_POOL_

