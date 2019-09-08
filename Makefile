# Config variables

CFLAGS := -fPIC -g -MD -MP
INCLUDE_PATH := -I./include
LIB_PATH := -L./lib

# PHONY rules

all: libs bins

libs:

bins: bin/test-buffer-stream bin/genmsg

clean:
	rm -rf lib/lib*.so bin build

.PHONY: all libs bins clean

# bins

bin/test-buffer-stream: build/test_buffer_stream.o | bin
	gcc -o $@ $<

bin/genmsg: scripts/genmsg | bin
	cp $< $@

# Shared libraries


# Object files

build/%.o: src/%.c | build
	gcc ${INCLUDE_PATH} ${CFLAGS} -o $@ -c $<

# Header dependancies
-include $(wildcard build/*.d)

# Directories

build lib bin:
	mkdir -p $@
