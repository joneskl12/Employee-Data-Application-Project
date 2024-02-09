CC= gcc
CFLAGS= -Wall


# Productions
p2 : cmsc257-p2.c p2-support.c
	$(CC) $(CFLAGS) cmsc257-p2.c p2-support.c -o p2


clean:
	rm -f p2
