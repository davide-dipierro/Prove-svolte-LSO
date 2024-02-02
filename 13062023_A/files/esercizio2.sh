#!/bin/bash

aggiungi_titolo(){
	if [ "$1" == "M" ]; then
		echo "Sig.re $2"
	elif [ "$1" == "F" ]; then
		echo "Sign.ra $2"
	else
		echo $2
	fi
}

stipendio_minimo=9999999
stipendio_massimo=0
media_stipendi=0
numero_dipendenti=0
while IFS=, read -r  nome cognome genere stipendio assunzione; do
	nome_completo=$(aggiungi_titolo "$genere" "$cognome")
	if [ "$stipendio" -lt "$stipendio_minimo" ]; then
    		stipendio_minimo="$stipendio"
	fi
	if [ "$stipendio" -gt "$stipendio_massimo" ]; then
		stipendio_massimo="$stipendio";
	fi
	media_stipendi=$(( media_stipendi + stipendio ))
	numero_dipendenti=$(( numero_dipendenti + 1 ))	
echo "$nome_completo, $nome, $genere, $stipendio, $assunzione"
done < paghe.txt
echo "Stipendio massimo: $stipendio_massimo"
echo "Stipendio minimo: $stipendio_minimo"
media_stipendi=$(( media_stipendi / numero_dipendenti ))
echo "Media stipendi: $media_stipendi"

read -p "Inserisci il bonus per lo stipendio minimo: " bonus
read -p "Si vuole modificare il file incrementando lo stipendio minimo? (y/n) " modifica

if [ "$modifica" == "y" ]; then
	sed -i "s/$stipendio_minimo/$((stipendio_minimo+bonus))/g" paghe.txt
else
	 sed "s/$stipendio_minimo/$((stipendio_minimo+bonus))/g" paghe.txt
fi


