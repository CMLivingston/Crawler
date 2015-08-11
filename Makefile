# crawler Makefile
#
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 
UTILFLAG=-lcurl


EXEC = crawler
OBJS = crawler.o web.o hashtable.o list.o
SRCS = crawler.c list.c hashtable.c web.c web.h hashtable.h list.h common.h

$(EXEC): $(OBJS) 
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS) $(UTILFLAG)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)
 								
.PHONY : clean


#clean function : deletes all temporary files
clean :
	rm -f *~
	rm -f *#
	rm -f *.o
	rm -f core.*
	rm -f vgcore.*
	rm -f *.gch
