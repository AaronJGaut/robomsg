#!/usr/bin/env sh
set -e
set -o pipefail

rm -f MyMessage.js
genmsg -t javascript ../common/MyMessage.msg
node msg_test.js
