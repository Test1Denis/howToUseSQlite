all: test_sqlite

test_sqlite: main.o sqlite3.o base_sqlite.o
	g++ main.o sqlite3.o base_sqlite.o -o test_sqlite
	
main.o: main.cpp
	g++ -c main.cpp
	
sqlite3.o: sqlite3.c
	gcc -c sqlite3.c
	
base_sqlite.o: base_sqlite.cpp
	g++ -c base_sqlite.cpp
	
clean:
	rm -rf *.o *.exe