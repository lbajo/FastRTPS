#include <fastcdr/FastBuffer.h>
#include <fastcdr/Cdr.h>

#include "DatePubSubTypes.h"

DatePubSubType::DatePubSubType() {
    setName("Date");
    m_typeSize = (uint32_t)Date::getMaxCdrSerializedSize() + 4 /*encapsulation*/;
    m_isGetKeyDefined = Date::isKeyDefined();
    m_keyBuffer = (unsigned char*)malloc(Date::getKeyMaxCdrSerializedSize()>16 ? Date::getKeyMaxCdrSerializedSize() : 16);
}

DatePubSubType::~DatePubSubType() {
    if(m_keyBuffer!=nullptr)
        free(m_keyBuffer);
}

bool DatePubSubType::serialize(void *data, SerializedPayload_t *payload) {
    Date *p_type = (Date*) data;
    eprosima::fastcdr::FastBuffer fastbuffer((char*) payload->data, payload->max_size);
    eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN,
            eprosima::fastcdr::Cdr::DDS_CDR);
    payload->encapsulation = ser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;
    ser.serialize_encapsulation();
    p_type->serialize(ser);
    payload->length = (uint32_t)ser.getSerializedDataLength();
    return true;
}

bool DatePubSubType::deserialize(SerializedPayload_t* payload, void* data) {
    Date* p_type = (Date*) data;
    eprosima::fastcdr::FastBuffer fastbuffer((char*)payload->data, payload->length);
    eprosima::fastcdr::Cdr deser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN,
            eprosima::fastcdr::Cdr::DDS_CDR);
    deser.read_encapsulation();
    payload->encapsulation = deser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;
    p_type->deserialize(deser);
    return true;
}

std::function<uint32_t()> DatePubSubType::getSerializedSizeProvider(void* data) {
    return [data]() -> uint32_t {
        return (uint32_t)type::getCdrSerializedSize(*static_cast<Date*>(data)) + 4;
    };
}

void* DatePubSubType::createData() {
    return (void*)new Date();
}

void DatePubSubType::deleteData(void* data) {
    delete((Date*)data);
}

bool DatePubSubType::getKey(void *data, InstanceHandle_t* handle) {
    if(!m_isGetKeyDefined)
        return false;
    Date* p_type = (Date*) data;
    eprosima::fastcdr::FastBuffer fastbuffer((char*)m_keyBuffer,Date::getKeyMaxCdrSerializedSize());
    eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::BIG_ENDIANNESS); 
    p_type->serializeKey(ser);
    if(Date::getKeyMaxCdrSerializedSize()>16)	{
        m_md5.init();
        m_md5.update(m_keyBuffer,(unsigned int)ser.getSerializedDataLength());
        m_md5.finalize();
        for(uint8_t i = 0;i<16;++i)    	{
            handle->value[i] = m_md5.digest[i];
        }
    }
    else    {
        for(uint8_t i = 0;i<16;++i)    	{
            handle->value[i] = m_keyBuffer[i];
        }
    }
    return true;
}

