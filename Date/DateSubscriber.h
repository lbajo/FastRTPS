#ifndef DATESUBSCRIBER_H_
#define DATESUBSCRIBER_H_

#include "DatePubSubTypes.h"

#include <fastrtps/fastrtps_fwd.h>
#include <fastrtps/attributes/SubscriberAttributes.h>
#include <fastrtps/subscriber/SubscriberListener.h>
#include <fastrtps/subscriber/SampleInfo.h>


using namespace eprosima::fastrtps;

#include "Date.h"

class DateSubscriber {
public:
	DateSubscriber();
	virtual ~DateSubscriber();
	//!Initialize the subscriber
	bool init();
	//!RUN the subscriber
	void run();
	//!Run the subscriber until number samples have been recevied.
	void run(uint32_t number);
private:
	Participant* mp_participant;
	Subscriber* mp_subscriber;
public:
	class SubListener:public SubscriberListener
	{
	public:
		SubListener():n_matched(0),n_samples(0){};
		~SubListener(){};
		void onSubscriptionMatched(Subscriber* sub,MatchingInfo& info);
		void onNewDataMessage(Subscriber* sub);
		Date m_Hello;
		SampleInfo_t m_info;
		int n_matched;
		uint32_t n_samples;
	}m_listener;
private:
	DatePubSubType m_type;
};

#endif /* DATESUBSCRIBER_H_ */
