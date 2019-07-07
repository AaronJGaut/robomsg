#!/usr/bin/env sh
set -e
set -o pipefail

rm -f MyMessage.h msg-test
genmsg -t c ../common/MyMessage.msg
gcc -o msg-test msg_test.c
./msg-test
