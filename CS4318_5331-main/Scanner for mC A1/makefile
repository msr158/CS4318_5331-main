CC = gcc
CFLAGS = -I./src -std=gnu99
LEX=lex

obj/scanner: obj/lex.yy.o obj/driver.o
	gcc $(CFLAGS) -o scanner obj/driver.o obj/lex.yy.o -lfl
.PHONY: clean test

obj/driver.o: src/driver.c
	@mkdir -p obj
	$(CC)  $(CFLAGS) -c $< -o $@

obj/lex.yy.o: obj/lex.yy.c
	gcc $(CFLAGS) -c $< -o $@

obj/lex.yy.c: src/scanner.l
	@mkdir -p obj
	lex -o $@ $<

clean:
	rm -rf obj
	rm -f lex.yy.* *.o *~ scanner

test: obj/scanner
	@python ./test/testScanner.py
