#!/usr/bin/sh

root=$(dirname $0)
root=${root}/..
cd ${root}

src=$(find . -name '*.[ch]')

sed -i 's|../../include/||g' ${src}
sed -i 's|../include/||g' ${src}
sed -i 's|include/||g' ${src}