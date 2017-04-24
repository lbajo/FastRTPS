#include <fastrtps/participant/Participant.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/subscriber/Subscriber.h>
#include <fastrtps/attributes/SubscriberAttributes.h>

#include <fastrtps/Domain.h>

#include "DateSubscriber.h"


DateSubscriber::DateSubscriber() : mp_participant(nullptr), mp_subscriber(nullptr) {}

DateSubscriber::~DateSubscriber() {	Domain::removeParticipant(mp_participant);}

bool DateSubscriber::init()
{
	ParticipantAttributes PParam;
	PParam.rtps.builtin.domainId = 0; 
	PParam.rtps.builtin.leaseDuration = c_TimeInfinite;
	PParam.rtps.setName("Participant_subscriber");
	mp_participant = Domain::createParticipant(PParam);
	if(mp_participant == nullptr)
			return false;
	
	Domain::registerType(mp_participant,(TopicDataType*) &myType);		
			
	SubscriberAttributes Rparam;
	Rparam.topic.topicKind = NO_KEY;
	Rparam.topic.topicDataType = myType.getName();
	Rparam.topic.topicName = "DatePubSubTopic";
	mp_subscriber = Domain::createSubscriber(mp_participant,Rparam,(SubscriberListener*)&m_listener);
	if(mp_subscriber == nullptr)
		return false;
	return true;
}

void DateSubscriber::SubListener::onSubscriptionMatched(Subscriber* sub,MatchingInfo& info)
{
	if (info.status == MATCHED_MATCHING)
	{
		n_matched++;
		std::cout << "Subscriber matched" << std::endl;
	}
	else
	{
		n_matched--;
		std::cout << "Subscriber unmatched" << std::endl;
	}
}

void DateSubscriber::SubListener::onNewDataMessage(Subscriber* sub)
{
		Date st;
		
		if(sub->takeNextData(&st, &m_info))
		{
			if(m_info.sampleKind == ALIVE)
			{
				++n_msg;
				std::cout << "Sample received, count=" << n_msg << std::endl;
			}
		}
}

void DateSubscriber::run()
{
	std::cout << "Waiting for Data, press Enter to stop the Subscriber. "<<std::endl;
	std::cin.ignore();
	std::cout << "Shutting down the Subscriber." << std::endl;
}

