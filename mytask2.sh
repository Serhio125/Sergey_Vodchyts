#!/bash/bin/

catalog=$1
let n=0

if [ -d "$catalog" ]
then
   files=$(find "$catalog" -type f)
   for file in $files
   do
     find "$catalog" -type f -wholename "$file" -printf "%p %s %M\n"
     let n=n+1
   done 
   echo "Count of viewing files: $n"
else
  echo "Error: you entered invalid catalog"
fi
