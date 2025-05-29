CC = gcc
CFLAGS = -Wall -O2
LIBS_PUB = -lnl-3 -lnl-genl-3 -lnl-route-3 -lmosquitto -lcjson
LIBS_SUB = -lmosquitto

PUBLISHER_SRC = scan-report_pub-public-broker.c
SUBSCRIBER_SRC = scan-report_sub-public-broker.c

PUBLISHER_BIN = pub
SUBSCRIBER_BIN = sub

all: $(PUBLISHER_BIN) $(SUBSCRIBER_BIN)

$(PUBLISHER_BIN): $(PUBLISHER_SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS_PUB)

$(SUBSCRIBER_BIN): $(SUBSCRIBER_SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS_SUB)

clean:
	rm -f $(PUBLISHER_BIN) $(SUBSCRIBER_BIN)

