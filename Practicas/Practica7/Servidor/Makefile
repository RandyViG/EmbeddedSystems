PROYECTO=servidor_rtcc
OBJECTS:=$(patsubst %.c,%.o,$(wildcard *.c))
DESTDIR=/usr/local/bin
DAEMONDIR=/etc/systemd/system
DAEMON_SCRIPT=servidor_rtcc.service
CFLAGS=-Wall
LFLAGS=-lm -lpthread
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
	sudo cp $(DAEMON_SCRIPT) $(DAEMONDIR)
	sudo systemctl enable servidor_rtcc.service
	
clean: 
	rm -f *.o $(PROYECTO)

