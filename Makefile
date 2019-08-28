hmac-sha1.o: hmac-sha1.c
	gcc -I/usr/local/ssl/include/ -L/usr/local/ssl/lib/ -o hmac-sha1 hmac-sha1.c -lcrypto
