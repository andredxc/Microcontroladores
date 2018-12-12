TARGET1=testPWM
SRC1=testPWM.c

TARGET2=testVoltage
SRC2=testVoltage.c

TARGET3=testEnd
SRC3=testEnd.c

FLAGS=-Wall -g -MMD
INCLUDE=-I../api -I../include
LIBDIR=
LIBS=../api/api.a

CC=$(CROSS_COMPILE)gcc
CFLAGS=$(FLAGS) $(INCLUDE)
LDFLAGS=$(LIBDIR) $(LIBS)

all: testPWM.c testVoltage.c
	$(CC) $(CFLAGS) -o $(TARGET1) $(SRC1) $(LDFLAGS)
	$(CC) $(CFLAGS) -o $(TARGET2) $(SRC2) $(LDFLAGS)
	$(CC) $(CFLAGS) -o $(TARGET3) $(SRC3) $(LDFLAGS)

clean:
	rm -f *~ *.bak *.o *.d

distclean: clean
	rm -f $(TARGET1) $(TARGET2) $(TARGET3)
