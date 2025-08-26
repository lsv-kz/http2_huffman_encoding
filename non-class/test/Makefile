CFLAGS = -Wall -O2

CC = c++

OBJSDIR = objs
$(shell mkdir -p $(OBJSDIR))

DEPS = ../../bytes_array.h

OBJS = $(OBJSDIR)/test.o \
	$(OBJSDIR)/huffman_code.o \

test: $(OBJS)
	$(CC) $(CFLAGS) -o $@  $(OBJS)

$(OBJSDIR)/test.o: test.cpp $(DEPS)
	$(CC) $(CFLAGS) -c test.cpp -o $@

$(OBJSDIR)/huffman_code.o: ../huffman_code.cpp $(DEPS)
	$(CC) $(CFLAGS) -c ../huffman_code.cpp -o $@


clean:
	rm -f test
	rm -f $(OBJSDIR)/*.o
