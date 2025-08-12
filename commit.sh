#! /bin/bash

#retreving enviroment variables
ProjectName=$( ./.bash/getEnvVar.sh PROJECT_NAME ./.var/env.txt )
echo $ProjectName

#create CMakeLists.txt
echo "Creating CMakeLists.txt..."
cat ./application/CMakeLists.template| sed "s/project_name/${ProjectName}/g" > ./application/CMakeLists.txt

#append directories
echo "Appending directories to CMake file..."
./.bash/appendDirsToCMakeLists.sh ./

#generate dir CMakeFiles
echo "Generating CMakeLists.txt files in directories..."
./.bash/generateDirCMakeFiles.sh $ProjectName

cd application

#committing
echo "Committing..."

git add .
git status

commitMessage=$1

read -p "Does everything look correct...? (y/N)" confirm
if [[ $confirm == "y" ]]; then
    echo "Commit!"
    git commit -m "${commitMessage}"
else
    echo "Resetting..."
    git restore --staged
fi

cd ..
#cleanup
echo "cleanup..."
rm ./application/CMakeLists.txt

