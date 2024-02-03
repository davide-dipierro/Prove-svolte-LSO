#!/bin/bash
echo "Benvenuto in menù"
if [ $# -ne 1 ]
then
     echo "Utilizzo: $0 <nomefile>"
     exit 1
fi

if [ ! -f $1 ]
then
     echo "Il file $1 non esiste"
     exit 2
fi

echo "Cosa vuoi fare?"
echo "1) Cerca"
echo "2) Aggiungi"
echo "3) Elimina"
echo "4) Esci"
read scelta

case $scelta in
     # Cerca
     1) echo "Inserisci il codice"
         read codice
         grep $codice $1
         ;;
     # Aggiungi
     2) echo "Inserisci il codice"
         read codice
         if [ $(grep -c $codice $1) -eq 0 ]
         then
             echo "Il codice non esiste"
             exit 3
         fi
         echo "Inserisci la quantità"
         read quantita
         quantita_file=$(grep "$codice" $1 | awk '{print $2}')
         if [ $quantita_file -lt $quantita ]
         then
             echo "Non ci sono abbastanza prodotti"
             exit 4
         fi
         echo $codice $quantita $costo >> carrello.txt
         ;;
     # Elimina
     3) echo "Inserisci il codice da eliminare"
         read codice
         sed -i "/$codice/d" carrello.txt
         ;;
     # Esci
     4) echo "Arrivederci"
         exit 0
         ;;
     # Scelta non valida
     *) echo "Scelta non valida"
         exit 3
         ;;
esac