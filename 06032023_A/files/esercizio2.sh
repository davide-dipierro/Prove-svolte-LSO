#!/bin/bash

scelta=0
while [ $scelta -ne 4 ];
do
    echo "Scegli un'opzione"
    echo "1) Aggiungi verifica"
    echo "2) Conta"
    echo "3) Media"
    echo "4) Uscita"
    read scelta
    case $scelta in
        1) echo "Inserisci il giorno: "
            read giorno
            echo "Inserisci il mese nel formato di 3 lettere (gen feb mar): "
            read mese
            echo "Inserisci l'anno: "
            read anno
            echo "Inserisci il nome dello studente: "
            read nome
            echo "Inserisci il voto: "
            read voto
            echo $giorno,$mese,$anno,$nome,$voto >> verifica
            ;;
        2) echo "Inserisci il nome dello studente: "
            read nome
            echo "Inserisci il mese in cui contare le prove: "
            read mese
            risultato=$(awk -F, -v mese="$mese" -v nome="$nome" 'BEGIN{somma=0} {if($2==mese && $4==nome) somma=somma+1} END {print somma}' verifica)
            echo "In $mese ci sono $risultato prove per $nome"
            ;;
        3) echo "Inserisci il nome dello studente: "
            read nome
            somma=$(awk -F, -v nome="$nome" 'BEGIN{somma=0} {if($4==nome) somma=somma+$5} END {print somma}' verifica)
            numero=$(awk -F, -v nome="$nome" 'BEGIN{somma=0}{if($4==nome) somma=somma+1} END {print somma}' verifica)
            media=$((somma/numero))
            echo "La media è: $media"
            ;;
        4) echo "Uscita"
            ;;
        *) echo "Scelta non valida"
            ;;
    esac
done

