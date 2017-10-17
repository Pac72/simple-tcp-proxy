PROG=simple-tcp-proxy
CFLAGS=-Wall

all: ${PROG}

$(PROG): $(PROG).o
	$(CC) -o $(PROG) $(PROG).o

$(PROG).static: $(PROG).o
	$(CC) -static -o ${@} $(PROG).o
	strip $@

.PHONY: clean

clean:
	-rm $(PROG) $(PROG).o $(PROG).core
