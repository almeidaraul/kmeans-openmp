#!/bin/bash
INPUTDIR="inputs"
INPUTFILES=( "10x1M.txt" "10x2M.txt" "10x5M.txt" )
CPUVALUES=( 1 2 4 8 )
CODE="$1.c"
OUTPUTFILE="$2.csv"
CFLAGS="-fopenmp"
NUM_EXECS=5

echo "Creating $OUTPUTFILE and compiling $CODE, skmeans.c"

echo "CPUs;Input Size;Time;Output" > $OUTPUTFILE
gcc $CODE $CFLAGS -o tmprun
gcc skmeans.c $CFLAGS -o oskmeans

echo "Creating reference output files"
for (( INPUT=0; INPUT<${#INPUTFILES[@]}; INPUT++ ))
do
		INPUTFILE=$INPUTDIR"/"${INPUTFILES[INPUT]}
		./oskmeans < $INPUTFILE > oskmeans-$INPUT.out
		head oskmeans-$INPUT.out --lines=-2 > oskmeans-$INPUT.out
done

echo "Running parallel code"
for CPU in "${CPUVALUES[@]}"
do
	echo "OMP_NUM_THREADS=$CPU"
	export OMP_NUM_THREADS=$CPU
	for (( INPUT=0; INPUT<${#INPUTFILES[@]}; INPUT++ ))
	do
		INPUTFILE=$INPUTDIR"/"${INPUTFILES[INPUT]}
		echo $INPUTFILE

		for (( ITERATION=0; ITERATION<$NUM_EXECS; ITERATION++ ))
		do
			./tmprun < $INPUTFILE > tmprun.out
			EXECTIME=$(tail -n 1 tmprun.out)

			head tmprun.out --lines=-2 > tmprun.out
			diff tmprun.out oskmeans-$INPUT.out > difffile

			OUTOK="y"
			if [ -s "difffile" ]
			then
				OUTOK="n"
			fi
			echo $CPU";"${INPUTFILES[INPUT]}";"$EXECTIME";"$OUTOK >> $OUTPUTFILE
		done
		rm oskmeans-$INPUT.out
	done
done
rm tmprun oskmeans *.out difffile

echo "Saved information to $OUTPUTFILE"
