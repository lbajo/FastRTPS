#ifndef DATEPUBLISHER_H_
#define DATEPUBLISHER_H_

#include "DatePubSubTypes.h"

#include <fastrtps/fastrtps_fwd.h>
#include <fastrtps/attributes/PublisherAttributes.h>
#include <fastrtps/publisher/PublisherListener.h>
using namespace eprosima::fastrtps;

#include "Date.h"

class DatePublisher {
public:
	DatePublisher();
	virtual ~DatePublisher();
	bool init();
	void run(uint32_t number);
private:
	Date m_Hello;
	Participant* mp_participant;
	Publisher* mp_publisher;
	class PubListener:public PublisherListener
	{
	public:
		PubListener():n_matched(0){};
		~PubListener(){};
		void onPublicationMatched(Publisher* pub,MatchingInfo& info);
		int n_matched;
	}m_listener;
	DatePubSubType m_type;
};



#endif
