#!/bin/bash
# pouzitie: ./shift.sh x
# posunie vsetky subory s cislami x a viac o 1 vyssie

cislo='^[0-9]+$'
if ! [[ $1 =~ $cislo ]] ; then
   echo "parameter musi byt cislo" >&2; exit 1
fi

cisla=()
for nr in `ls | sed -e's/^\([0-9][0-9]*\)\(.*\)/\1/' | sort -n -r| uniq`; do
  if [[ $nr =~ $cislo ]] ; then
    if (( $nr >= $1 )) ; then      
      cisla+=($nr)
    fi
  fi
done

for t in ${cisla[@]}; do
  nt=$(( $t + 1 ))
  for f in `find . -regex "\./$t[^0-9]*"`; do
    mv $f  `echo $f | sed -e"s/$t/${nt}/g"`
  done
done

