echo "Enter names of two files"
read first

cat> $first
chmod 333 $first

read second
cat> $second
chmod 333 $second

ls -l
