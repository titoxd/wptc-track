#!/bin/bash

ARGS="--res 128 --bg bgs/bg2048.png"

function yearly() (
  echo "<td align=left valign=top nowrap><h3>$basin</h3>" >>yearly/index.html
  done=no
  while true; do
    echo $basin-$year

    nice -n 19 ./track --year $year --basin $basin 2>/dev/null || break
    echo "$year - <a href=$basin$year.png>season</a>" >> yearly/index.html
    mv output.png yearly/$basin$year.png

    id=1
    while true; do
      nice -n 19 ./track --year $year --basin $basin --id $id $ARGS 2>/dev/null || break
      mv output.png yearly/$basin$year-$id.png
      echo " - <a href=$basin$year-$id.png>$id</a>" >>yearly/index.html
      id=$(($id + 1))
    done

    echo "<br>" >> yearly/index.html

    year=$(($year + 1))
  done
  echo "</td>" >>yearly/index.html
)

rm -f yearly/*.png yearly/*.html
echo "<table><tr>" > yearly/index.html

basin=natlantic
year=1851
#year=2003
yearly

basin=epac
year=1949
#year=2003
yearly

basin=wpac
year=1945
#year=2003
yearly

basin=south
year=1945
#year=2003
yearly

basin=nindian
year=1945
#year=2003
yearly

echo "</tr></table>" >>yearly/index.html
