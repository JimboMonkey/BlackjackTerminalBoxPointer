
CC= g++
CFLAGS= -c
SOURCES= Blackjack.cpp Table.cpp Croupier.cpp Player.cpp Card.cpp Box.cpp Participant.cpp
OBJECTS= $(SOURCES:.cpp=.o)
EXECUTABLE= blackjack

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o blackjack
