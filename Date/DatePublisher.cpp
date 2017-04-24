#include "DatePublisher.h"
#include <fastrtps/participant/Participant.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/PublisherAttributes.h>
#include <fastrtps/publisher/Publisher.h>
#include <fastrtps/Domain.h>
#include <fastrtps/utils/eClock.h>
#include <string>
#include <iostream>
#include <ctime>

using namespace std;

DatePublisher::DatePublisher():mp_participant(nullptr),
mp_publisher(nullptr)
{


}

bool DatePublisher::init()
{
    //m_Hello.num(0);
    //m_Hello.msg("Date and time");
    ParticipantAttributes PParam;
    PParam.rtps.defaultSendPort = 11511;
    PParam.rtps.use_IP6_to_send = true;
    PParam.rtps.builtin.use_SIMPLE_RTPSParticipantDiscoveryProtocol = true;
    PParam.rtps.builtin.use_SIMPLE_EndpointDiscoveryProtocol = true;
    PParam.rtps.builtin.m_simpleEDP.use_PublicationReaderANDSubscriptionWriter = true;
    PParam.rtps.builtin.m_simpleEDP.use_PublicationWriterANDSubscriptionReader = true;
    PParam.rtps.builtin.domainId = 80;
    PParam.rtps.builtin.leaseDuration = c_TimeInfinite;
    PParam.rtps.setName("Participant_pub");
    mp_participant = Domain::createParticipant(PParam);

    if(mp_participant==nullptr)
        return false;

    Domain::registerType(mp_participant,&m_type);

    PublisherAttributes Wparam;
    Wparam.topic.topicKind = NO_KEY;
    Wparam.topic.topicDataType = "Date";
    Wparam.topic.topicName = "DateTopic";
    Wparam.topic.historyQos.kind = KEEP_LAST_HISTORY_QOS;
    Wparam.topic.historyQos.depth = 30;
    Wparam.topic.resourceLimitsQos.max_samples = 50;
    Wparam.topic.resourceLimitsQos.allocated_samples = 20;
    Wparam.times.heartbeatPeriod.seconds = 2;
    Wparam.times.heartbeatPeriod.fraction = 200*1000*1000;
    Wparam.qos.m_reliability.kind = RELIABLE_RELIABILITY_QOS;
    mp_publisher = Domain::createPublisher(mp_participant,Wparam,(PublisherListener*)&m_listener);
    if(mp_publisher == nullptr)
        return false;

    return true;

}

DatePublisher::~DatePublisher()
{
    // TODO Auto-generated destructor stub
    Domain::removeParticipant(mp_participant);
}

void DatePublisher::PubListener::onPublicationMatched(Publisher* /*pub*/,MatchingInfo& info)
{
    if(info.status == MATCHED_MATCHING)
    {
        n_matched++;
        std::cout << "Publisher matched"<<std::endl;
    }
    else
    {
        n_matched--;
        std::cout << "Publisher unmatched"<<std::endl;
    }
}

void DatePublisher::run(uint32_t samples)
{

    for(int i = 0; i<50; i++)
    {
        time_t now = time(0); 
        string dt = ctime(&now);
        tm *gmtm = gmtime(&now);
        dt = asctime(gmtm);
        m_Hello.msg() = dt;
        std::cout << "Message number "<< m_Hello.num()<<": " <<m_Hello.msg() <<std::endl;
        
        if(m_listener.n_matched>0)
        {
            m_Hello.num(m_Hello.num()+1);
            mp_publisher->write((void*)&m_Hello);
        }

        eClock::my_sleep(100);
    }
}
/*
bool DatePublisher::publish()
{
    if(m_listener.n_matched>0)
    {
        m_Hello.num(m_Hello.num()+1);
        mp_publisher->write((void*)&m_Hello);
        return true;
    }
    return false;
}
*/
