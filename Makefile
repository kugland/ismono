CC     := gcc
CFLAGS := -O2 -fomit-frame-pointer -ffast-math -march=native

all: ismono

ismono: ismono.c
	$(CC) $(CFLAGS) -o ismono ismono.c -lsndfile
	strip ismono

install:
	install -o root -g root -m 755 ismono /usr/local/bin/ismono

clean:
	rm ismono
