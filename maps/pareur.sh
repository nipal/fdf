#/bin/zsh

echo -n '{' > tmp
cat $1 >> tmp
echo -n '}' >> tmp

#cat tmp | tr '\n' '$' > tmp2
#cat tmp2 | sed /$/}${/



cat tmp | tr '\n' 'B'| sed  "s/B/},B{/g" | sed "s/  / /g" | sed "s/ /, /g"| tr 'B' '\n' > tmp2
