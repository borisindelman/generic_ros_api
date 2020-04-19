#ifndef ROS_DATA_HANDLE_BASE
#define ROS_DATA_HANDLE_BASE

class RosDataHandleBase
{
public:
	RosDataHandleBase() {}
	virtual ~RosDataHandleBase() {}

	virtual void publish() = 0;

	inline std::string getTopicName()
	{
		return m_topicName;
	}

	inline void setTopicName(std::string topicName)
	{
		m_topicName = topicName;
	}

protected:
	std::string m_topicName;
};

#endif // ROS_DATA_HANDLE_BASE
