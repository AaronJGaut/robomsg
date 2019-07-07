#!/usr/bin/env sh
set -e
set -o pipefail

rm -rf artifacts
mkdir artifacts
genmsg -o artifacts/MyMessage.py ../common/MyMessage.msg
python3 msg_test.py
