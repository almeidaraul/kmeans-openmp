#!/bin/bash
INPUTDIR="inputs"
INPUTFILES=( "10x1M.txt" ) # "10x2M.txt" "10x5M.txt" )
CPUVALUES=( 1 ) # 2
CODE="$1.c"
OUTPUTFILE="$2.csv"
CFLAGS="-fopenmp"

echo "criando arquivo"

echo "CPUs;Input Size;Time;Output" > $OUTPUTFILE
gcc $CODE $CFLAGS -o tmprun
gcc skmeans.c $CFLAGS -o oskmeans

# create reference file for comparison
echo "criando arquivos de referencia"
for (( INPUT=0; INPUT<${#INPUTFILES[@]}; INPUT++ ))
do
		INPUTFILE=$INPUTDIR"/"${INPUTFILES[INPUT]}
		./oskmeans < $INPUTFILE > oskmeans-$INPUT.out
		head oskmeans-$INPUT.out --lines=-2 > oskmeans-$INPUT.out
done

# run parallel version
echo "versao paralela"
for CPU in "${CPUVALUES[@]}"
do
	export OMP_NUM_THREADS=$CPU
	for (( INPUT=0; INPUT<${#INPUTFILES[@]}; INPUT++ ))
	do
		INPUTFILE=$INPUTDIR"/"${INPUTFILES[INPUT]}
		./tmprun < $INPUTFILE > tmprun.out
		EXECTIME=$(tail -n 1 tmprun.out)

		head tmprun.out --lines=-2 > tmprun.out
		diff tmprun.out oskmeans-$INPUT.out > difffile
		rm oskmeans-$INPUT.out

		OUTOK="y"
		if [ -s "difffile" ]
		then
			OUTOK="n"
		fi
		echo $CPU";"${INPUTFILES[INPUT]}";"$EXECTIME";"$OUTOK >> $OUTPUTFILE
	done
done
rm tmprun oskmeans *.out difffile

echo "Saved information to $OUTPUTFILE"
