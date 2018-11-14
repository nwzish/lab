#!/bin/sh

echo "Welcome to the DOS interpreter"
echo "Type Ctrl-C to exit"

while [ "forever" ]
do
  echo "DOS> \c"  
  read command arg1 arg2
  case $command in
    cd)
      cd $arg1
      ;;
    dir)
      ls
      ;;
    type)
      cat $arg1
      ;;
    del)
      rm $arg1
      ;;
    ren)
      mv $arg1 $arg2
      ;;
    copy)
      cp $arg1 $arg2
      ;;
    *)
      echo "DOS does not recognise the command $command"
      ;;
  esac   
done