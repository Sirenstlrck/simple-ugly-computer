#!/usr/bin/sh

currDir=$(dirname $0)

asmDir=${currDir}/../assembler/
cd ${asmDir}
./build.sh
cd -

cliDir=${currDir}/../computer-cli/
cd ${cliDir}
./build.sh
cd -