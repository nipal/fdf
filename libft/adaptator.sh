#!/bin/bash

liste_fichiers=`ls *.c`;


for fichier in $liste_fichiers
do
head -n 5 $fichier > tmp; 
echo "/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */" >> tmp;
tail -n +7 $fichier | sed 's/tboos  /fjanoty/g'>> tmp;
cat tmp > $fichier;
cat $fichier  |  sed 's/cpy(/gfdg(/g' | sed 's/cpy\./kjfh/g'|sed 's/cpy/copy/g'  | sed 's/kjfh/cpy./g'|sed 's/gfdg(/cpy(/g'\
| sed 's/rabbit/front/g'\
| sed 's/turtle/back/g'\
| sed 's/alst/begin/g' > tmp;
cat tmp > $fichier;

done

