PROYECTO=servidor_rtcc
OBJECTS:=$(patsubst %.c,%.o,$(wildcard *.c))
DESTDIR=/usr/local/bin
DAEMONDIR=/etc/systemd/system
DAEMON_SCRIPT=servidor_rtcc.service
CFLAGS=-Wall
LFLAGS=-lm -lpthread -lwiringPi
CC=gcc

all: $(PROYECTO)

%.o: %.c
	${CC} -c $< $(CFLAGS)

$(PROYECTO): ${OBJECTS}
	$(CC) $^ -o $@ $(LFLAGS)

.PHONY: clean

install: all 
	if [ ! -d $(DESTDIR) ]; then \
		sudo mkdir $(DESTDIR); \
	fi; \
	sudo cp $(PROYECTO) $(DESTDIR)

uninstall:
	sudo rm $(DESTDIR)/$(PROYECTO)

daemon:
	if [ ! -f $(DAEMONDIR)/$(DAEMON_SCRIPT) ]; then \
		sudo cp $(DAEMON_SCRIPT) $(DAEMONDIR); \
	fi; \
	sudo systemctl enable servidor_rtcc.service
	sudo systemctl start servidor_rtcc.service
	
clean: 
	rm -f *.o $(PROYECTO)

