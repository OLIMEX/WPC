#!/bin/sh

#   /--|
#   |  o
#   | /|\
#   | / \
#  ---
# A hangman in bash
#
#  by notzed

# Source of words
inwords="/usr/share/dict/words"

# Game style
# 0 = normal
# 1 = computer says no
mode=1

# Show inner workings
debug=0

# clean up the words in dict, it contains proper nouns and hypenated words
# even with this there are some doozies
echo "Building clean word list"
words="/tmp/words.$$"
grep -v -e "^[[:upper:]]" ${inwords} | grep -v -e "[^[:alpha:]]" > ${words}
# list of words which are the same length
list="/tmp/words.same.$$"

function quit() {
    rm $words
    rm $list

    c=0
    while [ $c -lt 10 ] ; do
	clear
	showman $c "" ""
	usleep 250000
	c=`expr $c + 1`
    done

    clear
    showman 10 "by NotZed" "BYE!"

    exit 0
}

function showman() {
    w=`echo $2 | sed -e 's/\(.\)/\\1 /g'`
    g=`echo $3 | sed -e 's/^\(.\{8\}\).*/\\1/' -e 's/\(.\)/\\1 /g'`
    h=`echo $3 | sed -e 's/^.\{,8\}//' -e 's/\(.\)/\\1 /g'`
    echo "/------------------------------\\"
    case $1 in
	0)
	    echo
	    echo "             $g"
	    echo "             $h"
	    echo
	    echo
	    ;;
	1)
	    echo
	    echo "             $g"
	    echo "             $h"
	    echo
	    echo "   ---"
	    ;;
	2)
	    echo
	    echo "    |        $g"
	    echo "    |        $h"
	    echo "    |"
	    echo "   ---"
	    ;;
	3)
	    echo "    /--"
	    echo "    |        $g"
	    echo "    |        $h"
	    echo "    |"
	    echo "   ---"
	    ;;
	4)
	    echo "    /--|"
	    echo "    |        $g"
	    echo "    |        $h"
	    echo "    |"
	    echo "   ---"
	    ;;
	5)
	    echo "    /--|"
	    echo "    |  o     $g"
	    echo "    |        $h"
	    echo "    |"
	    echo "   ---"
	    ;;
	6)
	    echo "    /--|"
	    echo "    |  o     $g"
	    echo "    |  |     $h"
	    echo "    |"
	    echo "   ---"
	    ;;
	7)
	    echo "    /--|"
	    echo "    |  o     $g"
	    echo "    |  |     $h"
	    echo "    | /"
	    echo "   ---"
	    ;;
	8)
	    echo "    /--|"
	    echo "    |  o     $g"
	    echo "    |  |     $h"
	    echo "    | / \\"
	    echo "   ---"
	    ;;
	9)
	    echo "    /--|"
	    echo "    |  o     $g"
	    echo "    | /|     $h"
	    echo "    | / \\"
	    echo "   ---"
	    ;;
	10)
	    echo "    /--|"
	    echo "    |  x     $g"
	    echo "    | /|\\    $h"
	    echo "    | / \\"
	    echo "   ---"
	    ;;
    esac
    echo "    $w"
    echo "\------------------------------/"
}

function debug() {
    if [ $debug -eq 1 ] ; then
	echo $*
    fi
}

function play() {
    word=`shuf -n 1 ${words}`
    guess=`echo $word | sed s/./_/g`
    wrong=0
    tries=""
    found=0

    debug "word chosen $word"
    debug "guess '$guess'"

    # optimise: build list of words the same length
    grep -e "^.\{${#word}\}\$" ${words} > ${list}

    while [ $found -eq 0 -a $wrong -lt 10 ] ; do
	echo
	showman $wrong $guess $tries
	echo

	letter=""
	while [ -z "$letter" ] ; do
	    echo -n "Your guess? > "
	    read letter
	    if [ "x$letter" = "xquit" ] ; then
		quit
	    fi
	done
	echo

	tries="${tries}${letter:0:1}"

	echo -n "Hmm, let me think ... "

	# check for match
	echo $word | grep -q -e "${letter}"
	match=$?
	if [ $mode -eq 1 -a $match -eq 0 ] ; then
	    debug "Word contains that letter"
	    # see if another word without a match exists
	    pattern="^`echo $guess | sed -e "s/_/\[^${tries}]/g"`\$"
	    debug "Testing pattern $pattern"
	    grep -q -e "${pattern}" "${list}"
	    if [ $? -eq 0 ] ; then
		word=`grep -e "${pattern}" "${list}" | shuf -n 1`
		debug "iCheat: Changing word to: $word"
		match=1
	    else
		debug "No other word I can use"
	    fi
	fi
	if [ $match -eq 0 ] ; then
	    debug "correct guess: $letter"
	    guess=`echo -n $word | tr -c ${tries} _`
	    echo "$guess" | grep -q -e _
	    found=$?
	else
	    echo "Wrong!"
	    wrong=`expr $wrong + 1`
	fi
    done
    echo
    if [ $found -eq 1 ] ; then
	echo "You live!"
    else
	showman $wrong $guess $tries
	echo "You die!"
    fi
    echo
    echo "The correct word was: $word"
}

go="y"

echo "************************************************************************"
echo 
echo "Welcome to hang-man bash."
echo 
echo "       /--|"
echo "       |  o /"
echo "       | /|"
echo "       | / \\"
echo "      ---"
echo 
echo "Choose a letter carefully, each wrong guess brings"
echo "you one step closer to total oblivion"
echo
echo "Type quit to quit the game"
echo
echo "************************************************************************"

while [ "x${go}" = "xy" ] ; do
    play
    echo
    echo -n "Have another go? [y/n] >"
    read go
done
echo "See-ya!"

quit

