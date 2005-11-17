storms="arlene bret cindy dennis emily franklin gert harvey irene jose katrina lee maria nate ophelia philippe rita stan tammy vince wilma alpha beta"

function download() (
  for storm in $storms; do
    wget http://www.atmos.umd.edu/~stevenb/hurr/05/$storm/$storm.txt && mv $storm.txt 2005/
  done
)

#download

echo "" > 2005/index.html
for storm in $storms; do
  ./track --input 2005/$storm.txt --format 1 && mv output.png 2005/$storm.png
  echo "<a href=$storm.png>$storm</a><br>" >> 2005/index.html
done
