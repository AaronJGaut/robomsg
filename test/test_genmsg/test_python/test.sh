#!/usr/bin/env sh
set -e
set -o pipefail

rm -f MyMessage.py
genmsg -t python ../common/MyMessage.msg
python3 msg_test.py
