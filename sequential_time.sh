#!/bin/bash
INPUTDIR="inputs"
INPUTFILES=( "10x1M.txt" "10x2M.txt" "10x5M.txt" )
CPUVALUES=( 1 2 4 8 )
CODE="$1"
CFLAGS="-fopenmp -Wextra -O3"
NUM_EXECS=10


for CPU in "${CPUVALUES[@]}"
do
	echo "cpu=$CPU"
	gcc $CODE $CFLAGS -o tmprun
	export OMP_NUM_THREADS=$CPU
	for (( INPUT=0; INPUT<${#INPUTFILES[@]}; INPUT++ ))
	do
		for (( I=0; I<$NUM_EXECS; I++ ))
		do
			echo "I=$I"
			echo "entrada=${INPUTFILES[INPUT]}"
			INPUTFILE=$INPUTDIR"/"${INPUTFILES[INPUT]}
			./tmprun < $INPUTFILE | tail -n 2
		done
	done
done

rm tmprun
