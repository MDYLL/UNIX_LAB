#!/bin/bash

FILE='duck.xml'

function show
{
	if [[ $1 = '0' ]];then
		while read LINE;do
			echo DUCK
			echo Name ${LINE:6:`expr length $LINE` - 13}
			read LINE
			echo Weigth ${LINE:8:`expr length $LINE` - 17}
			read LINE
			echo IQ ${LINE:4:`expr length $LINE` - 9}
			read LINE
			echo Color ${LINE:7:`expr length $LINE` - 15}
			read LINE
			echo Age ${LINE:5:`expr length $LINE` - 11}
			# echo `expr length $LINE`
		done < $FILE
	else
		while read LINE;do
			if [[ ${LINE:6:`expr length $LINE` - 13} != $1 ]];then
				read LINE
				read LINE
				read LINE
				read LINE
			else
			echo DUCK
			echo Name ${LINE:6:`expr length $LINE` - 13}
			read LINE
			echo Weigth ${LINE:8:`expr length $LINE` - 17}
			read LINE
			echo IQ ${LINE:4:`expr length $LINE` - 9}
			read LINE
			echo Color ${LINE:7:`expr length $LINE` - 15}
			read LINE
			echo Age ${LINE:5:`expr length $LINE` - 11}
			fi
		done < $FILE
	fi

}
function add
{
	read -p 'Input Name: ' name
	read -p 'Input Weight: ' weight 
	read -p 'Input IQ: ' iq
	read -p 'Input Color: ' color

	read -p 'Input Age: ' age
	{
		echo "<Name>${name}</Name>"
		echo "<Weight>${weight}</Weight>"
		echo "<IQ>${iq}</IQ>"
		echo "<Color>${color}</Color>"
		echo "<Age>${age}</Age>"

	} >>$FILE

}
function change
{

	TEMP='temp.xml'
	touch $TEMP
	while read LINE;do
			if [[ ${LINE:6:`expr length $LINE` - 13} != $1 ]];then
				echo $LINE >> $TEMP
				read LINE
				echo $LINE >> $TEMP
				read LINE
				echo $LINE >> $TEMP
				read LINE
				echo $LINE >> $TEMP
				read LINE
				echo $LINE >> $TEMP
			elif [[ $2 = 'del' ]];then
				read LINE
				read LINE
				read LINE
				read LINE
			else
				if [[ $2 = 'Name' ]];then
					LINE="<Name>$3</Name>"
				fi
				echo $LINE >> $TEMP
				read LINE
				if [[ $2 = 'Weight' ]];then
					LINE="<Weight>$3</Weight>"
				fi
				echo $LINE >> $TEMP
				read LINE
				if [[ $2 = 'IQ' ]];then
					LINE="<IQ>$3</IQ>"
				fi
				echo $LINE >> $TEMP
				read LINE
				if [[ $2 = 'Color' ]];then
					LINE="<Color>$3</Color>"
				fi
				echo $LINE >> $TEMP
				read LINE
				if [[ $2 = 'Age' ]];then
					LINE="<Age>$3</Age>"
				fi
				echo $LINE >> $TEMP
			fi
		done < $FILE
	rm $FILE
	mv $TEMP $FILE

}
echo Duck Tales
echo 5 parameteres:
echo Name
echo Weight
echo IQ
echo Color
echo Age

while true
do
	echo ===========================================================
	echo Commands:
	echo show - show Ducks
	echo show Name_ - show Ducks with Name == Name_
	echo add - add Duck
	echo del Name_ - delete Duck with Name == Name_
	echo change Name_ Parameter_ Value_ - change parameter Parameter_ of Duck with Name == Name_ on Value_
	read -p 'Input command: ' command

	if [[ $command = 'show' ]]; then
		show '0'
	elif [[ ${command:0:4} = 'show' ]]; then
		show ${command:5}
	elif [[ $command = 'add' ]]; then
		add
	elif [[ ${command:0:6} = 'change' ]]; then
		change ${command:7}
	elif [[ ${command:0:3} = 'del' ]]; then
		change ${command:4} 'del'

	fi

done
