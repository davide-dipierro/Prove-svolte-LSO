#!/bin/bash

# Verifica se sono state fornite due directory come argomenti
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <directory1> <directory2>"
    exit 1
fi
dir1="$1"
dir2="$2"
lista_copiati=()

# Funzione per confrontare il contenuto delle directory e copiare i file mancanti
compare_and_copy() {
    local source_dir="$1"
    local dest_dir="$2"
    
    # Itera su tutti gli elementi nella directory di origine
    for item in "$source_dir"/*; do
        base_name=$(basename "$item")

        # Verifica se l'elemento esiste nella directory di destinazione
        if [ ! -e "$dest_dir/$base_name" ]; then
            # Copia l'elemento mancante nella directory di destinazione
            cp -r "$item" "$dest_dir/"
            # Aggiungi il file alla lista dei file copiati
            lista_copiati+=("$base_name")
        fi
    done
}

# Esegue la funzione per entrambe le directory
compare_and_copy "$dir1" "$dir2"
compare_and_copy "$dir2" "$dir1"

# Stampa il contenuto di ogni directory
echo -e "\nContenuto di $dir1:"
ls -l "$dir1"

echo -e "\nContenuto di $dir2:"
ls -l "$dir2"

# Stampa le dimensioni delle directory
echo -e "\nDimensione di $dir1:"
ls -l | awk -v dir1="$dir1" '$9 ~ dir1 {print $5}' 

echo -e "\nDimensione di $dir2:"
ls -l | awk -v dir2="$dir2" '$9 ~ dir2 {print $5}' 

# Stampa i file copiati
echo -e "\nFile copiati:"
for file in "${lista_copiati[@]}"; do
    echo "$file"
done

