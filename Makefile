CXX = gcc

SRCDIR=./src
INCDIR=./include
CCFILES += \
		$(SRCDIR)/fir.c \
		$(SRCDIR)/taps.c \
		$(SRCDIR)/main.c \

HFILES += \
		$(INCDIR)/fir.h \

LD_FLAGS         = -lm 

LD_LIBS          = 

OBJS             += $(patsubst %.c,%.c.o, $(CCFILES))

CFLAGS           =  -g -O0 -m64 -Wall

CFLAGS += -ffunction-sections -fdata-sections -Wno-unused-but-set-variable  -Wno-overflow -Wno-sign-compare

EXECUTABLE       = fir_process

INCLUDE_FLAGS    = -I$(SRCDIR) -I$(COMMDIR) -I$(NSDIR) -I$(AGCDIR) -I$(VADDIR)
#INCLUDE_FLAGS    = -I$(SRCDIR) -I$(COMMDIR) -I$(AGCDIR) -I$(VADDIR)

## Each subdirectory must supply rules for building sources it contributes
all: $(OBJS) $(CCFILES)
	$(CXX) -o $(EXECUTABLE) $(CFLAGS) $(OBJS) $(LD_FLAGS) 


$(OBJS): $(CCFILES) $(HFILES)
	$(CXX) $(CFLAGS) $(INCLUDE_FLAGS) -o $@ -c $*


.phony: clean


clean:
	@rm -f $(OBJS) $(EXECUTABLE)
