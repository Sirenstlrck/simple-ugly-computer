#!/usr/bin/sh

root=$(dirname $0)/../..
cd $root

cp ./scripts/hooks/pre-commit ./.git/hooks