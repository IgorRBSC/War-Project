CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -g
OBJS = main.o territory.o attack.o mission.o utils.o

all: war_game

war_game: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c territory.h attack.h mission.h utils.h
	$(CC) $(CFLAGS) -c main.c -o main.o

clean:
	rm -f *.o war_game
