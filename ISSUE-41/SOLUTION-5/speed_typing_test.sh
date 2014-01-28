#!/bin/sh
echo -e "Please enter text:\nMake code which displays text, then measures how"
echo -e "fast and correct one would enter this test via the keyboard.\n"
echo -e "Start enter text\n"
line1="Make code which displays text, then measures how"
line2="fast and correct one would enter this test via the keyboard."
START_TIME=$SECONDS
read input_variable1
read input_variable2
ELAPSED_TIME=$(($SECONDS - $START_TIME))
if [ "$line1" != "$input_variable1" ] ;
then
    echo "line 1 entered incorrect"
fi
if [ "$line2" != "$input_variable2" ] ;
then
    echo "line 2 entered incorrect"
fi
echo -e "You entered:\n$input_variable1\n$input_variable2"
echo "elapsed time $(($ELAPSED_TIME/60)) min $(($ELAPSED_TIME%60)) sec"
