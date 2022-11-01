#!/bin/bash
NPROC=1

if [ "$(uname)" == "Darwin" ]; then
     NPROC=$(sysctl -a | grep machdep.cpu.core_count | cut -d ':' -f 2)     
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
     NPROC=$(nproc)
fi

DIR=bootloader-tftp

rm -rf /tmp/$DIR
mkdir /tmp/$DIR

cd ../$DIR

MAKEFILE=Makefile*.GD32

for m in $MAKEFILE
do
	make -f $m -j $NPROC clean
	make -f $m -j $NPROC
	retVal=$?
			
	if [ $retVal -ne 0 ]; then
		echo "Error : " "$f" " : " "$m"
		exit $retVal
	fi
			
	SUFFIX=$(echo $m | cut -d '-' -f 2 | cut -d '.' -f 1)
		
	if [ $SUFFIX == 'Makefile' ]
	then
		cp gd32f4xx.bin /tmp/$DIR
	else
		echo $SUFFIX
		mkdir /tmp/$DIR/$SUFFIX
		cp gd32f4xx.bin /tmp/$DIR/$SUFFIX
	fi		
done

cd /tmp/$DIR
			
find . -name gd32f4xx.bin | sort | xargs ls -al
find . -name gd32f4xx.bin | xargs ls -al | wc -l

cd -