clean:
	rm -rf bin
	rm -rf reports
	rm -rf *.db

test: clean
	mkdir -p bin
	gcc src/input.c src/row.c src/table.c src/statement.c src/test.c -o bin/test
	./bin/test

cover: clean
	mkdir -p bin
	gcc --coverage -g -O0 src/input.c src/row.c src/table.c src/statement.c src/test.c -o bin/test
	./bin/test
	bash cover.sh

build: test
	gcc src/input.c src/row.c src/table.c src/statement.c src/main.c -o bin/main

