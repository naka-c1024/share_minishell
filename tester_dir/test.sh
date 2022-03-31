#!/bin/bash

# echo -e "echo hello world\nexit" | ./minishell

# 標準入力を受け取ってファイルの中身を出力
# read -p "ファイルpathを入力 > " str
# while read line
# do
# 	echo $line
# done < $str

# echo -e "cd ..\npwd" | ../minishell 2>&- | sed -e "/my_shell/d" > mslog.txt
# echo -e "cd ..\npwd" | bash 2>&- > bashlog.txt
# diff -u mslog.txt bashlog.txt && rm mslog.txt bashlog.txt
# echo $?

while read line
do
	echo -e "$line" | ../minishell 2>&- | sed -e "/my_shell/d" > mslog.txt
	echo -e "$line" | bash 2>&- > bashlog.txt
	diff -u mslog.txt bashlog.txt && rm mslog.txt bashlog.txt
	if [ $? -ne 0 ]; then
		echo $line
		break
	fi
done < case.txt # このファイルは必ず最後改行を入れる
