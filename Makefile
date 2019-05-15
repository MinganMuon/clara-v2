# from http://nuclear.mutantstargoat.com/articles/make/

src = $(wildcard *.c)
obj = $(src:.c=.o)
dep = $(obj:.o=.d)

CFLAGS = -Wall
LDFLAGS = -lncurses

clara: $(obj)
	gcc -o $@ $^ $(LDFLAGS)

-include $(dep)

%.d: %.c
	gcc $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@

.PHONY: clean
clean:
	rm -f $(obj) clara 

.PHONY: cleandep
cleandep:
	rm -f $(dep)

