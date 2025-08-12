#! /bin/bash

AppName=$1
MatchFiles="\\.(h|cpp|c)$"

shopt -s globstar # Enable recursive globbing
for dir in ./application/src/project/**/; do
  if [[ -d "$dir" && ! -L "$dir" && "$dir" != ../application/src/project/assets/ ]]; then
    echo "Processing directory: $dir"
    # Add your commands here
    
    if [[ -f "./$dir/CMakeLists.txt" ]]; then
        echo "File exists, removing old file..."
        rm "./$dir/CMakeLists.txt"
    else
        echo "File Does Not Exist"
    fi
 
    echo "Generating File"
    touch "./${dir}CMakeLists.txt"

    #this is where the new file is built
    echo "target_sources($AppName PRIVATE" >> "./${dir}CMakeLists.txt" 
        
    for file in ./${dir}*; do
        # Check if the item is a regular file (not a directory)
        if [[ -f "$file" ]] && [[ $file =~ $MatchFiles ]]; then
            echo "Found file: $file"

            #append file to Generated CMakeLists
            filename=$(basename $file)
            echo "  $filename" >> "./${dir}CMakeLists.txt"
        fi
    done       

    echo ")" >> "./${dir}CMakeLists.txt"
  fi
done
shopt -u globstar # Disable globstar after use
