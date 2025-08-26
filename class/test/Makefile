CFLAGS = -Wall -O2

CC = c++

OBJSDIR = objs
$(shell mkdir -p $(OBJSDIR))

DEPS = ../../bytes_array.h ../huffman.h

OBJS = $(OBJSDIR)/test.o 

test: $(OBJS)
	$(CC) $(CFLAGS) -o $@  $(OBJS)

$(OBJSDIR)/test.o: test.cpp $(DEPS)
	$(CC) $(CFLAGS) -c test.cpp -o $@

clean:
	rm -f test
	rm -f $(OBJSDIR)/*.o
