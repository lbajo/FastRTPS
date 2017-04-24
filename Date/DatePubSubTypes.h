#ifndef _DATE_PUBSUBTYPES_H_
#define _DATE_PUBSUBTYPES_H_

#include <fastrtps/TopicDataType.h>

using namespace eprosima::fastrtps;

#include "Date.h"

class DatePubSubType : public TopicDataType {
public:
        typedef Date type;

	DatePubSubType();
	virtual ~DatePubSubType();
	bool serialize(void *data, SerializedPayload_t *payload);
	bool deserialize(SerializedPayload_t *payload, void *data);
        std::function<uint32_t()> getSerializedSizeProvider(void* data);
	bool getKey(void *data, InstanceHandle_t *ihandle);
	void* createData();
	void deleteData(void * data);
	MD5 m_md5;
	unsigned char* m_keyBuffer;
};

#endif
