


all:
	$(MAKE) -C test
	$(MAKE) -C test/clients

clean:
	rm -f server client_lookup client_delete server tcp_client udp_client
