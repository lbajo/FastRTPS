#include "DateSubscriber.h"
#include <fastrtps/participant/Participant.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/SubscriberAttributes.h>
#include <fastrtps/subscriber/Subscriber.h>
#include <fastrtps/Domain.h>
#include <fastrtps/utils/eClock.h>


DateSubscriber::DateSubscriber():mp_participant(nullptr),
mp_subscriber(nullptr)
{
}

bool DateSubscriber::init()
{
    ParticipantAttributes PParam;
    PParam.rtps.defaultSendPort = 10043;
    PParam.rtps.builtin.use_SIMPLE_RTPSParticipantDiscoveryProtocol = true;
    PParam.rtps.builtin.use_SIMPLE_EndpointDiscoveryProtocol = true;
    PParam.rtps.builtin.m_simpleEDP.use_PublicationReaderANDSubscriptionWriter = true;
    PParam.rtps.builtin.m_simpleEDP.use_PublicationWriterANDSubscriptionReader = true;
    PParam.rtps.builtin.domainId = 80;
    PParam.rtps.builtin.leaseDuration = c_TimeInfinite;
    PParam.rtps.setName("Participant_sub");
    mp_participant = Domain::createParticipant(PParam);
    if(mp_participant==nullptr)
        return false;

    Domain::registerType(mp_participant,&m_type);
    SubscriberAttributes Rparam;
    Rparam.topic.topicKind = NO_KEY;
    Rparam.topic.topicDataType = "Date";
    Rparam.topic.topicName = "DateTopic";
    Rparam.topic.historyQos.kind = KEEP_LAST_HISTORY_QOS;
    Rparam.topic.historyQos.depth = 30;
    Rparam.topic.resourceLimitsQos.max_samples = 50;
    Rparam.topic.resourceLimitsQos.allocated_samples = 20;
    Rparam.qos.m_reliability.kind = RELIABLE_RELIABILITY_QOS;
    mp_subscriber = Domain::createSubscriber(mp_participant,Rparam,(SubscriberListener*)&m_listener);

    if(mp_subscriber == nullptr)
        return false;


    return true;
}

DateSubscriber::~DateSubscriber() {
    // TODO Auto-generated destructor stub
    Domain::removeParticipant(mp_participant);
}

void DateSubscriber::SubListener::onSubscriptionMatched(Subscriber* /*sub*/,MatchingInfo& info)
{
    if(info.status == MATCHED_MATCHING)
    {
        n_matched++;
        std::cout << "Subscriber matched"<<std::endl;
    }
    else
    {
        n_matched--;
        std::cout << "Subscriber unmatched"<<std::endl;
    }
}

void DateSubscriber::SubListener::onNewDataMessage(Subscriber* sub)
{
    if(sub->takeNextData((void*)&m_Hello, &m_info))
    {
        if(m_info.sampleKind == ALIVE)
        {
            this->n_samples++;
            std::cout << "Message number " << m_Hello.num()<< " received: " << m_Hello.msg() <<std::endl;
        }
    }

}


void DateSubscriber::run()
{
    std::cout << "Subscriber running. Please press enter to stop the Subscriber" << std::endl;
    std::cin.ignore();
}

void DateSubscriber::run(uint32_t number)
{
    std::cout << "Subscriber running until "<< number << "samples have been received"<<std::endl;
    while(number < this->m_listener.n_samples)
        eClock::my_sleep(500);
}
