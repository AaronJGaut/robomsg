#!/usr/bin/env sh
set -e
set -o pipefail

rm -rf artifacts
mkdir artifacts
genmsg -o artifacts/MyMessage.h ../common/MyMessage.msg
gcc -I./artifacts -o artifacts/msg-test msg_test.c
artifacts/msg-test
