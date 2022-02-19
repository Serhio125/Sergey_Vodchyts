#!/bash/bin

dist=$1
extension=$3
catalog=$2

if [ -z "$dist" ]
then
    echo "Error: you entered invalid file name"
elif [ -z "$extension"  ]
then
    echo "Error: you entered invalid extension"
elif [ -d "$catalog" ]
then
   find "$catalog" -type f -name "*.$extension" | sort -i>"$dist" 
else
    echo "Error: you entered invalid catalog"

fi
