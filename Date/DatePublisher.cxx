#include <fastrtps/participant/Participant.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/publisher/Publisher.h>
#include <fastrtps/attributes/PublisherAttributes.h>

#include <fastrtps/Domain.h>

#include <fastrtps/utils/eClock.h>

#include "DatePublisher.h"




DatePublisher::DatePublisher() : mp_participant(nullptr), mp_publisher(nullptr) {}

DatePublisher::~DatePublisher() {	Domain::removeParticipant(mp_participant);}

bool DatePublisher::init()
{
	
	ParticipantAttributes PParam;
	PParam.rtps.builtin.domainId = 0;
	PParam.rtps.builtin.leaseDuration = c_TimeInfinite;
	PParam.rtps.setName("Participant_publisher");
	mp_participant = Domain::createParticipant(PParam);
	if(mp_participant == nullptr)
		return false;
	
	
	Domain::registerType(mp_participant,(TopicDataType*) &myType);
	
	
	PublisherAttributes Wparam;
	Wparam.topic.topicKind = NO_KEY;
	Wparam.topic.topicDataType = myType.getName(); 
	Wparam.topic.topicName = "DatePubSubTopic";
	mp_publisher = Domain::createPublisher(mp_participant,Wparam,(PublisherListener*)&m_listener);
	if(mp_publisher == nullptr)
		return false;
	std::cout << "Publisher created, waiting for Subscribers." << std::endl;
	return true;
}

void DatePublisher::PubListener::onPublicationMatched(Publisher* pub,MatchingInfo& info)
{
	if (info.status == MATCHED_MATCHING)
	{
		n_matched++;
		std::cout << "Publisher matched" << std::endl;
	}
	else
	{
		n_matched--;
		std::cout << "Publisher unmatched" << std::endl;
	}
}

void DatePublisher::run()
{
	while(m_listener.n_matched == 0)
	{
		eClock::my_sleep(250);
	}
	
	
	Date st;
	
	
	int msgsent = 0;
	char ch = 'y';
	do
	{
		if(ch == 'y')
		{
			mp_publisher->write(&st);  ++msgsent;
			std::cout << "Sending sample, count=" << msgsent << ", send another sample?(y-yes,n-stop): ";
		}
		else if(ch == 'n')
		{
			std::cout << "Stopping execution " << std::endl;
			break;
		}
		else
		{
			std::cout << "Command " << ch << " not recognized, please enter \"y/n\":";
		}
	}while(std::cin >> ch);
}
