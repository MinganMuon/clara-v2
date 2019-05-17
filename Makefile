# from http://nuclear.mutantstargoat.com/articles/make/

src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)
dep = $(obj:.o=.d)

CFLAGS = -Wall
LDFLAGS = -lncurses

clara: $(obj)
	g++ -o $@ $^ $(LDFLAGS)

-include $(dep)

%.d: %.c
	g++ $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@

.PHONY: clean
clean:
	rm -f $(obj) clara 

.PHONY: cleandep
cleandep:
	rm -f $(dep)

