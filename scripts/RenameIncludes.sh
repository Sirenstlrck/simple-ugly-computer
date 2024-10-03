#!/usr/bin/sh

root=$(dirname $0)
root=${root}/..
cd ${root}

src=$(find . -name '*.[ch]')

sed -i 's|myTerminal.h|terminal.h|g' ${src}
sed -i 's|mySimpleComputer.h|simple_computer.h|g' ${src}
sed -i 's|myBigChars.h|big_chars.h|g' ${src}
sed -i 's|myConsole.h|console.h|g' ${src}
