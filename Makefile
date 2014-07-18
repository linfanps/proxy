PROJECT_NAME = "proxy"
VERSION = "0.0.1"
CFLAGS = -Wall -W -g
OBJS = log.o config.o net.o util.o packet.o
LIBS = -lpthread
TARGET = proxy


all: $(TARGET)

proxy: proxy.c $(OBJS)
	gcc proxy.c $(OBJS) $(LIBS) -o proxy

clean:
	rm -rf $(OBJS) $(TARGET)
