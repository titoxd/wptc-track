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
       #'Alex', 'Bonnie', 'Charley', 'Danielle', 'Earl', 'Frances',
       #'Gaston', 'Hermine', 'Ivan',
       #'Jeanne', 'Karl', 'Lisa', 'Matthew', 'Nicole', 'Otto'
      )],
     "2005" =>
     [(
       #'Arlene', 'Bret', 'Cindy', 'Dennis', 'Emily', 'Franklin', 'Gert', 
       #'Harvey', 'Irene', 'Jose', 'Katrina', 'Lee', 'Maria', 'Nate', 
       #'Ophelia', 'Philippe', 'Rita', 'Stan', 'Tammy', 'Vince', 'Wilma', 
       #'Alpha', 'Beta', 'Gamma', 'Delta', 'Epsilon', 'Zeta'
      )],
     "2006" =>
     [(
       #'Alberto', 'Beryl', 'Chris', 'Debby', 'Ernesto',
       #'Florence', 'Gordon', 'Helene', 'Isaac', 
      )],
    )],

   "epac" =>
   [(
     "1950" =>
     [(
       #'Hiki', 
      )],
     "1957" =>
     [(
       #'Kanoa', 'Della', 'Nina', 
      )],
     "1959" =>
     [(
       #'Dot', 'Patsy', 'Wanda', 
      )],
     "1960" =>
     [(
       #'Annette', 'Bonny', 'Celeste', 'Diana', 'Estelle', 'Fernanda', 
       #'Hyacinth', 
      )],
     "1961" =>
     [(
       #'Iva', 'Joanne', 'Kathleen', 'Liza', 'Naomi', 'Orla', 'Pauline', 
       #'Rebecca', 'Simone', 'Tara', 
      )],
     "1962" =>
     [(
       #'Valerie', 'Willa', 'Ava', 'C', 'Bernice', 'Claudia', 'Doreen', 
      )],
     "1963" =>
     [(
       #'Emily', 'Florence', 'Glenda', 'Jen-kath', 'Irah', 'Lillian', 
       #'Mona', 
      )],
     "1964" =>
     [(
       #'Natalie', 'Odessa', 'Prudence',
       #'Roslyn', 'Tillie', 
      )],
     "1965" =>
     [(
       #'Victoria', 'Wallie', 'Ava', 'Bernice', 'Claudia', 'Doreen', 
       #'Emily', 'Florence', 'Glenda', 'Hazel', 
      )],
     "1966" =>
     [(
       #'Adele', 'Blanca', 'Connie', 'Dolores', 'Eileen', 'Francesca', 
       #'Gretchen', 'Helga', 'Ione', 'Joyce', 'Kirsten', 'Lorraine', 
       #'Maggie', 
      )],
     "1967" =>
     [(
       #'Agatha', 'Bridget', 'Carlotta', 'Denise', 'Eleanor', 'Francene', 
       #'Georgette', 'Ilsa', 'Jewel', 'Katrina', 'Lily', 'Sarah', 'Monica', 
       #'Nanette', 'Olivia', 'Priscilla', 'Ramona', 
      )],
     "1968" =>
     [(
       #'Annette', 'Bonny', 'Celeste', 'Diana', 'Estelle', 'Fernanda', 
       #'Gwen', 'Hyacinth', 'Iva', 'Joanne', 'Kathleen', 'Liza', 'Madeline', 
       #'Naomi', 'Orla', 'Pauline', 'Rebecca', 'Tara', 
      )],
     "1969" =>
     [(
       #'Ava', 'Bernice', 'Claudia', 'Doreen', 'Emily', 'Florence', 
       #'Glenda', 'Heather', 'Irah', 'Jennifer', 
      )],
     "1970" =>
     [(
       #'Adele', 'Blanca', 'Connie', 'Eileen', 'Francesca', 'Gretchen', 
       #'Helga', 'Ione 2', 'Ione 1', 'Joyce', 'Kristen', 'Lorraine', 
       #'Maggie', 'Norma', 'Dot', 'Orlene', 'Patricia', 'Rosalie', 
       #'Selma', 
      )],
     "1971" =>
     [(
       #'Agatha', 'Bridget', 'Carlotta', 'Denise', 'Eleanor', 'Francene', 
       #'Georgette', 'Hilary', 'Ilsa', 'Jewel', 'Katrina', 'Lily', 
       #'Monica', 'Nanette', 'Olivia', 'Priscilla', 'Ramona', 'Sharon', 
      )],
     "1972" =>
     [(
       #'Annette', 'Bonny', 'Celeste', 'Diana', 'Estelle', 'Fernanda', 
       #'Gwen', 'Hyacinth', 'Iva', 'June', 'Joanne', 'Kathleen', 'Ruby', 
       #'Liza', 
      )],
     "1973" =>
     [(
       #'Ava', 'Bernice', 'Claudia', 'Doreen', 'Emily', 'Florence', 
       #'Glenda', 'Heather', 'Irah', 'Jennifer', 'Katherine', 'Lillian', 
      )],
     "1974" =>
     [(
       #'Aletta', 'Blanca', 'Connie', 'Dolores', 'Eileen', 'Francesca', 
       #'Gretchen', 'Helga', 'Ione', 'Olive', 'Joyce', 'Kirsten', 'Lorraine', 
       #'Maggie', 'Norma', 'Orlene', 'Patricia', 'Rosalie', 
      )],
     "1975" =>
     [(
       #'Agatha', 'Bridget', 'Carlotta', 'Denise', 'Eleanor', 'Francene', 
       #'Georgette', 'Hilary', 'Ilsa', 'Jewel', 'Katrina', 'Lily', 
       #'Monica', 'Nanette', 'Olivia', 'Priscilla', 
      )],
     "1976" =>
     [(
       #'Annette', 'Bonny', 'Celeste', 'Diana', 'Estelle', 'Fernanda', 
       #'Gwen', 'Hyacinth', 'Iva', 'Joanne', 'Kathleen', 'Kate',
       #'Liza', 'Madeline', 'Naomi', 
      )],
     "1977" =>
     [(
       #'Ava', 'Bernice', 'Claudia', 'Doreen', 'Emily', 'Florence', 
       #'Glenda', 'Heather', 
      )],
     "1978" =>
     [(
       #'Aletta', 'Bud', 'Carlotta', 'Daniel', 'Emilia', 'Fico', 'Gilma', 
       #'Hector', 'Iva', 'John', 'Kristy', 'Lane', 'Miriam', 'Norman', 
       #'Olivia', 'Paul', 'Rosa', 'Susan', 'Sergio', 
      )],
     "1979" =>
     [(
       #'Andres', 'Blanca', 'Carlos', 'Dolores', 'Enrique', 'Fefa', 
       #'Guillermo', 'Hilda', 'Ignacio', 'Jimena', 
      )],
     "1980" =>
     [(
       #'Agatha', 'Blas', 'Celia', 'Darby', 'Estelle', 'Frank', 'Georgette', 
       #'Howard', 'Isis', 'Javier', 'Kay', 'Lester', 'Madeline', 'Newton', 
      )],
     "1981" =>
     [(
       #'Adrian', 'Beatriz', 'Calvin', 'Dora', 'Eugene', 'Fernanda', 
       #'Greg', 'Hilary', 'Irwin', 'Jova', 'Knut', 'Lidia', 'Max', 
       #'Norma', 'Otis', 
      )],
     "1982" =>
     [(
       #'Aletta', 'Bud', 'Carlotta', 'Daniel', 'Emilia', 'Fabio', 'Gilma', 
       #'Hector', 'Iva', 'John', 'Kristy', 'Lane', 'Miriam', 'Akoni', 
       #'Norman', 'Ema', 'Hana', 'Olivia', 'Paul', 'Rosa', 'Sergio', 
       #'Tara', 'Iwa', 
      )],
     "1983" =>
     [(
       #'Adolph', 'Barbara', 'Cosme', 'Dalilia', 'Erick', 'Flossie', 
       #'Gil', 'Henriette', 'Ismael', 'Juliette', 'Kiko', 'Lorena', 
       #'Manuel', 'Narda', 'Octave', 'Priscilla', 'Raymond', 'Sonia', 
       #'Tico', 'Velma', 'Winnie', 
      )],
     "1984" =>
     [(
       #'Alma', 'Boris', 'Cristina', 'Douglas', 'Elida', 'Fausto', 
       #'Genevieve', 'Hernan', 'Iselle', 'Julio', 'Keli', 'Kenna', 
       #'Lala', 'Lowell', 'Moke', 'Marie', 'Norbert', 'Odile', 'Polo', 
       #'Rachel', 'Simon', 
      )],
     "1985" =>
     [(
       #'Andres', 'Blanca', 'Carlos', 'Dolores', 'Enrique', 'Fefa', 
       #'Guillermo', 'Hilda', 'Ignacio', 'Jimena', 'Kevin', 'Linda', 
       #'Marty', 'Nora', 'Olaf', 'Pauline', 'Rick', 'Sandra', 'Terry', 
       #'Vivian', 'Waldo', 'Nele', 'Xina', 
      )],
     "1986" =>
     [(
       #'Agatha', 'Blas', 'Celia', 'Darby', 'Estelle', 'Frank', 'Georgette', 
       #'Howard', 'Isis', 'Javier', 'Kay', 'Lester', 'Madeline', 'Newton', 
       #'Orlene', 'Paine', 'Roslyn', 
      )],
     "1987" =>
     [(
       #'Adrian', 'Beatriz', 'Calvin', 'Dora', 'Eugene', 'Fernanda', 
       #'Greg', 'Hilary', 'Irwin', 'Jova', 'Oka', 'Knut', 'Lidia', 
       #'Max', 'Norma', 'Otis', 'Peke', 'Pilar', 'Ramon', 'Selma', 
      )],
     "1988" =>
     [(
       #'Aletta', 'Bud', 'Carlotta', 'Daniel', 'Emilia', 'Fabio', 'Gilma', 
       #'Hector', 'Iva', 'John', 'Uleki', 'Kristy', 'Wila', 'Lane', 
       #'Miriam', 
      )],
     "1989" =>
     [(
       #'Adolph', 'Barbara', 'Cosme', 'Dalilia', 'Erick', 'Flossie', 
       #'Gil', 'Henriette', 'Ismael', 'Juliette', 'Kiko', 'Lorena', 
       #'Manuel', 'Narda', 'Octave', 'Priscilla', 'Raymond', 
      )],
     "1990" =>
     [(
       #'Alma', 'Boris', 'Cristina', 'Douglas', 'Elida', 'Fausto', 
       #'Genevieve', 'Hernan', 'Iselle', 'Aka', 'Julio', 'Kenna', 'Lowell', 
       #'Marie', 'Norbert', 'Odile', 'Polo', 'Rachel', 'Simon', 'Trudy', 
       #'Vance', 
      )],
     "1991" =>
     [(
       #'Andres', 'Blanca', 'Carlos', 'Delores', 'Enrique', 'Fefa', 
       #'Guillermo', 'Hilda', 'Ignacio', 'Jimena', 'Kevin', 'Linda', 
       #'Marty', 'Nora', 
      )],
     "1992" =>
     [(
       #'Ekeka', 'Hali', 'Agatha', 'Blas', 'Celia', 'Darby', 'Estelle', 
       #'Frank', 'Georgette', 'Howard', 'Isis', 'Javier', 'Kay', 'Lester', 
       #'Madeline', 'Newton', 'Orlene', 'Iniki', 'Paine', 'Roslyn', 
       #'Seymour', 'Tina', 'Virgil', 'Winifred', 'Xavier', 'Yolanda', 
       #'Zeke', 
      )],
     "1993" =>
     [(
       #'Adrian', 'Beatriz', 'Calvin', 'Dora', 'Eugene', 'Keoni', 'Fernanda', 
       #'Greg', 'Hilary', 'Irwin', 'Jova', 'Kenneth', 'Lidia', 'Max', 
       #'Norma', 
      )],
     "1994" =>
     [(
       #'Aletta', 'Bud', 'Carlotta', 'Daniel', 'Emilia', 'Fabio', 'Gilma', 
       #'Li', 'Hector', 'Ileana', 'John', 'Kristy', 'Lane', 'Mele', 
       #'Miriam', 'Norman', 'Olivia', 'Paul', 'Rosa', 'Nona', 
      )],
     "1995" =>
     [(
       #'Adolph', 'Barbara', 'Cosme', 'Dalila', 'Erick', 'Flossie', 
       #'Gil', 'Henriette', 'Ismael', 'Juliette', 
      )],
     "1996" =>
     [(
       #'Alma', 'Boris', 'Cristina', 'Douglas', 'Elida', 'Fausto', 
       #'Genevieve', 'Hernan', 
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
     "2005" =>
     [(
       #'Adrian', 'Beatriz', 'Calvin', 'Dora', 'Eugene', 'Fernanda', 'Greg',
       #'Hilary', 'Irwin', 'Jova', 'Kenneth', 'Lidia', 'Max', 'Norma',
       #'Otis'
      )],
     "2006" =>
     [(
       #'Aletta'
      )]
    )],
 
   "wpac" =>
   [(
     "1950" =>
     [(
      )],
     "1951" =>
     [(
      )],
     "1952" =>
     [(
      )],
     "1953" =>
     [(
      )],
     "1954" =>
     [(
      )],
     "1955" =>
     [(
      )],
     "1956" =>
     [(
       #'Emma'
      )],
     "1957" =>
     [(
       #'Rose', 'Shirley', 'Trix', 'Virginia',
       #'Wendy', 'Agnes', 'Bess', 'Carmen', 'Della',
       #'Elaine', 'Faye', 'Gloria', 'Hester',
       #'Irma', 'Judy', 'Kit', 'Lola', 'Mamie'
      )],
     "1958" =>
     [(
      )],
     "1959" =>
     [(
       #'Patsy', 'Vera'
      )],
     "1960" =>
     [(
      )],
     "1961" =>
     [(
       #'Nancy'
      )],
     "1962" =>
     [(
       #'Karen'
      )],
     "1963" =>
     [(
      )],
     "1964" =>
     [(
      #'Tess', 'Viola', 'Winnie', 'Alice', 'Betty', 
      #'Cora', 'Doris', 'Elsie', 'Flossie', 'Grace',
      #'Helen', 'Ida', 'June', 'Kathy', 'Lorna', 'Marie',
      #'Nancy', 'Olga', 'Pamela', 'Ruby', 'Sally',
      #'Tilda', 'Violet', 'Wilda', 'Anita', 'Billie',
      #'Clara', 'Dot', 'Ellen', 'Fran', 'Georgia', 'Hope',
      #'Iris', 'Joan', 'Kate', 'Louise', 'Marge', 'Nora', 'Opal'
      )],
     "1965" =>
     [(
      )],
     "1966" =>
     [(
      )],
     "1967" =>
     [(
      )],
     "1968" =>
     [(
      )],
     "1969" =>
     [(
      )],
     "1970" =>
     [(
       #'Joan', 'Kate', 'Patsy'
      )],
     "1971" =>
     [(
       #'Rose'
      )],
     "1972" =>
     [(
       #'Helen', 'Ora'
      )],
     "1973" =>
     [(
      )],
     "1974" =>
     [(
       #'Bess'
      )],
     "1975" =>
     [(
       #'Nina'
      )],
     "1976" =>
     [(
       #'Billie'
      )],
     "1977" =>
     [(
      )],
     "1978" =>
     [(
      )],
     "1979" =>
     [(
       #'Tip'
      )],
     "1980" =>
     [(
      )],
     "1981" =>
     [(
       #'Irma'
      )],
     "1982" =>
     [(
       #'Bess'
      )],
     "1983" =>
     [(
       #'Kim'
      )],
     "1984" =>
     [(
       #'Ike'
      )],
     "1985" =>
     [(
       #'Dot'
      )],
     "1986" =>
     [(
      )],
     "1987" =>
     [(
      #'Peke', 'Nina'
      )],
     "1988" =>
     [(
       #'Ruby'
      )],
     "1989" =>
     [(
       #'Gay'
      )],
     "1990" =>
     [(
       #'Mike'
      )],
     "1991" =>
     [(
       #'Yunya', 'Mireille', 'Thelma'
      )],
     "1992" =>
     [(
       #'Omar'
      )],
     "1993" =>
     [(
       #'Koryn'
      )],
     "1994" =>
     [(
      )],
     "1995" =>
     [(
      )],
     "1996" =>
     [(
       #'Herb'
      )],
     "1997" =>
     [(
      )],
     "1998" =>
     [(
       #'Babs', 'Zeb'
      )],
     "1999" =>
     [(
      )],
     "2000" =>
     [(
      )],
     "2001" =>
     [(
       #'Chebi', 'Vamei'
      )],
     "2002" =>
     [(
       #'Kammuri', 'Chataan', 'Pongsona', 'Rusa'
      )],
     "2003" =>
     [(
       #'Maemi', 'Imbudo'
      )],
     "2004" =>
     [(
       #'Conson', 'Mindulle','Songda', 'Meari', 
       #'Sudal', 'Nida', 'Omais',  'Chanthu',
       #'Dianmu', 'Tingting', 'Kompasu', 'Namtheun',
       #'Malou', 'Meranti', 'Rananim', 'Malakas', 'Megi',
       #'Chaba', 'Aere', 'Sarika', 'Haima',
       #'Ma-on', 'Tokage', 'Nock-ten', 'Muifa',
       #'Nanmadol', 'Talas', 'Noru'
      )],
     "2005" =>
     [(
       #'Haitang', 'Longwang', 'Talim'
      )],
     "2006" =>
     [(
       #'Chanchu', 'Jelawat', 'Ewiniar', 'Bilis', 'Kaemi'
      )],
    )],
    
   "nindian" =>
   [(
     "2004" =>
     [(
       #'Agni'
      )],
     "2006" =>
     [(
       #'Mala'
      )],
    )],
    
   "south" =>
   [(
     "1998" =>
     [(
       #'Thelma'
      )],
     "1999" =>
     [(
       #'Vance'
       #'Ilsa', 'John', 'Astride'
      )],
     "2000" =>
     [(
       #'Leon-Eline'
       #'Babiola', 'Iris', 'Jo', 'Connie', 'Kirrily',
       #'Damienne', 'Felicia', 'Kim', 'Steve', 'Rosita',
       #'Gloria', 'Norman', 'Leo', 'Mona', 'Olga', 
       #'Hudah', 'Tessi', 'Vaughan', 'Paul', 'Neil',
       #'Innocente'
      )],
     "2002" =>
     [(
       #'Zoe'
      )],
     "2004" =>
     [(
       #'Gafilo'
      )],
     "2005" =>
     [(
       #'Ingrid', 'Olaf', 'Percy'
      )],
     "2006" =>
     [(
       #'Larry', 'Monica'
      )],
    )],
  );

# Format: year, name, extra, type
%named =
  (
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
#      [ (1977, 10, "Babe Pacific") ],

# 2004 storms aren't included in the best-track...
 #      [ (2004, 26, "Ma-on") ],
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

#	[ (" --input epac/bud.txt --format md","Bud 2006","Hurricane Bud (2006)") ],
#	[ (" --input epac/carlotta.txt --format md","Carlotta 2006","Hurricane Carlotta (2006)" ) ],
#	[ (" --input epac/daniel.txt --format md","Daniel 2006","Hurricane Daniel (2006)" ) ],
#	[ (" --input epac/emilia.txt --format md","Emilia 2006","Tropical Storm Emilia (2006)") ],
#	[ (" --input epac/fabio.txt  --format md","Fabio 2006"  ,"Tropical Storm Daniel (2006)") ],
#	[ (" --input epac/gilma.txt  --format md","Gilma 2006"  ,"Tropical Storm Gilma (2006)")  ],
#	[ (" --input epac/hector.txt --format md","Hector 2006", "Hurricane Hector (2006)"    )  ],
#	[ (" --input epac/ioke.txt   --format md","Ioke 2006",   "Hurricane Ioke (2006)" )  ],
#	[ (" --input epac/ileana.txt --format md","Ileana 2006","Hurricane Ileana (2006)" )],
#	[ (" --input epac/john.txt   --format md","John 2006"  ,"Hurricane John"               )],
#	[ (" --input epac/kristy.txt --format md","Kristy 2006","Tropical Storm Kristy" )],
#	[ (" --input epac/lane.txt   --format md","Lane 2006",  "Hurricane Lane" )],
#	[ (" --input epac/miriam.txt --format md --windformat kt", "Miriam 2006", "Tropical Storm Miriam (2006)") ],
#	[ (" --input epac/norman.txt --format md --windformat kt", "Norman 2006", "Tropical Storm Norman (2006)") ],
#	[ (" --input epac/olivia.txt --format md --windformat kt", "Olivia 2006", "Tropical Storm Olivia (2006)") ],
#	[ (" --input epac/paul.txt   --format md", "Paul 2006","Tropical Storm Paul" ) ],
# Pre-naming EPac storms:
#      [ ("--year 1959 --id 15", "1959 Mexico hurricane") ],
#      [ ("--year 1975 --id 12", "1975 Pacific hurricane 12") ],
     ) ],

   "natlantic" =>
   [ (
# Pre-naming Atlantic storms:
#   [ ("--year 1856 --id 1", "1856 Last Island hurricane") ],
#   [ ("--year 1857 --id 2", "1857 North Carolina hurricane") ],
#   [ ("--year 1869 --id 10", "1869 New England hurricane") ],
#   [ ("--year 1873 --id 2", "1873 Nova Scotia hurricane") ],
#   [ ("--year 1878 --id 11", "1878 Atlantic hurricane") ],
#   [ ("--year 1886 --id 5", "1886 Indianola hurricane") ],
#   [ ("--year 1887 --id 1", "1887 Atlantic tropical storm 1") ],
#   [ ("--year 1887 --id 2", "1887 Atlantic tropical storm 2") ],
#   [ ("--year 1887 --id 3", "1887 Atlantic tropical storm 3") ],
#   [ ("--year 1887 --id 4", "1887 Atlantic hurricane 4") ],
#   [ ("--year 1887 --id 5", "1887 Atlantic tropical storm 5") ],
#   [ ("--year 1887 --id 6", "1887 Atlantic hurricane 6") ],
#   [ ("--year 1887 --id 7", "1887 Atlantic hurricane 7") ],
#   [ ("--year 1887 --id 8", "1887 Atlantic hurricane 8") ],
#   [ ("--year 1887 --id 9", "1887 Atlantic hurricane 9") ],
#   [ ("--year 1887 --id 10", "1887 Atlantic hurricane 10") ],
#   [ ("--year 1887 --id 11", "1887 Atlantic tropical storm 11") ],
#   [ ("--year 1887 --id 12", "1887 Atlantic tropical storm 12") ],
#   [ ("--year 1887 --id 13", "1887 Atlantic hurricane 13") ],
#   [ ("--year 1887 --id 14", "1887 Atlantic hurricane 14") ],
#   [ ("--year 1887 --id 15", "1887 Atlantic hurricane 15") ],
#   [ ("--year 1887 --id 16", "1887 Atlantic tropical storm 16") ],
#   [ ("--year 1887 --id 17", "1887 Atlantic hurricane 17") ],
#   [ ("--year 1887 --id 18", "1887 Atlantic hurricane 18") ],
#   [ ("--year 1887 --id 19", "1887 Atlantic tropical storm 19") ],
#   [ ("--year 1893 --id 1", "1893 Atlantic hurricane 1") ],
#   [ ("--year 1893 --id 2", "1893 Atlantic hurricane 2") ],
#   [ ("--year 1893 --id 3", "1893 Atlantic hurricane 3") ],
#   [ ("--year 1893 --id 4", "1893 Atlantic hurricane 4") ],
#   [ ("--year 1893 --id 5", "1893 Atlantic hurricane 5") ],
#   [ ("--year 1893 --id 6", "1893 Sea Islands hurricane") ],
#   [ ("--year 1893 --id 7", "1893 Atlantic hurricane 7") ],
#   [ ("--year 1893 --id 8", "1893 Atlantic hurricane 8") ],
#   [ ("--year 1893 --id 9", "1893 Atlantic hurricane 9") ],
#   [ ("--year 1893 --id 10", "1893 Chenier Caminanda hurricane") ],
#   [ ("--year 1893 --id 11", "1893 Atlantic tropical storm 11") ],
#   [ ("--year 1893 --id 12", "1893 Atlantic tropical storm 12") ],
#   [ ("--year 1894 --id 1", "1894 Atlantic tropical storm 1") ],
#   [ ("--year 1894 --id 2", "1894 Atlantic tropical storm 2") ],
#   [ ("--year 1894 --id 3", "1894 Atlantic hurricane 3") ],
#   [ ("--year 1894 --id 4", "1894 Atlantic hurricane 4") ],
#   [ ("--year 1894 --id 5", "1894 Atlantic hurricane 5") ],
#   [ ("--year 1894 --id 6", "1894 Atlantic hurricane 6") ],
#   [ ("--year 1894 --id 7", "1894 Atlantic hurricane 7") ],
#   [ ("--year 1895 --id 1", "1895 Atlantic tropical storm 1") ],
#   [ ("--year 1895 --id 2", "1895 Atlantic hurricane 2") ],
#   [ ("--year 1895 --id 3", "1895 Atlantic tropical storm 3") ],
#   [ ("--year 1895 --id 4", "1895 Atlantic tropical storm 4") ],
#   [ ("--year 1895 --id 5", "1895 Atlantic hurricane 5") ],
#   [ ("--year 1895 --id 6", "1895 Atlantic tropical storm 6") ],
#   [ ("--year 1896 --id 1", "1896 Atlantic hurricane 1") ],
#   [ ("--year 1896 --id 2", "1896 Atlantic hurricane 2") ],
#   [ ("--year 1896 --id 3", "1896 Atlantic hurricane 3") ],
#   [ ("--year 1896 --id 4", "1896 Atlantic hurricane 4") ],
#   [ ("--year 1896 --id 5", "1896 Atlantic hurricane 5") ],
#   [ ("--year 1896 --id 6", "1896 Atlantic hurricane 6") ],
#   [ ("--year 1896 --id 7", "1896 Atlantic tropical storm 7") ],
#   [ ("--year 1897 --id 1", "1897 Atlantic hurricane 1") ],
#   [ ("--year 1897 --id 2", "1897 Atlantic hurricane 2") ],
#   [ ("--year 1897 --id 3", "1897 Atlantic tropical storm 3") ],
#   [ ("--year 1897 --id 4", "1897 Atlantic tropical storm 4") ],
#   [ ("--year 1897 --id 5", "1897 Atlantic hurricane 5") ],
#   [ ("--year 1897 --id 6", "1897 Atlantic tropical storm 6") ],
#   [ ("--year 1898 --id 4 --name \"Not named\"", "1898 Windward Islands hurricane") ],
#   [ ("--year 1899 --id 1", "1899 Atlantic tropical storm 1") ],
#   [ ("--year 1899 --id 2", "1899 Atlantic hurricane 2") ],
#   [ ("--year 1899 --id 3", "1899 San Ciriaco hurricane") ],
#   [ ("--year 1899 --id 4", "1899 Atlantic hurricane 4") ],
#   [ ("--year 1899 --id 5", "1899 Atlantic hurricane 5") ],
#   [ ("--year 1899 --id 6", "1899 Atlantic tropical storm 6") ],
#   [ ("--year 1899 --id 7", "1899 Atlantic tropical storm 7") ],
#   [ ("--year 1899 --id 8", "1899 Atlantic hurricane 8") ],
#   [ ("--year 1899 --id 9", "1899 Atlantic tropical storm 9") ],
#   [ ("--year 1900 --id 1", "1900 Galveston hurricane") ],
#   [ ("--year 1900 --id 2", "1900 Atlantic hurricane 2") ],
#   [ ("--year 1900 --id 3", "1900 Atlantic hurricane 3") ],
#   [ ("--year 1900 --id 4", "1900 Atlantic tropical storm 4") ],
#   [ ("--year 1900 --id 5", "1900 Atlantic tropical storm 5") ],
#   [ ("--year 1900 --id 6", "1900 Atlantic tropical storm 6") ],
#   [ ("--year 1900 --id 7", "1900 Atlantic tropical storm 7") ],
#   [ ("--year 1901 --id 1", "1901 Atlantic tropical storm 1") ],
#   [ ("--year 1901 --id 2", "1901 Atlantic tropical storm 2") ],
#   [ ("--year 1901 --id 3", "1901 Atlantic hurricane 3") ],
#   [ ("--year 1901 --id 4", "1901 Atlantic hurricane 4") ],
#   [ ("--year 1901 --id 5", "1901 Atlantic tropical storm 5") ],
#   [ ("--year 1901 --id 6", "1901 Atlantic hurricane 6") ],
#   [ ("--year 1901 --id 7", "1901 Atlantic hurricane 7") ],
#   [ ("--year 1901 --id 8", "1901 Atlantic tropical storm 8") ],
#   [ ("--year 1901 --id 9", "1901 Atlantic tropical storm 9") ],
#   [ ("--year 1901 --id 10", "1901 Atlantic tropical storm 10") ],
#   [ ("--year 1901 --id 11", "1901 Atlantic tropical storm 11") ],
#   [ ("--year 1901 --id 12", "1901 Atlantic hurricane 12") ],
#   [ ("--year 1902 --id 1", "1902 Atlantic tropical storm 1") ],
#   [ ("--year 1902 --id 2", "1902 Atlantic hurricane 2") ],
#   [ ("--year 1902 --id 3", "1902 Atlantic hurricane 3") ],
#   [ ("--year 1902 --id 4", "1902 Atlantic hurricane 4") ],
#   [ ("--year 1902 --id 5", "1902 Atlantic tropical storm 5") ],
#   [ ("--year 1903 --id 1", "1903 Atlantic hurricane 1") ],
#   [ ("--year 1903 --id 2", "1903 Atlantic hurricane 2") ],
#   [ ("--year 1903 --id 3", "1903 Atlantic hurricane 3") ],
#   [ ("--year 1903 --id 4", "1903 Atlantic hurricane 4") ],
#   [ ("--year 1903 --id 5", "1903 Atlantic tropical storm 5") ],
#   [ ("--year 1903 --id 6", "1903 Atlantic hurricane 6") ],
#   [ ("--year 1903 --id 7", "1903 Atlantic hurricane 7") ],
#   [ ("--year 1903 --id 8", "1903 Atlantic tropical storm 8") ],
#   [ ("--year 1903 --id 9", "1903 Atlantic tropical storm 9") ],
#   [ ("--year 1903 --id 10", "1903 Atlantic hurricane 10") ],
#   [ ("--year 1904 --id 1", "1904 Atlantic hurricane 1") ],
#   [ ("--year 1904 --id 2", "1904 Atlantic hurricane 2") ],
#   [ ("--year 1904 --id 3", "1904 Atlantic hurricane 3") ],
#   [ ("--year 1904 --id 4", "1904 Atlantic tropical storm 4") ],
#   [ ("--year 1904 --id 5", "1904 Atlantic tropical storm 5") ],
#   [ ("--year 1905 --id 1", "1905 Atlantic tropical storm 1") ],
#   [ ("--year 1905 --id 2", "1905 Atlantic tropical storm 2") ],
#   [ ("--year 1905 --id 3", "1905 Atlantic tropical storm 3") ],
#   [ ("--year 1905 --id 4", "1905 Atlantic hurricane 4") ],
#   [ ("--year 1905 --id 5", "1905 Atlantic tropical storm 5") ],
#   [ ("--year 1907 --id 1", "1907 Atlantic tropical storm 1") ],
#   [ ("--year 1907 --id 2", "1907 Atlantic tropical storm 2") ],
#   [ ("--year 1907 --id 3", "1907 Atlantic tropical storm 3") ],
#   [ ("--year 1907 --id 4", "1907 Atlantic tropical storm 4") ],
#   [ ("--year 1907 --id 5", "1907 Atlantic tropical storm 5") ],
#   [ ("--year 1914 --id 1", "1914 Atlantic tropical storm 1") ],
#   [ ("--year 1915 --id 1", "1915 Atlantic tropical storm 1") ],
#   [ ("--year 1915 --id 2", "1915 Galveston hurricane") ],
#   [ ("--year 1915 --id 3", "1915 Atlantic hurricane 3") ],
#   [ ("--year 1915 --id 4", "1915 Atlantic hurricane 4") ],
#   [ ("--year 1915 --id 5", "1915 Louisiana hurricane") ],
#   [ ("--year 1916 --id 1", "1916 Atlantic hurricane 1") ],
#   [ ("--year 1916 --id 2", "1916 Atlantic hurricane 2") ],
#   [ ("--year 1916 --id 3", "1916 Atlantic hurricane 3") ],
#   [ ("--year 1916 --id 4", "1916 Atlantic hurricane 4") ],
#   [ ("--year 1916 --id 5", "1916 Atlantic hurricane 5") ],
#   [ ("--year 1916 --id 6", "1916 Atlantic hurricane 6") ],
#   [ ("--year 1916 --id 7", "1916 Atlantic tropical storm 7") ],
#   [ ("--year 1916 --id 8", "1916 Atlantic tropical storm 8") ],
#   [ ("--year 1916 --id 9", "1916 Atlantic hurricane 9") ],
#   [ ("--year 1916 --id 10", "1916 Atlantic hurricane 10") ],
#   [ ("--year 1916 --id 11", "1916 Atlantic tropical storm 11") ],
#   [ ("--year 1916 --id 12", "1916 Atlantic hurricane 12") ],
#   [ ("--year 1916 --id 13", "1916 Atlantic hurricane 13") ],
#   [ ("--year 1916 --id 14", "1916 Atlantic hurricane 14") ],
#   [ ("--year 1919 --wind 120", "1919 Florida Keys hurricane") ],
#   [ ("--year 1921 --id 6", "1921 Tampa Bay hurricane") ],
#   [ ("--year 1925 --id 1", "1925 Atlantic tropical storm 1") ],
#   [ ("--year 1925 --id 2", "1925 Atlantic hurricane 2") ],
#   [ ("--year 1926 --id 1", "1926 Nassau Hurricane") ],
#   [ ("--year 1926 --id 2", "1926 Atlantic hurricane 2") ],
#   [ ("--year 1926 --id 3", "1926 Atlantic hurricane 3") ],
#   [ ("--year 1926 --id 4", "1926 Atlantic hurricane 4") ],
#   [ ("--year 1926 --id 5", "1926 Atlantic hurricane 5") ],
#   [ ("--year 1926 --id 6", "1926 Miami hurricane") ],
#   [ ("--year 1926 --id 7", "1926 Atlantic tropical storm 7") ],
#   [ ("--year 1926 --id 8", "1926 Atlantic hurricane 8") ],
#   [ ("--year 1926 --id 9", "1926 Atlantic tropical storm 9") ],
#   [ ("--year 1926 --id 10", "1926 Havana-Bermuda hurricane") ],
#   [ ("--year 1926 --id 11", "1926 Atlantic tropical storm 11") ],
#   [ ("--year 1928 --wind 140 --id 4", "1928 Okeechobee hurricane") ],
#   [ ("--year 1929 --id 2", "1929 Florida hurricane") ],
#   [ ("--year 1930 --id 1", "1930 Atlantic hurricane 1") ],
#   [ ("--year 1930 --id 2", "1930 Dominican Republic hurricane") ],
#   [ ("--year 1932 --wind 140 --extra 0", "1932 Bahamas hurricane") ],
#   [ ("--year 1934 --id 2", "1934 Central America hurricane") ],
#   [ ("--year 1935 --wind 140 --extra 0", "1935 Labor Day hurricane") ],
#   [ ("--year 1938 --wind 140", "1938 New England hurricane") ],
#   [ ("--year 1939 --id 1", "1939 Atlantic tropical storm 1") ],
#   [ ("--year 1939 --id 2", "1939 Atlantic hurricane 2") ],
#   [ ("--year 1939 --id 3", "1939 Atlantic tropical storm 3") ],
#   [ ("--year 1939 --id 4", "1939 Atlantic hurricane 4") ],
#   [ ("--year 1939 --id 5", "1939 Atlantic hurricane 5") ],
#   [ ("--year 1941 --id 1", "1941 Atlantic tropical storm 1") ],
#   [ ("--year 1941 --id 2", "1941 Atlantic hurricane 2") ],
#   [ ("--year 1941 --id 3", "1941 Atlantic hurricane 3") ],
#   [ ("--year 1941 --id 4", "1941 Central American hurricane") ],
#   [ ("--year 1941 --id 5", "1941 Atlantic hurricane 5") ],
#   [ ("--year 1941 --id 6", "1941 Atlantic tropical storm 6") ],
#   [ ("--year 1943 --id 1", "1943 Surprise hurricane") ],
#   [ ("--year 1944 --id 11", "1944 Sanibel Island hurricane") ],
#   [ ("--year 1944 --wind 120 --extra 0", "1944 Atlantic hurricane") ],
#   [ ("--year 1945 --id 1", "1945 Atlantic hurricane 1") ],
#   [ ("--year 1945 --id 2", "1945 Atlantic tropical storm 2") ],
#   [ ("--year 1945 --id 3", "1945 Atlantic tropical storm 3") ],
#   [ ("--year 1945 --id 4", "1945 Atlantic tropical storm 4") ],
#   [ ("--year 1945 --id 5", "1945 Atlantic hurricane 5") ],
#   [ ("--year 1945 --id 6", "1945 Atlantic tropical storm 6") ],
#   [ ("--year 1945 --id 7", "1945 Atlantic tropical storm 7") ],
#   [ ("--year 1945 --id 8", "1945 Atlantic tropical storm 8") ],
#   [ ("--year 1945 --id 9", "1945 Atlantic hurricane 9") ],
#   [ ("--year 1945 --id 10", "1945 Atlantic hurricane 10") ],
#   [ ("--year 1945 --id 11", "1945 Atlantic hurricane 11") ],
#   [ ("--year 1946 --id 1", "1946 Atlantic tropical storm 1") ],
#   [ ("--year 1946 --id 2", "1946 Atlantic hurricane 2") ],
#   [ ("--year 1946 --id 3", "1946 Atlantic tropical storm 3") ],
#   [ ("--year 1946 --id 4", "1946 Atlantic hurricane 4") ],
#   [ ("--year 1946 --id 5", "1946 Atlantic hurricane 5") ],
#   [ ("--year 1946 --id 6", "1946 Atlantic tropical storm 6") ],
#   [ ("--year 1947 --id 1", "1947 Atlantic tropical storm 1") ],
#   [ ("--year 1947 --id 2", "1947 Atlantic hurricane 2") ],
#   [ ("--year 1947 --id 3", "1947 Atlantic hurricane 3") ],
#   [ ("--year 1947 --id 4", "1947 Fort Lauderdale hurricane") ],
#   [ ("--year 1947 --id 5", "1947 Atlantic tropical storm 5") ],
#   [ ("--year 1947 --id 6", "1947 Atlantic tropical storm 6") ],
#   [ ("--year 1947 --id 7", "1947 Atlantic tropical storm 7") ],
#   [ ("--year 1947 --id 8", "1947 Atlantic hurricane 8") ],
#   [ ("--year 1947 --id 9", "1947 Atlantic hurricane 9") ],

# Unnamed storms since start of naming
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
#      [ ("--year 2005 --id 19", "2005 Atlantic subtropical storm 19") ],
#      [ ("--year 2006 --id 2", "2006 Atlantic tropical storm 2") ],

#      [ ("--year 1954 --id 1 --name Alice --extra 0", "Alice1 1954", "Hurricane Alice1 (1954)") ],
#      [ ("--year 1954 --id 11 --name Alice --extra 0", "Alice2 1954", "Hurricane Alice2 (1954)") ],
#      [ ("--year 1977 --name Babe --extra 0", "Babe Atlantic 1977", "Hurricane Babe (1977)") ],

      # Zone-crossers
      #[ ("--year 1996 --name cesar --next --input epac.txt --year 1996 --name douglas", "Cesar-Douglas 1996", "Hurricane Cesar-Douglas (1996)") ],
      #[ ("--year 1974 --name fifi --next --input epac.txt --year 1974 --name orlene", "Fifi-Orlene 1974", "Hurricane Fifi-Orlene (1974)") ],
      #[ ("--year 1988 --name joan --next --input epac.txt --year 1988 --name miriam", "Joan-Miriam 1988", "Hurricane Joan-Miriam (1988)") ],
      #[ ("--year 1961 --name hattie --next --input epac.txt --year 1961 --name simone --next --year 1961 --input natlantic.txt --name inga", "Hattie-Simone-Inga 1961", "Hurricane Hattie-Simone-Inga (1961)") ],
      #[ ("--year 1978 --name Greta --next --input epac.txt --year 1978 --name Olivia", "Greta-Olivia 1978", "Hurricane Greta-Olivia (1978)") ],

     ) ],


   "wpac" =>
   [ (
#     [ ("--year 1957 --id 1 --name \"not named\"", "1957 West Pacific tropical storm 1") ],
#     [ ("--year 1957 --id 8 --name \"not named\"", "1957 West Pacific tropical storm 8") ],
#     [ ("--year 1957 --id 17 --name \"not named\"", "1957 West Pacific tropical storm 17") ],
     )],

   "south" =>
   [ (
      # Southern hemisphere numbering is weird because the storms are numbered
      # by season not by year, so there are two ID 5 storms in 1970 - one 
      # part of 1969-70 and one part of 1970-71 seasons.
#      [ ("--year 1970 --id 5 --wind 60", "Ada 1970", "Cyclone Ada (1970)") ],
#      [ ("--year 1971 --id 9 --wind 60", "Althea 1971", "Cyclone Althea (1971)") ],
#      [ ("--year 1974 --id 19", "Wanda 1974", "Tropical Storm Wanda (1974)") ],
#      [ ("--year 1974 --id 7", "Tracy 1974", "Cyclone Tracy (1974)") ],
     )],
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
	$args = "$args --id \"$name\"";
      } else {
	$args = "$args --name \"$name\"";
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
