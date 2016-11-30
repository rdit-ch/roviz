#!/bin/bash

function rename_file
{

    for file in ${@:3}; do
        if echo "$file" | grep $1 > /dev/null 2> /dev/null; then
            mv "$file" "$(echo $file | sed s/$1/$2/)"
        fi
    done
}

# Default template
template="plugins/template"

if [ "$#" -eq 2 ]; then
    template="$2"
elif [ "$#" -ne 1 ]; then
    echo "Usage: ./new_project.sh ClassName [template]"
    exit 22
fi

classname="$1"
subdir="plugins"
# Convert to UPPER CASE
upper=$(echo "$classname" | tr '[:lower:]' '[:upper:]')
# Convert from CamelCase to underscore_seperated
filename=$(echo "$classname" | sed -r 's/([a-z0-9])([A-Z])/\1_\L\2/g' | tr '[:upper:]' '[:lower:]')
proj_path="plugins/$filename"

if [ -e "$proj_path" ]; then
    echo "Error: Destination path already exists"
    exit 17
fi

cp -r "$template" "$proj_path"
rename_file TEMPLATE_FILE "$filename" "$proj_path/"*
rename_file TEMPLATE_CLASS "$classname" "$proj_path/"*
sed -i "s/TEMPLATE_FILE/$filename/g" "$proj_path/"*
sed -i "s/TEMPLATE_CLASS/$classname/g" "$proj_path/"*
sed -i "s/TEMPLATE_UPPER/$upper/g" "$proj_path/"*
echo "SUBDIRS += $filename" >> "plugins/plugins.pro"

echo "Created project '$proj_path' for class '$classname'"

exit 0
