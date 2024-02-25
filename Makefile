clean:
	rm -rf bin
	rm -rf reports

test: clean
	mkdir -p bin
	gcc --coverage -g -O0 src/row.c src/table.c src/statement.c src/test.c -o bin/test
	./bin/test

cover: test
	bash cover.sh

build: cover
	gcc src/row.c src/table.c src/statement.c src/main.c -o bin/main
