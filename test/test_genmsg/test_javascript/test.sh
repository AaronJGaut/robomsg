#!/usr/bin/env sh
set -e
set -o pipefail

rm -rf artifacts
mkdir artifacts
genmsg -o artifacts/MyMessage.js ../common/MyMessage.msg
node msg_test.js
