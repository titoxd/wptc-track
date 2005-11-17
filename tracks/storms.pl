#! /usr/bin/perl

# Format: year, name, extra, type
%named =
  (
   "natlantic" => [ (
# Retired storms: (since 1954)
#   [ (1954, 'Carol', 0, 'Hurricane') ],
#   [ (1954, 'Edna', 0, 'Hurricane') ],
#   [ (1954, 'Hazel', 0, 'Hurricane') ],
#   [ (1955, 'Connie', 0, 'Hurricane') ],
#   [ (1955, 'Diane', 0, 'Hurricane') ],
#   [ (1955, 'Ione', 0, 'Hurricane') ],
#   [ (1955, 'Janet', 0, 'Hurricane') ],
#   [ (1957, 'Audrey', 0, 'Hurricane') ],
#   [ (1959, 'Gracie', 0, 'Hurricane') ],
#   [ (1960, 'Donna', 0, 'Hurricane') ],
#   [ (1961, 'Carla', 0, 'Hurricane') ],
#   [ (1961, 'Hattie', 0, 'Hurricane') ],
#   [ (1963, 'Flora', 0, 'Hurricane') ],
#   [ (1964, 'Cleo', 0, 'Hurricane') ],
#   [ (1964, 'Dora', 0, 'Hurricane') ],
#   [ (1964, 'Hilda', 0, 'Hurricane') ],
#   [ (1965, 'Betsy', 0, 'Hurricane') ],
#   [ (1966, 'Inez', 0, 'Hurricane') ],
#   [ (1967, 'Beulah', 0, 'Hurricane') ],
#   [ (1969, 'Camille', 0, 'Hurricane') ],
#   [ (1970, 'Celia', 0, 'Hurricane') ],
#   [ (1972, 'Agnes', 0, 'Hurricane') ],
#   [ (1974, 'Carmen', 0, 'Hurricane') ],
#   [ (1974, 'Fifi', 0, 'Hurricane') ],
#   [ (1975, 'Eloise', 0, 'Hurricane') ],
#   [ (1977, 'Anita', 0, 'Hurricane') ],
#   [ (1979, 'David', 0, 'Hurricane') ],
#   [ (1979, 'Frederic', 0, 'Hurricane') ],
#   [ (1980, 'Allen', 0, 'Hurricane') ],
#   [ (1983, 'Alicia', 0, 'Hurricane') ],
		     [ (1985, 'Elena', 0, 'Hurricane') ],
#   [ (1985, 'Gloria', 0, 'Hurricane') ],
#   [ (1988, 'Gilbert', 0, 'Hurricane') ],
#   [ (1988, 'Joan', 0, 'Hurricane') ],
#   [ (1989, 'Hugo', 0, 'Hurricane') ],
#   [ (1990, 'Diana', 0, 'Hurricane') ],
#   [ (1990, 'Klaus', 0, 'Hurricane') ],
#   [ (1991, 'Bob', 0, 'Hurricane') ],
#   [ (1992, 'Andrew', 0, 'Hurricane') ],
#   [ (1995, 'Luis', 0, 'Hurricane') ],
#   [ (1995, 'Marilyn', 0, 'Hurricane') ],
#   [ (1995, 'Opal', 0, 'Hurricane') ],
#   [ (1995, 'Roxanne', 0, 'Hurricane') ],
#   [ (1996, 'Cesar', 0, 'Hurricane') ],
#   [ (1996, 'Fran', 0, 'Hurricane') ],
#   [ (1996, 'Hortense', 0, 'Hurricane') ],
#   [ (1998, 'Georges', 0, 'Hurricane') ],
#   [ (1998, 'Mitch', 0, 'Hurricane') ],
#   [ (1999, 'Floyd', 0, 'Hurricane') ],
#   [ (1999, 'Lenny', 0, 'Hurricane') ],
#   [ (2000, 'Keith', 0, 'Hurricane') ],
#   [ (2001, 'Allison', 0, 'Tropical Storm') ],
#   [ (2001, 'Iris', 0, 'Hurricane') ],
#   [ (2001, 'Michelle', 0, 'Hurricane') ],
#   [ (2002, 'Isidore', 0, 'Hurricane') ],
#   [ (2002, 'Lili', 0, 'Hurricane') ],
#   [ (2003, 'Fabian', 0, 'Hurricane') ],
#   [ (2003, 'Isabel', 0, 'Hurricane') ],
#   [ (2003, 'Juan', 0, 'Hurricane') ],
#   [ (2004, 'Charley', 0, 'Hurricane') ],
#   [ (2004, 'Frances', 0, 'Hurricane') ],
#   [ (2004, 'Ivan', 0, 'Hurricane') ],
#   [ (2004, 'Jeanne', 0, 'Hurricane') ],

# Non-retired but notable storms:
#   [ (1966, 'Faith', 1, 'Hurricane') ],
#   [ (1994, 'Alberto', 0, 'Tropical Storm') ],
#   [ (2003, 'Odette', 0, 'Tropical Storm') ],
#   [ (1994, 'Gordon', 0, 'Hurricane') ],
#   [ (2000, 'Alberto', 0, 'Hurricane') ],
#   [ (2004, 'Alex', 0, 'Hurricane') ],
#   [ (1996, 'Bertha', 0, 'Hurricane') ],
#   [ (1971, 'Ginger', 1, 'Hurricane') ],

# Non-retired Category 5 storms:
#   [ (1960, 'Ethel', 0, 'Hurricane') ],
#   [ (1971, 'Edith', 0, 'Hurricane') ],
#   [ (1958, 'Cleo', 0, 'Hurricane') ],
#   [ (1950, 'Dog', 0, 'Hurricane') ],

		    ) ],
  );

#Format: args, filename, name
@unnamed =
  (
# Pre-naming Atlantic storms:
#   [ ("--year 1856 --id 1", "1856 Last Island hurricane") ],
#    [ ("--year 1857 --id 2", "1857 Carolinas hurricane") ],
#   [ ("--year 1886 --id 5", "1886 Indianola hurricane") ],
#   [ ("--year 1893 --id 6 --extra 0", "1893 Sea Islands hurricane") ],
#   [ ("--year 1899 --id 3", "1899 San Ciriaco hurricane") ],
#   [ ("--year 1900 --wind 125 --extra 0", "1900 Galveston hurricane") ],
#   [ ("--year 1919 --wind 120", "1919 Florida Keys hurricane") ],
#   [ ("--year 1926 --wind 130", "1926 Miami hurricane") ],
#   [ ("--year 1928 --wind 140", "1928 Okeechobee hurricane") ],
#   [ ("--year 1935 --wind 140 --extra 0", "1935 Labor Day hurricane") ],
#   [ ("--year 1938 --wind 140", "1938 New England hurricane") ],
#   [ ("--year 1943 --id 1", "1943 Surprise hurricane") ],
#   [ ("--year 1944 --wind 120 --extra 0", "1944 Atlantic hurricane") ],
#   [ ("--year 1947 --wind 140", "1947 Fort Lauderdale hurricane") ],
#   [ ("--year 1959 --id 3 --extra 1", "1959 Escuminac hurricane") ],
#   [ ("--year 1932 --wind 140 --extra 0", "1932 Bahamas hurricane") ],

# 2005 storms
#   [ ("--input 2005/arlene.txt --format 1", "Arlene 2005", "Tropical Storm Arlene (2005)") ],
#   [ ("--input 2005/bret.txt --format 1", "Bret 2005", "Tropical Storm Bret (2005)") ],
#   [ ("--input 2005/cindy.txt --format 1", "Cindy 2005", "Tropical Storm Cindy (2005)") ],
#   [ ("--input 2005/dennis.txt --format 1", "Dennis 2005", "Hurricane Dennis (2005)") ],
#   [ ("--input 2005/emily.txt --format 1", "Emily 2005", "Hurricane Emily (2005)") ],
#   [ ("--input 2005/franklin.txt --format 1", "Franklin 2005", "Tropical Storm Franklin (2005)") ],
#   [ ("--input 2005/gert.txt --format 1", "Gert 2005", "Tropical Storm Gert (2005)") ],
#   [ ("--input 2005/harvey.txt --format 1", "Harvey 2005", "Tropical Storm Harvey (2005)") ],
#   [ ("--input 2005/irene.txt --format 1", "Irene 2005", "Hurricane Irene (2005)") ],
#   [ ("--input 2005/jose.txt --format 1", "Jose 2005", "Tropical Storm Jose (2005)") ],
#   [ ("--input 2005/katrina.txt --format 1", "Katrina 2005", "Hurricane Katrina (2005)") ],
#   [ ("--input 2005/lee.txt --format 1", "Lee 2005", "Tropical Storm Lee (2005)") ],
#   [ ("--input 2005/maria.txt --format 1", "Maria 2005", "Hurricane Maria (2005)") ],
#   [ ("--input 2005/nate.txt --format 1", "Nate 2005", "Hurricane Nate (2005)") ],
#   [ ("--input 2005/ophelia.txt --format 1", "Ophelia 2005", "Hurricane Ophelia (2005)") ],
#   [ ("--input 2005/philippe.txt --format 1", "Philippe 2005", "Hurricane Philippe (2005)") ],
#   [ ("--input 2005/rita.txt --format 1", "Rita 2005", "Hurricane Rita (2005)") ],
#   [ ("--input 2005/stan.txt --format 1", "Stan 2005", "Hurricane Stan (2005)") ],
#   [ ("--input 2005/tammy.txt --format 1", "Tammy 2005", "Tropical Storm Tammy (2005)") ],
#   [ ("--input 2005/vince.txt --format 1", "Vince 2005", "Hurricane Vince (2005)") ],
#   [ ("--input 2005/wilma.txt --format 1", "Wilma 2005", "Hurricane Wilma (2005)") ],
#   [ ("--input 2005/alpha.txt --format 1", "Alpha 2005", "Tropical Storm Alpha (2005)") ],
#   [ ("--input 2005/beta.txt --format 1", "Beta 2005", "Hurricane Beta (2005)") ],
  );

$wiki="../../pywikipedia/";
$storms="../tracks/tracks/";

sub mydosleep {
  my ($stime) = @_;
  if ($stime > 0) {
    print "  ...sleeping for $stime seconds.\n";
    sleep $stime;
  }
}

# Uncomment the next line to allow automatic uploads (DANGEROUS)
$real = 0;
if ($real != 0 && $ARGV[0] ne "--real") {
  print "Not running for real!\n";
  exit;
}

sub generate {
  my ($args, $filename, $descname) = @_;
  my $desc = "{{Hurricane auto track map|$descname}}";
  my $sleeptime = 60;
  my $res;

  $filename =~ s/ /_/g;

  print("Building $filename.\n");
  $res = system "./track $args --output \"$filename\"";
  if ($res != 0) {
    printf "Error!\n";
    exit;
  }
  print "  Uploading as $filename with $desc.\n";
  if ($real) {
    do {
      $res = system "cd $wiki && python upload.py -keep \"$storms$filename\" \"$desc\" 2>&1 >/dev/null";
      mydosleep($sleeptime);
      $sleeptime += 30;
    } while ($res != 0);
  }
}

system "mkdir -p storms";

@basins = keys %named;
foreach $basin (@basins) {
  foreach (@{ $named{$basin} }) {
    my ($year, $name, $extra, $type) = @{ $_ };
    my $filename = "storms/$name" . "_$year" . "_track.png";
    my $descname = "$type $name ($year)";

    generate("--extra $extra --year $year --name $name",
	     "storms/$name" . "_$year" . "_track.png",
	     "$type $name ($year)");
  }
}

foreach (@unnamed) {
  my ($args, $name, $name2) = @{ $_ };
  if (!defined $name2) {
    $name2 = $name;
  }

  generate($args, "storms/$name track.png", $name2);
}
