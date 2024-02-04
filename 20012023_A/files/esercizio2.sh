#!/bin/bash

# Verifica che sia stato fornito un file come argomento
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <groups_file>"
    exit 1
fi

groups_file="$1"

# (a) Stampa il numero massimo di campi di una linea in un dato file
max_fields=$(awk -F':' '{print NF}' "$groups_file" | sort -n | tail -n 1)
echo "(a) Numero massimo di campi in una linea: $max_fields"

# (b) Crea una sottodirectory per ogni gruppo e assegna permessi agli utenti di "adm" e "admins"
while IFS=":" read -r group_name x gid users; do
    dir_name="subdir_$group_name"
    mkdir -p "$dir_name"
    group_members=$(echo "$users" | sed 's/,/ /g')
    
    # Imposta i permessi sulla directory
    chmod 770 "$dir_name"
    chown :"$group_name" "$dir_name"
    
    # Imposta i permessi sugli utenti di "adm" e "admins"
    for user in $group_members adm admins; do
        usermod -aG "$group_name" "$user"
        chmod +rw "$dir_name" # Aggiunge permessi di lettura e scrittura
    done
done < "$groups_file"


# (c) Crea un file per ogni sottodirectory contenente gli utenti del gruppo riga per riga
while IFS=":" read -r group_name x gid users; do
        dir_name="subdir_$group_name"
        echo "$users" | tr ',' '\n' > "$dir_name/users.txt"
done < "$groups_file"

echo "Script completato con successo."
