CFLAGS=-Wall -Werror -std=gnu99 -pedantic -ggdb3
SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(SRCS))
PROGRAM=test

$(PROGRAM) : $(OBJS)
	gcc $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	gcc -c $(CFLAGS) $<

clean:
	rm -f $(OBJS) $(PROGRAM) *~

deck.o: deck.h
cards.o: cards.h
eval.o: eval.h
future.o: future.h
input.o: input.h
