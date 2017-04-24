#include "DatePublisher.h"
#include "DateSubscriber.h"

#include <fastrtps/Domain.h>

using namespace eprosima;
using namespace eprosima::fastrtps;

int main(int argc, char** argv)
{
    std::cout << "Starting " << std::endl;
	int type = 1;
	if (argc > 1)
	{
		if (strcmp(argv[1], "publisher") == 0)
		{
			type = 1;
		}
		else if (strcmp(argv[1], "subscriber") == 0)
		{
			type = 2;
		}
	}
	else
	{
        std::cout << "publisher OR subscriber argument needed" << std::endl;
		return 0;
	}
	
	switch(type)
	{
		case 1:
		{
			DatePublisher mypub;
			if (mypub.init())
			{
				mypub.run();
			}
			break;
		}
		case 2:
		{
			DateSubscriber mysub;
			if (mysub.init())
			{
				mysub.run();
			}
			break;
		}
	}
	
	return 0;
}
