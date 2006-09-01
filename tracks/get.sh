storms="alberto beryl chris debby ernesto"

year=2006
year2=06

mkdir -p $year
function download() (
  for storm in $storms; do
    echo "Downloading $storm."
    (wget http://www.atmos.umd.edu/~stevenb/hurr/$year2/$storm/$storm.txt 2>&1 >/dev/null && mv $storm.txt $year/) #2>&1 >/dev/null
  done
)

function generate() (
  echo "" > $year/index.html
  for storm in $storms; do
    echo "Generating $storm."
    ./track --input $year/$storm.txt --format 1 && mv output.png $year/$storm.png
    echo "<a href=$storm.png>$storm</a><br>" >> $year/index.html
  done
)

download
#generate
