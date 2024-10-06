#!/usr/bin/sh

asmDir=../assembler/
cd ${asmDir}
./build.sh
cd -

cliD=../computer-cli/
cd ${cliD}
./build.sh
cd -