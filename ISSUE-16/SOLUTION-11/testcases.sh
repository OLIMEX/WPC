#/bin/sh
./shunting-yard "(((3+6)*(2-4))+7)"
echo "3 6 + 2 4 - * 7 + is answer"
./shunting-yard "(10 + 20) / (30 - 40)"
echo "10 20 + 30 40 - / is answer"
