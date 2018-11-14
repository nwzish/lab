echo "enter contents of file"
cat >first.txt

grep -v "Dog" first.txt | wc -l
