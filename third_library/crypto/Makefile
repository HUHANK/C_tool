TARGS=libcrypto.a
CC= gcc
CFLAGS= -c -w
O_SRC=CSLCoder.o CSLRsa.o bignum.o rsa.o CRC.o

$(TARGS):$(O_SRC)
	ar rcs $(TARGS) $(O_SRC)

CSLCoder.o: CSLCoder.c
	$(CC) $(CFLAGS) CSLCoder.c

CSLRsa.o: CSLRsa.c
	$(CC) $(CFLAGS) CSLRsa.c

bignum.o: bignum.c
	$(CC) $(CFLAGS) bignum.c

rsa.o: rsa.c
	$(CC) $(CFLAGS) rsa.c

CRC.o: CRC.c
	g++  $(CFLAGS) CRC.c


clean:
	rm -rf $(O_SRC) $(TARGS)
