#! /usr/bin/perl

%default =
  (
   "natlantic" => [ ("Hurricane", "") ],
   "epac" =>  [ ("Hurricane", "") ],
   "wpac" =>  [ ("Typhoon", "") ],
   "nindian" =>  [ ("Tropical Cyclone", "") ],
   "south" =>  [ ("Cyclone", "--negy 1") ]
  );

%namedsimple = 
  (
   "natlantic" =>
   [(
     "1950" =>
     [(
       #'Able', 'Baker', 'Charlie', 'Dog', 'Easy', 'Fox',
       #'George', 'How', 'Item', 'Jig', 'King', 'Love', 
      )],
     "1951" =>
     [(
       #'Able', 'Baker', 'Charlie', 'Dog', 'Easy',
       #'Fox', 'George', 'How', 'Item', 'Jig',
      )],
     "1952" =>
     [(
       #'Able', 'Baker', 'Charlie', 'Dog', 'Easy', 'Fox', 
      )],
     "1953" =>
     [(
       #'Alice', 'Barbara', 'Carol', 'Dolly', 'Edna', 'Florence', 'Gail', 
       #'Hazel', 
      )],
     "1954" =>
     [(
       #'Barbara', 'Carol', 'Dolly', 'Edna',
       #'Florence', 'Gilda', 'Hazel',
       # Alice1 and Alice2 are below.
      )],
     "1955" =>
     [(
       #'Brenda', 'Connie', 'Diane', 'Edith', 'Flora', 'Gladys',
       #'Hilda', 'Ione', 'Janet', 'Katie',
      )],
     "1956" =>
     [(
       #'Anna', 'Betsy', 'Carla', 'Dora', 'Ethel', 'Flossy', 'Greta', 
      )],
     "1957" =>
     [(
       #'Audrey', 'Bertha', 'Carrie',
       #'Debbie', 'Esther', 'Frieda', 
      )],
     "1958" =>
     [(
       #'Alma', 'Becky', 'Cleo',
       #'Daisy', 'Ella', 'Fifi', 'Gerda', 
       #'Helene', 'Ilsa', 'Janice', 
      )],
     "1959" =>
     [(
       #'Arlene', 'Beulah', 'Cindy', 'Debra', 'Edith', 'Flora',
       #'Gracie', 'Hannah', 'Irene', 'Judith', 
      )],
     "1960" =>
     [(
       #'Abby', 'Brenda', 'Cleo',
       #'Donna', 'Ethel', 'Florence', 
      )],
     "1961" =>
     [(
       #'Anna', 'Betsy', 'Carla', 'Debbie', 'Esther', 'Frances',
       #'Gerda', 'Hattie', 'Jenny', 'Inga'
       # Hattie-Simone-Inga is also below
      )],
     "1962" =>
     [(
       #'Alma', 'Becky', 'Celia', 'Daisy', 'Ella', 
      )],
     "1963" =>
     [(
       #'Arlene', 'Beulah', 'Cindy', 'Debra', 'Edith',
       #'Flora', 'Ginny', 'Helena',
      )],
     "1964" =>
     [(
       #'Abby', 'Brenda', 'Cleo', 'Dora',
       #'Ethel', 'Florence', 'Gladys', 'Hilda', 'Isbell',
      )],
     "1965" =>
     [(
       #'Anna', 'Betsy', 'Carol', 'Debbie', 'Elena', 
      )],
     "1966" =>
     [(
       #'Alma', 'Becky', 'Celia', 'Dorothy', 'Ella',
       #'Greta', 'Hallie', 'Inez', 'Judith', 'Lois', 
       # Faith is below
      )],
     "1967" =>
     [(
       #'Arlene', 'Beulah',
       #'Chloe', 'Doria', 'Edith', 'Fern', 'Ginger', 'Heidi', 
      )],
     "1968" =>
     [(
       #'Abby', 'Brenda', 'Candy', 'Dolly', 'Edna', 'Frances', 'Gladys', 
      )],
     "1969" =>
     [(
       #'Anna', 'Blanche', 'Camille', 'Debbie', 'Eve', 'Francelia', 
       #'Gerda', 'Holly', 'Inga', 'Jenny', 'Kara', 'Laurie', 'Martha', 
      )],
     "1970" =>
     [(
       #'Alma', 'Becky', 'Celia',
       #'Dorothy', 'Ella', 'Felice', 'Greta'
       # 4, 9, and 10 are unnamed
      )],
     "1971" =>
     [(
       #'Arlene', 'Beth', 'Chloe', 'Doria', 'Edith',
       #'Fern','Ginger',
       #'Heidi', 'Irene', 'Janice', 'Kristy', 'Laura'
       # 2 is unnamed
      )],
     "1972" =>
     [(
       #'Alpha', 'Agnes',
       #'Betty', 'Carrie', 'Dawn', 'Charlie', 'Delta'
      )],
     "1973" =>
     [(
       #'Alice', 'Alfa', 'Brenda', 'Christine', 'Delia',
       #'Ellen', 'Fran', 'Gilda'
      )],
     "1974" =>
     [(
       #'Alma', 'Becky', 'Carmen',
       #'Dolly', 'Elaine', 'Gertrude'
       # Fifi is under Fifi-Orlene
       # there are 4 unnamed subtropical storms
      )],
     "1975" =>
     [(
       #'Amy', 'Blanche', 'Caroline', 'Doris', 'Eloise',
       #'Faye', 'Gladys', 'Hallie'
       # plus SS2
      )],
     "1976" =>
     [(
       #'Anna', 'Belle', 'Candice', 'Dottie', 'Emmy',
       #'Frances', 'Gloria', 'Holly'
       # plus SS1, SS3
      )],
     "1977" =>
     [(
       #'Anita', 'Clara', 'Dorothy', 'Evelyn', 'Frieda'
       # Babe is handled below
      )],
     "1978" =>
     [(
       #'Amelia', 'Bess', 'Cora', 'Debra', 'Ella', 'Flossie',
       #'Greta', 'Hope', 'Irma', 'Juliet', 'Kendra'
       # SS1 is below
      )],
     "1979" =>
     [(
       #'Ana', 'Bob', 'Claudette', 'David',
       #'Elena', 'Frederic', 'Gloria', 'Henri'
       # SS1 is below
      )],
     "1980" =>
     [(
       #'Allen', 'Bonnie', 'Charley', 'Danielle', 'Earl',
       #'Frances', 'Georges', 'Hermine', 'Ivan', 'Jeanne', 'Karl'
      )],
     "1981" =>
     [(
       #'Arlene', 'Bret', 'Cindy', 'Dennis', 'Emily', 'Floyd',
       #'Gert', 'Harvey', 'Irene', 'Jose', 'Katrina'
      )],
     "1982" =>
     [(
       #'Alberto', 'Beryl', 'Chris', 'Debby', 'Ernesto',
       #SS1 is below
      )],
     "1983" =>
     [(
       #'Alicia', 'Barry', 'Chantal', 'Dean'
      )],
     "1984" =>
     [(
       #'Arthur', 'Bertha', 'Cesar', 'Diana', 'Edouard', 'Fran',
       #'Gustav', 'Hortense', 'Isidore', 'Josephine', 'Klaus', 'Lili'
       #SS1 is below
      )],
     "1985" =>
     [(
       #'Ana', 'Bob', 'Claudette', 'Danny', 'Elena', 'Fabian',
       #'Gloria', 'Henri', 'Isabel', 'Juan', 'Kate'
      )],
     "1986" =>
     [(
       #'Andrew', 'Bonnie', 'Charley', 'Danielle', 'Earl', 'Frances'
      )],
     "1987" =>
     [(
       #'Arlene', 'Bret', 'Cindy', 'Dennis', 'Emily', 'Floyd'
       #TS1 is below
      )],
     "1988" =>
     [(
       #'Alberto', 'Beryl', 'Chris', 'Debby', 'Ernesto', 'Florence',
       #'Gilbert', 'Helene', 'Isaac', 'Keith'
       # Joan is handled as Joan-Miriam, below
       # TS13 is below
      )],
     "1989" =>
     [(
       #'Allison', 'Barry', 'Chantal', 'Dean', 'Erin', 'Felix', 'Gabrielle',
       #'Hugo', 'Iris', 'Jerry', 'Karen'
      )],
     "1990" =>
     [(
       #'Arthur', 'Bertha', 'Cesar', 'Diana', 'Edouard', 'Fran', 'Gustav',
       #'Hortense', 'Isidore', 'Josephine', 'Klaus', 'Lili', 'Marco', 'Nana'
      )],
     "1991" =>
     [(
       #'Ana', 'Bob', 'Claudette', 'Danny', 'Erika', 'Fabian', 'Grace'
       # Hurricane #8 is below
      )],
     "1992" =>
     [(
       #'Andrew', 'Bonnie', 'Charley', 'Danielle', 'Earl', 'Frances'
      )],
     "1993" =>
     [(
       #'Arlene', 'Bret', 'Cindy', 'Dennis', 'Emily', 'Floyd',
       #'Gert', 'Harvey'
      )],
     "1994" =>
     [(
       #'Alberto', 'Beryl', 'Chris', 'Debby', 'Ernesto', 'Florence', 'Gordon'
      )],
     "1995" =>
     [(
       #'Allison', 'Barry', 'Chantal', 'Dean', 'Erin', 'Felix', 'Gabrielle',
       #'Humberto', 'Iris', 'Jerry', 'Karen', 'Luis', 'Marilyn', 'Noel',
       #'Opal', 'Pablo', 'Roxanne', 'Sebastien', 'Tanya',
      )],
     "1996" =>
     [(
       #'Arthur','Bertha', 'Dolly', 'Edouard', 'Fran', 'Gustav',
       #'Hortense', 'Isidore', 'Josephine', 'Kyle', 'Lili', 'Marco'
       # Cesar is done as Cesar-Douglas, below
      )],
     "1997" =>
     [(
       #'Ana', 'Bill', 'Claudette', 'Danny', 'Erika', 'Fabian', 'Grace'
      )],
     "1998" =>
     [(
       #'Alex', 'Bonnie', 'Charley', 'Danielle', 'Earl', 'Frances',
       #'Georges', 'Hermine','Ivan', 'Jeanne', 'Karl', 'Lisa',
       #'Mitch', 'Nicole',
      )],
     "1999" =>
     [(
       #'Arlene', 'Bret', 'Cindy', 'Dennis', 'Emily', 'Floyd',
       #'Gert', 'Harvey', 'Irene', 'Jose', 'Katrina', 'Lenny'
      )],
     "2000" =>
     [(
       #'Alberto', 'Beryl', 'Chris', 'Debby', 'Ernesto', 'Florence',
       #'Gordon', 'Helene', 'Isaac', 'Joyce', 'Keith',
       #'Leslie', 'Michael', 'Nadine'
       )],
     "2001" =>
     [(
       #'Allison', 'Barry', 'Chantal', 'Dean', 'Erin', 'Felix', 'Gabrielle',
       #'Humberto', 'Iris', 'Jerry', 'Karen', 'Lorenzo', 'Michelle',
       #'Noel', 'Olga'
      )],
     "2002" =>
     [(
       #'Arthur', 'Bertha', 'Cristobal', 'Dolly', 'Edouard', 'Fay', 'Gustav',
       #'Hanna', 'Isidore', 'Josephine', 'Kyle', 'Lili'
      )],
     "2003" =>
     [(
       #'Ana', 'Bill', 'Claudette', 'Danny', 'Erika', 'Fabian', 'Grace',
       #'Henri', 'Isabel', 'Juan', 'Kate', 'Larry', 'Mindy', 'Nicholas',
       #'Odette', 'Peter',
      )],
     "2004" =>
     [(
#       'Alex', 'Bonnie', 'Charley', 'Danielle', 'Earl', 'Frances',
#       'Gaston', 'Hermine', 'Ivan',
#       '#10', # Not included in the best-track for some reason
#       'Jeanne', 'Karl', 'Lisa', 'Matthew', 'Nicole', 'Otto'
      )],
    )],

   "epac" =>
   [(
     "1976" =>
     [(
       #'Kathleen', 'Liza'
      )],
     "1997" =>
     [(
       #'Andres', 'Blanca', 'Carlos', 'Dolores', 'Enrique', 'Felicia',
       #'Guillermo', 'Hilda', 'Ignacio', 'Jimena', 'Oliwa', 'Kevin',
       #'Linda', 'Marty', 'Nora', 'Olaf', 'Pauline', 'Rick', 'Paka',
      )],

     "1998" =>
     [(
       #'Agatha', 'Blas', 'Celia', 'Darby', 'Estelle', 'Frank', 'Georgette',
       #'Howard', 'Isis', 'Javier', 'Kay', 'Lester', 'Madeline',
      )],
     "1999" =>
     [(
       #'Adrian', 'Beatriz', 'Calvin', 'Dora', 'Eugene', 'Fernanda',
       #'Greg', 'Hilary', 'Irwin',
      )],
     "2000" =>
     [(
       #'Aletta', 'Bud', 'Carlotta', 'Upana', 'Daniel', 'Emilia', 'Fabio',
       #'Gilma', 'Hector', 'Ileana', 'Wene', 'John', 'Kristy', 'Lane',
       #'Miriam', 'Norman', 'Olivia', 'Paul', 'Rosa',
      )],
     "2001" =>
     [(
       #'Adolph', 'Barbara', 'Cosme', 'Erick', 'Dalila', 'Flossie',
       #'Gil', 'Henriette', 'Ivo', 'Juliette',
       #'Kiko', 'Lorena', 'Manuel',
       #'Narda', 'Octave',
      )],
     "2002" =>
     [(
       #'Alma', 'Boris', 'Cristina', 'Douglas', 'Elida', 'Fausto',
       #'Alika', 'Ele', 'Genevieve', 'Hernan', 'Iselle', 'Julio', 'Kenna',
       #'Lowell', 'Huko',
      )],
     "2003" =>
     [(
       #'Andres', 'Blanca', 'Carlos', 'Dolores', 'Enrique', 'Felicia',
       #'Guillermo', 'Hilda', 'Ignacio', 'Jimena', 'Kevin', 'Linda',
       #'Marty', 'Nora', 'Olaf', 'Patricia',
      )],
     "2004" =>
     [(
       #'Agatha', 'Blas', 'Celia', 'Darby', 'Estelle', 'Frank', 'Georgette',
       #'Howard', 'Isis', 'Javier', 'Kay', 'Lester',
      )],
    )],
  );

# Format: year, name, extra, type
%named =
  (
   "epac" =>
   [(
# Retired storms:
#     [ (1982, 'Iwa') ],
#     [ (1970, 'Adele') ], # Don't bother.
#     [ (1978, 'Fico') ],
#     [ (1987, 'Knut', 0, 'Tropical Storm') ],  # WTF?  Don't bother.
#     [ (1988, 'Iva') ], # Don't bother.
#     [ (1991, 'Fefa') ],
#     [ (1992, 'Iniki') ],
#     [ (1995, 'Ismael') ],

# Non-retired but notable:
#     [ (1982, 'Paul') ],
#     [ (1993, 'Calvin') ],
#     [ (1994, 'John') ],

    )],
   "natlantic" =>
   [ (
#   [ (1966, 'Faith', 1) ],
     ) ],
  );

# Format: year, id, name, extra, type
%namedbyid =
  (
   "wpac" =>
   [ (
#      [ (1956, 12, "Emma") ],
#      [ (1959, 15, "Vera") ],
#      [ (1977, 10, "Babe Pacific") ],
#      [ (1979, 23, "Tip") ],
#      [ (1984, 13, "Ike") ],
#      [ (1988, 23, "Ruby") ],
#      [ (1989, 32, "Gay") ],
#      [ (1990, 27, "Mike") ],
#      [ (1991, 21, "Mireille") ],
#      [ (1991, 27, "Thelma", 0, "Tropical Storm") ],
#      [ (1992, 15, "Omar") ],
#      [ (1996, 10, "Herb") ],
#      [ (2001, 32, "Vamei") ],
#      [ (2002, 8, "Chataan") ],
#      [ (2002, 21, "Rusa") ],
#      [ (2002, 31, "Pongsona") ],
#      [ (2003, 9, "Imbudo") ],

# 2004 storms aren't included in the best-track...
 #      [ (2004, 26, "Ma-on") ],
   ) ],

   "nindian" =>
   [ (
#      [ (2004, 4, "Agni") ], # Not included
     ) ],

   "south" =>
   [ (
#      [ (2002, 6, "Zoe") ],
     ) ],

  );

#Format: args, filename, name
%unnamed =
  (
   "nindian" =>
   [ (
#      [ ("--year 1991 --id 2", "1991 Bangladesh cyclone") ],
#      [ ("--year 1970 --id 15", "1970 Bhola cyclone") ],
#      [ ("--year 1999 --id 5", "1999 Indian cyclone 05B") ],
     ) ],

   "epac" =>
   [ (
# Pre-naming EPac storms:
#      [ ("--year 1959 --id 15", "1959 Mexico hurricane") ],
#      [ ("--year 1975 --id 12", "1975 Pacific hurricane 12") ],
     ) ],

   "wpac" =>
   [ (

     ) ],


   "natlantic" =>
   [ (
# Pre-naming Atlantic storms:
#   [ ("--year 1856 --id 1", "1856 Last Island hurricane") ],
#    [ ("--year 1857 --id 2", "1857 North Carolina hurricane") ],
#      [ ("--year 1869 --id 10", "1869 New England hurricane") ],
#      [ ("--year 1873 --id 2", "1873 Nova Scotia hurricane") ],
#      [ ("--year 1878 --id 11", "1878 Atlantic hurricane") ],
#   [ ("--year 1886 --id 5", "1886 Indianola hurricane") ],
#   [ ("--year 1893 --id 6 --extra 0", "1893 Sea Islands hurricane") ],
#      [ ("--year 1893 --id 10 --extra 0", "1893 Chenier Caminanda hurricane") ],
#      [ ("--year 1898 --id 4 --name \"Not named\"", "1898 Windward Islands hurricane") ],
#   [ ("--year 1899 --id 3", "1899 San Ciriaco hurricane") ],
#   [ ("--year 1900 --id 1 --extra 0", "1900 Galveston hurricane") ],
#      [ ("--year 1915 --id 5", "1915 Louisiana hurricane") ],
#   [ ("--year 1919 --wind 120", "1919 Florida Keys hurricane") ],
#   [ ("--year 1926 --wind 130", "1926 Miami hurricane") ],
#      [ ("--year 1926 --id 10", "1926 Havana-Bermuda hurricane") ],
#   [ ("--year 1928 --wind 140", "1928 Okeechobee hurricane") ],
#      [ ("--year 1930 --id 2", "1930 Dominican Republic hurricane") ],
#   [ ("--year 1932 --wind 140 --extra 0", "1932 Bahamas hurricane") ],
#      [ ("--year 1934 --id 2", "1934 Central America hurricane") ],
#   [ ("--year 1935 --wind 140 --extra 0", "1935 Labor Day hurricane") ],
#   [ ("--year 1938 --wind 140", "1938 New England hurricane") ],
#   [ ("--year 1943 --id 1", "1943 Surprise hurricane") ],
#   [ ("--year 1944 --wind 120 --extra 0", "1944 Atlantic hurricane") ],
#   [ ("--year 1947 --wind 140", "1947 Fort Lauderdale hurricane") ],

#      [ ("--year 1950 --id 12 --name \"not named\"", "1950 Atlantic tropical storm 12") ],
#      [ ("--year 1952 --id 1 --name \"not named\"", "1952 Groundhog Day tropical storm") ],
#      [ ("--year 1953 --id 3 --name \"not named\"", "1953 Atlantic tropical storm 3") ],
#      [ ("--year 1953 --id 7 --name \"not named\"", "1953 Atlantic tropical storm 7") ],
#      [ ("--year 1953 --id 10 --name \"not named\"", "1953 Atlantic tropical storm 10") ],
#      [ ("--year 1953 --id 11 --name \"not named\"", "1953 Atlantic tropical storm 11") ],
#      [ ("--year 1953 --id 13 --name \"not named\"", "1953 Atlantic tropical storm 13") ],
#      [ ("--year 1953 --id 14 --name \"not named\"", "1953 Atlantic tropical storm 14") ],
#      [ ("--year 1954 --id 8 --name \"not named\"", "1954 Atlantic hurricane 8") ],
#      [ ("--year 1954 --id 10 --name \"not named\"", "1954 Atlantic tropical storm 10") ],
#      [ ("--year 1955 --id 5 --name \"not named\"", "1955 Atlantic tropical storm 5") ],
#      [ ("--year 1955 --id 11 --name \"not named\"", "1955 Atlantic tropical storm 11") ],
#      [ ("--year 1956 --id 1 --name \"not named\"", "1956 Atlantic tropical storm 1") ],
#      [ ("--year 1957 --id 1 --name \"not named\"", "1957 Atlantic tropical storm 1") ],
#      [ ("--year 1957 --id 8 --name \"not named\"", "1957 Atlantic tropical storm 8") ],
#      [ ("--year 1959 --id 3 --extra 1 --name \"not named\"", "1959 Escuminac hurricane") ],
#      [ ("--year 1960 --id 1 --name \"not named\"", "1960 Atlantic tropical storm 1") ],
#      [ ("--year 1961 --id 6 --name \"not named\"", "1961 Atlantic tropical storm 6") ],
#      [ ("--year 1963 --id 3 --name \"not named\"", "1963 Atlantic tropical storm 3") ],
#      [ ("--year 1964 --id 1 --name \"not named\"", "1964 Atlantic tropical storm 1") ],
#      [ ("--year 1964 --id 2 --name \"not named\"", "1964 Atlantic tropical storm 2") ],
#      [ ("--year 1964 --id 12 --name \"not named\"", "1964 Atlantic tropical storm 12") ],
#      [ ("--year 1965 --id 1 --name \"not named\"", "1965 Atlantic tropical storm 1") ],
#      [ ("--year 1968 --id 6 --name \"subtrop 1\"", "1968 Atlantic subtropical storm 1") ],
#      [ ("--year 1969 --id 10 --name \"not named\"", "1969 Atlantic hurricane 10") ],
#      [ ("--year 1969 --id 11 --name \"not named\"", "1969 Atlantic tropical storm 11") ],
#      [ ("--year 1969 --id 12 --name \"subtrop 1\"", "1969 Atlantic subtropical storm 1") ],
#      [ ("--year 1969 --id 16 --name \"not named\"", "1969 Atlantic tropical storm 16") ],
#      [ ("--year 1969 --id 17 --name \"not named\"", "1969 Atlantic hurricane 17") ],
#      [ ("--year 1970 --name \"not named\" --id 4", "1970 Atlantic tropical storm 4") ],
#      [ ("--year 1970 --name \"not named\" --id 9", "1970 Atlantic hurricane 9") ],
#      [ ("--year 1970 --name \"not named\" --id 10", "1970 Atlantic hurricane 10") ],
#      [ ("--year 1971 --name \"not named\" --id 2", "1971 Atlantic hurricane 2") ],
#      [ ("--year 1974 --name \"subtrop 1\"", "1974 Atlantic subtropical storm 1") ],
#      [ ("--year 1974 --name \"subtrop 2\"", "1974 Atlantic subtropical storm 2") ],
#      [ ("--year 1974 --name \"subtrop 3\"", "1974 Atlantic subtropical storm 3") ],
#      [ ("--year 1974 --name \"subtrop 4\"", "1974 Atlantic subtropical storm 4") ],
#      [ ("--year 1975 --name \"subtrop 2\"", "1975 Atlantic subtropical storm 2") ],
#      [ ("--year 1976 --name \"subtrop 1\"", "1976 Atlantic subtropical storm 1") ],
#      [ ("--year 1976 --name \"subtrop 3\"", "1976 Atlantic subtropical storm 3") ],
#      [ ("--year 1978 --name \"subtrop 1\"", "1978 Atlantic subtropical storm 1") ],
#      [ ("--year 1979 --name \"subtrop 1\"", "1979 Atlantic subtropical storm 1") ],
#      [ ("--year 1981 --id 12", "1981 Atlantic subtropical storm 3") ],
#      [ ("--year 1982 --id 2", "1982 Atlantic subtropical storm 1") ],
#      [ ("--year 1984 --id 1", "1984 Atlantic subtropical storm 1") ],
#      [ ("--year 1987 --id 1", "1987 Atlantic tropical storm 1") ],
#      [ ("--year 1988 --id 6", "1988 Atlantic tropical storm 6") ],
#      [ ("--year 1991 --id 8", "1991 Atlantic hurricane 8") ], # "Perfect storm"
#      [ ("--year 1992 --id 1", "1992 Atlantic subtropical storm 1") ],
#      [ ("--year 1997 --id 1", "1997 Atlantic subtropical storm 1") ],
#      [ ("--year 2000 --id 15", "2000 Atlantic subtropical storm 15") ],

#      [ ("--year 1954 --id 1 --name Alice --extra 0", "Alice1 1954", "Hurricane Alice1 (1954)") ],
#      [ ("--year 1954 --id 11 --name Alice --extra 0", "Alice2 1954", "Hurricane Alice2 (1954)") ],
#      [ ("--year 1977 --name Babe --extra 0", "Babe Atlantic 1977", "Hurricane Babe (1977)") ],

      # Zone-crossers
#      [ ("--year 1996 --name cesar --input1 epac.txt --year1 1996 --name1 douglas", "Cesar-Douglas 1996", "Hurricane Cesar-Douglas (1996)") ],
#      [ ("--year 1974 --name fifi --input1 epac.txt --year1 1974 --name1 orlene", "Fifi-Orlene 1974", "Hurricane Fifi-Orlene (1974)") ],
#      [ ("--year 1988 --name joan --input1 epac.txt --year1 1988 --name1 miriam", "Joan-Miriam 1988", "Hurricane Joan-Miriam (1988)") ],
#      [ ("--year 1961 --name hattie --input1 epac.txt --year1 1961 --name1 simone --year2 1961 --input2 natlantic.txt --name2 inga", "Hattie-Simone-Inga 1961", "Hurricane Hattie-Simone-Inga (1961)") ],
#      [ ("--year 1978 --name Greta --input1 epac.txt --year1 1978 --name1 Olivia", "Greta-Olivia 1978", "Hurricane Greta-Olivia (1978)") ],

# 2005 storms
#   [ ("--input 2005/arlene-bt.txt --format 2", "Arlene 2005", "Tropical Storm Arlene (2005)") ],
#   [ ("--input 2005/bret-bt.txt --format 2", "Bret 2005", "Tropical Storm Bret (2005)") ],
#   [ ("--input 2005/cindy-bt.txt --format 2", "Cindy 2005", "Hurricane Cindy (2005)") ],
#   [ ("--input 2005/dennis-bt.txt --format 2", "Dennis 2005", "Hurricane Dennis (2005)") ],
#   [ ("--input 2005/emily.txt --format 1", "Emily 2005", "Hurricane Emily (2005)") ],
#   [ ("--input 2005/franklin.txt --format 1", "Franklin 2005", "Tropical Storm Franklin (2005)") ],
#   [ ("--input 2005/gert-bt.txt --format 2", "Gert 2005", "Tropical Storm Gert (2005)") ],
#   [ ("--input 2005/harvey.txt --format 1", "Harvey 2005", "Tropical Storm Harvey (2005)") ],
#   [ ("--input 2005/irene-bt.txt --format 2", "Irene 2005", "Hurricane Irene (2005)") ],
#   [ ("--input 2005/jose-bt.txt --format 2", "Jose 2005", "Tropical Storm Jose (2005)") ],
#   [ ("--input 2005/katrina-bt.txt --format 2", "Katrina 2005", "Hurricane Katrina (2005)") ],
#   [ ("--input 2005/lee-bt.txt --format 2", "Lee 2005", "Tropical Storm Lee (2005)") ],
#   [ ("--input 2005/maria-bt.txt --format 2", "Maria 2005", "Hurricane Maria (2005)") ],
#   [ ("--input 2005/nate-bt.txt --format 2", "Nate 2005", "Hurricane Nate (2005)") ],
#   [ ("--input 2005/ophelia-bt.txt --format 2", "Ophelia 2005", "Hurricane Ophelia (2005)") ],
#   [ ("--input 2005/philippe-bt.txt --format 2", "Philippe 2005", "Hurricane Philippe (2005)") ],
#   [ ("--input 2005/rita.txt --format 1", "Rita 2005", "Hurricane Rita (2005)") ],
#   [ ("--input 2005/stan-bt.txt --format 2", "Stan 2005", "Hurricane Stan (2005)") ],
#   [ ("--input 2005/tammy-bt.txt --format 2", "Tammy 2005", "Tropical Storm Tammy (2005)") ],
#   [ ("--input 2005/vince-bt.txt --format 2", "Vince 2005", "Hurricane Vince (2005)") ],
#   [ ("--input 2005/wilma-bt.txt --format 2", "Wilma 2005", "Hurricane Wilma (2005)") ],
#   [ ("--input 2005/alpha-bt.txt --format 2", "Alpha 2005", "Tropical Storm Alpha (2005)") ],
#   [ ("--input 2005/beta.txt --format 1", "Beta 2005", "Hurricane Beta (2005)") ],
#   [ ("--input 2005/gamma-bt.txt --format 2", "Gamma 2005", "Tropical Storm Gamma (2005)") ],
#   [ ("--input 2005/delta-bt.txt --format 2", "Delta 2005", "Tropical Storm Delta (2005)") ],
#   [ ("--input 2005/epsilon-bt.txt --format 2", "Epsilon 2005", "Hurricane Epsilon (2005)") ],
#   [ ("--input 2005/zeta.txt --format 1", "Zeta 2005", "Tropical Storm Zeta (2005)") ],
     ) ],

   "south" =>
   [ (
      # Southern hemisphere numbering is weird because the storms are numbered
      # by season not by year, so there are two ID 5 storms in 1970 - one 
      # part of 1969-70 and one part of 1970-71 seasons.
#      [ ("--year 1970 --id 5 --wind 60", "Ada 1970", "Cyclone Ada (1970)") ],
#      [ ("--year 1971 --id 9 --wind 60", "Althea 1971", "Cyclone Althea (1971)") ],
#      [ ("--year 1974 --id 19", "Wanda 1974", "Tropical Storm Wanda (1974)") ],
#      [ ("--year 1974 --id 7", "Tracy 1974", "Cyclone Tracy (1974)") ],
#      [ ("--year 2000 --id 11", "Leon-Eline 2000", "Cyclone Leon-Eline (2000)") ],

     ) ],
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

$generated = 0;

# Uncomment the next line to allow automatic uploads (DANGEROUS; UNTESTED)
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

  print "$filename\n";
#  print "   $args \n";
  $res = system "./track $args --output \"$filename\"";
  if ($res != 0) {
    printf "Error!\n";
    exit;
  }
  print "  $desc\n";
  if ($real) {
    do {
      print "  Uploading...\n";
      $res = system "cd $wiki && python upload.py -keep \"$storms$filename\" \"$desc\" 2>&1 >/dev/null";
      mydosleep($sleeptime);
      $sleeptime += 30;
    } while ($res != 0);
  }

  $generated++;
}

system "rm -rf storms/";
system "mkdir -p storms";

@basins = sort keys %namedsimple;
foreach $basin (@basins) {
  my %years = @{ $namedsimple{$basin} };
  foreach my $year (sort keys %years) {
    my @names = @{ $years{$year} };
    foreach my $name (@names) {
      my $args = "--input $basin.txt --extra 0 --year $year ${ $default{$basin} }[1]";

      if ($name =~ /^#/) {
	$name =~ s/^#//;
	$args = "$args --id $name";
      } else {
	$args = "$args --name $name";
      }
      generate($args,
	       "storms/$name" . "_$year" . "_track.png",
	       "${ $default{$basin} }[0] $name ($year)");
    }
  }
}

@basins = sort keys %named;
foreach $basin (@basins) {
  foreach (@{ $named{$basin} }) {
    my ($year, $name, $extra, $type) = @{ $_ };
    my $filename = "storms/$name" . "_$year" . "_track.png";
    my $descname = "$type $name ($year)";

    if (!defined $type) {
      if (!defined $default{$basin}) {
	print "Undefined basin $basin.\n";
	exit;
      }
      $type = ${ $default{$basin} }[0];
    }
    if (!defined $extra) {
      $extra = 0; # ???
    }

    generate("${ $default{$basin} }[1] --input $basin.txt --extra $extra --year $year --name $name",
	     "storms/$name" . "_$year" . "_track.png",
	     "$type $name ($year)");
  }
}

@basins = sort keys %namedbyid;
foreach $basin (@basins) {
  foreach (@{ $namedbyid{$basin} }) {
    my ($year, $id, $name, $extra, $type) = @{ $_ };
    my $filename = "storms/$name" . "_$year" . "_track.png";
    my $descname = "$type $name ($year)";

    if (!defined $type) {
      if (!defined $default{$basin}) {
	print "Undefined basin $basin.\n";
	exit;
      }
      $type = ${ $default{$basin} }[0];
    }
    if (!defined $extra) {
      $extra = 0; # ???
    }

    generate("${ $default{$basin} }[1] --input $basin.txt --extra $extra --year $year --id $id",
	     "storms/$name" . "_$year" . "_track.png",
	     "$type $name ($year)");
  }
}

@basins = sort keys %unnamed;
foreach $basin (@basins) {
  foreach (@{ $unnamed{$basin} }) {
    my ($args, $name, $name2) = @{ $_ };
    if (!defined $name2) {
      $name2 = $name;
    }

    generate("--input $basin.txt ${ $default {$basin} }[1] $args", "storms/$name track.png", $name2);
  }
}

if (!$real && $generated > 0) {
  system("eog storms/* 2>&1 >/dev/null &");
}
