#!/bash/bin


if [ -s "$1" ]
then
  gcc "$1" -o "$2"  && ./"$2"
else
  echo "Error: you entered invalid filename"
fi
