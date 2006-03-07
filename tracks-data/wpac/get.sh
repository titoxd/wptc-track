#! /bin/bash

rm *.zip

# This downloads all the yearly zipped files.  Each contains one text file
# for every storm.  That means there are lots and lots of text files.
# Best-track data goes back to 1945 but some of the older seasons do not
# include the zipped files for some reason.  This program needs to be
# extended to handle downloading the individual files where necessary.

year=1945
while test $year != 2005; do
  post=s
  wget http://www.npmoc.navy.mil/jtwc/best_tracks/$year/$year$post-bwp/$year$post-bwp-full.zip || (echo "Couldn't download $year" > no$year.txt)
  year=$(($year + 1))
done

files=`ls *.zip`
for file in $files; do
  unzip $file
done
