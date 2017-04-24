
#ifdef _WIN32
namespace { char dummy; }
#endif

#include "Date.h"

#include <fastcdr/Cdr.h>

#include <fastcdr/exceptions/BadParamException.h>
using namespace eprosima::fastcdr::exception;

#include <utility>

Date::Date()
{
    m_num = 0;

}

Date::~Date()
{
}

Date::Date(const Date &x)
{
    m_num = x.m_num;
    m_msg = x.m_msg;
}

Date::Date(Date &&x)
{
    m_num = x.m_num;
    m_msg = std::move(x.m_msg);
}

Date& Date::operator=(const Date &x)
{
    m_num = x.m_num;
    m_msg = x.m_msg;
    
    return *this;
}

Date& Date::operator=(Date &&x)
{
    m_num = x.m_num;
    m_msg = std::move(x.m_msg);
    
    return *this;
}

size_t Date::getMaxCdrSerializedSize(size_t current_alignment)
{
    size_t initial_alignment = current_alignment;
            
    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);

    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4) + 255 + 1;


    return current_alignment - initial_alignment;
}

size_t Date::getCdrSerializedSize(const Date& data, size_t current_alignment)
{
    size_t initial_alignment = current_alignment;
            
    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);

    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4) + data.msg().size() + 1;


    return current_alignment - initial_alignment;
}

void Date::serialize(eprosima::fastcdr::Cdr &scdr) const
{
    scdr << m_num;

    if(m_msg.length() <= 255)
    scdr << m_msg;
    else
        throw eprosima::fastcdr::exception::BadParamException("msg field exceeds the maximum length");
}

void Date::deserialize(eprosima::fastcdr::Cdr &dcdr)
{
    dcdr >> m_num;
    dcdr >> m_msg;
}

size_t Date::getKeyMaxCdrSerializedSize(size_t current_alignment)
{
	size_t current_align = current_alignment;
            



    return current_align;
}

bool Date::isKeyDefined()
{
    return false;
}

void Date::serializeKey(eprosima::fastcdr::Cdr &scdr) const
{
	 
	 
}
