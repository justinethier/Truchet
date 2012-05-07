#!/bin/bash
cd images/gallery
rm -f *thumb*
find . -type f -name '*.png' | while read filename; do echo "converting ${filename}"; convert -size 128x96 -resize 128x96 +profile '*' "${filename}" "`echo "${filename}" | sed -e 's/\.png$/\.thumb.png/'`"; done
