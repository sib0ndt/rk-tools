CC=gcc
CFLAGS := -g -O3 -DUSE_OPENSSL -Wall
LDLIBS := -lssl -lcrypto
PREFIX ?= /usr
BINDIR ?= $(PREFIX)/bin
INSTALL ?= install

#CFLAGS := -DUSE_GCRYPT
#LDLIBS := -lgcrypt

TARGETS := afptool img_unpack img_maker mkkrnlimg

.PHONY: all clean install uninstall

all: ${TARGETS}

install: all
	$(INSTALL) -d "$(DESTDIR)$(BINDIR)"
	$(INSTALL) -m 0755 $(TARGETS) "$(DESTDIR)$(BINDIR)"

uninstall:
	rm -f $(addprefix "$(DESTDIR)$(BINDIR)"/,$(TARGETS))

clean:
	rm -f ${TARGETS}
