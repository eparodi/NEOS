#!/bin/bash
#make clean
make all
if [ $? = 0 ];
then
	./run.sh
fi
