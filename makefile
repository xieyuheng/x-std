cc = gcc
ldflags = -lX11
cflags = -g -Wall -Wwrite-strings -Wextra -Werror -O0 -std=c99 -D_POSIX_C_SOURCE=199309L -pedantic

src = $(shell find src -name '*.c')
headers = $(shell find src -name '*.h')
lib = $(patsubst src/%,lib/%,$(patsubst %.c,%.o,$(src)))
bin = bin/bifer

.PHONY: all
all: bin/bifer

.PHONY: run
run: bin/bifer
	./bin/bifer

.PHONY: test
test: self-test 

.PHONY: self-test
self-test: bin/bifer
	./bin/bifer self-test

bin/bifer: $(lib) lib/bifer.o
	mkdir -p $(dir $@); $(cc) $^ $(ldflags) -o $@

lib/%.o: src/%.c $(headers)
	mkdir -p $(dir $@); $(cc) -c $(cflags) $< -o $@

.PHONY: clean
clean:
	rm -rf lib bin
