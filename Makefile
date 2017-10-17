PROG=simple-tcp-proxy
CFLAGS=-Wall

all: ${PROG}

$(PROG): $(PROG).o

$(PROG).static: $(PROG).o
	$(CC) -static -o ${@} $(PROG).o
	strip $@

.PHONY: clean

clean:
	@find \( -name '*.[oas]' -o -name $(PROG) -o -name core -o -name '*~' \) \
		-type f -print | xargs rm -f
