# Config variables

CFLAGS := -fPIC -g -MD -MP
INCLUDES := -I./include

# PHONY rules

all: libs bins

libs:

bins: bin/test-buffer-stream bin/genmsg

test: all
	@runtests

clean:
	rm -rf lib/lib*.so bin build

.PHONY: all libs bins clean test

# bins

bin/test-buffer-stream: build/test_buffer_stream.o | bin
	gcc -o bin/test-buffer-stream build/test_buffer_stream.o

bin/genmsg: scripts/genmsg | bin
	cp $< $@

# Shared libraries


# Object files

build/%.o: src/%.c | build
	gcc ${INCLUDES} ${CFLAGS} -o $@ -c $<

-include $(wildcard build/*.d)

# Directories

build:
	mkdir -p build

lib:
	mkdir -p lib

bin:
	mkdir -p bin
