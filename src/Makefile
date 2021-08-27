# generic Makefile for building program from source
# PCH: sudo g++ -Wall -fexceptions -g src/common.h (for any 'common' file import)

SOURCE = main.cc bishop.cc white.cc config.cc black.cc pawn.cc knight.cc rook.cc queen.cc king.cc
CC = g++ -std=c++2a
EXECUTABLE = chess
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -w -g
OBJECT = $(SOURCE:.cpp=.o)

all: $(OBJECT)
	$(CC) $(SOURCE) $(LDFLAGS) -o $(EXECUTABLE)

$(OBJECT):
	$(CC) -c -o $@ $(@:.o=.cpp)

clean:
	rm -f $(EXECUTABLE) *.o *.out
