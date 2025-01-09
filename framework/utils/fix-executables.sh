#/bin/bash

set -e
cd "$(dirname "$0")"
cd ../..

# This avoid random failures from student's files loosing
# the executable bit due to WSL (or Windows in general,
# or the GitHub ZIP not having executable bits set).
chmod -R +x framework assign1 assign2 assign3 assign4