FLAGS = -Wall -Wextra -g

EXECUTABLE = splite
inputdir = songsdir

all: $(EXECUTABLE)


tar: clean
	cd .. && tar -cvzf $(EXECUTABLE).tar.gz $(EXECUTABLE) && cd -

scrub: clean
	rm ~* *.swp *\#

run: $(EXECUTABLE)
	./$(EXECUTABLE) $(inputdir)

$(EXECUTABLE): Song.o User.o main.o Heap.o
	g++ Song.o User.o main.o Heap.o -o $(EXECUTABLE)

User.o: User.h User.cpp
	g++ -c $(FLAGS) User.cpp -o User.o

Heap.o: Heap.h Heap.cpp Song.h
	g++ -c $(FLAGS) Heap.cpp -o Heap.o

Song.o: Song.h Song.cpp
	g++ -c $(FLAGS) Song.cpp -o Song.o

main.o: main.cpp Parser.h Song.h User.h BSTree.h Heap.h
	g++ -c $(FLAGS) main.cpp -o main.o

memcheck: $(EXECUTABLE)
	valgrind ./$(EXECUTABLE).exe $(inputdir)

clean:
	rm -f *.o *.gch *.exe $(EXECUTABLE)
