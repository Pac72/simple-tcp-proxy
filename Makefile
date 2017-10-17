PROG=simple-tcp-proxy
CFLAGS=-Wall

all: ${PROG}

simple-tcp-proxy: simple-tcp-proxy.o log.o

$(PROG).static: simple-tcp-proxy.o log.o
	$(CC) -static -o ${@} $(PROG).o
	strip $@

.PHONY: clean

clean:
	@find \( -name '*.[oas]' -o -name $(PROG) -o -name core -o -name '*~' \) \
		-type f -print | xargs rm -f
