#!/bin/bash
cd images/gallery
rm -f *thumb*
for img in *.png; do
    filename=${img%.*}
    convert "$filename.png[128x96+5+5]" "$filename.thumb.png"
done
