#!/usr/bin/sh

root=$(dirname $0)/..
find ${root} -iname '*.h' -o -iname '*.c' | xargs clang-format -i