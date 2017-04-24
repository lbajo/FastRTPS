CPP=g++
LN=g++
AR=ar
CP=cp
SYSLIBS= -ldl -lnsl -lm -lpthread -lrt
DEFINES= 
COMMON_CFLAGS= -c -Wall -D__LITTLE_ENDIAN__ -std=c++11

## CHOOSE HERE BETWEEN 32 and 64 bit architecture

##32 BIT ARCH:
#COMMON_CFLAGS+= -m32 -fpic
#LDFLAGS=-m32

#64BIT ARCH:
COMMON_CFLAGS+= -m64 -fpic
LDFLAGS=-m64

CFLAGS = $(COMMON_CFLAGS) -O2

INCLUDES= -I.

LIBS = -lfastcdr -lfastrtps $(SYSLIBS)

DIRECTORIES= output.dir bin.dir

all: $(DIRECTORIES) DateExample

DATEEXAMPLE_TARGET= bin/DateExample

DATEEXAMPLE_SRC_CXXFILES=

DATEEXAMPLE_SRC_CPPFILES= DateExample/Date.cxx \
								DateExample/DatePubSubTypes.cxx \
								DateExample/DatePublisher.cpp \
								DateExample/DateSubscriber.cpp \
								DateExample/Date_main.cpp 


DATEEXAMPLE_SRCS= $(DATEEXAMPLE_SRC_CXXFILES) $(DATEEXAMPLE_SRC_CPPFILES)

DATEEXAMPLE_SOURCES_DIRS_AUX= $(foreach srcdir, $(dir $(DATEEXAMPLE_SRCS)), $(srcdir))
DATEEXAMPLE_SOURCES_DIRS= $(shell echo $(DATEEXAMPLE_SOURCES_DIRS_AUX) | tr " " "\n" | sort | uniq | tr "\n" " ")

DATEEXAMPLE_OBJS = $(foreach obj,$(notdir $(addsuffix .o, $(DATEEXAMPLE_SRCS))), output/$(obj))
DATEEXAMPLE_DEPS = $(foreach dep,$(notdir $(addsuffix .d, $(DATEEXAMPLE_SRCS))), output/$(dep))

OBJS+=  $(DATEEXAMPLE_OBJS)
DEPS+=  $(DATEEXAMPLE_DEPS)

DateExample: $(DATEEXAMPLE_TARGET)

$(DATEEXAMPLE_TARGET): $(DATEEXAMPLE_OBJS)
	$(LN) $(LDFLAGS) -o $(DATEEXAMPLE_TARGET) $(DATEEXAMPLE_OBJS) $(LIBS)

vpath %.cxx $(DATEEXAMPLE_SOURCES_DIRS)
vpath %.cpp $(DATEEXAMPLE_SOURCES_DIRS)

output/%.cxx.o:%.cxx
	@echo Calculating dependencies $<
	@$(CC) $(CFLAGS) -MM $(CFLAGS) $(INCLUDES) $< | sed "s/^.*:/output\/&/g" > $(@:%.cxx.o=%.cxx.d)
	@echo Compiling $<
	@$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

output/%.cpp.o:%.cpp
	@echo Calculating dependencies $<
	@$(CPP) $(CFLAGS) -MM $(CFLAGS) $(INCLUDES) $< | sed "s/^.*:/output\/&/g" > $(@:%.cpp.o=%.cpp.d)
	@echo Compiling $<
	@$(CPP) $(CFLAGS) $(INCLUDES) $< -o $@

.PHONY: DateExample

clean:
	@rm -f $(OBJS)
	@rm -f $(DEPS)

ifneq ($(MAKECMDGOALS), clean)
-include $(DEPS)
endif

%.dir : 
	@echo "Checking directory $*"
	@if [ ! -d $* ]; then \
		echo "Making directory $*"; \
		mkdir -p $* ; \
	fi;
