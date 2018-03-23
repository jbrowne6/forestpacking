#!/bin/bash
runTimes=10
cd ..
rm runTimes.csv

for j in `seq 0 4`;
do
    for i in `seq 1 $runTimes`;
    do
        ./bin/packerWriteTime $j 1
    done
done

for j in `seq 5 8`;
do
    for i in `seq 1 $runTimes`;
    do
        ./bin/packerWriteTime $j 1 125 3
    done
done

for j in `seq 15 15`;
do
    for i in `seq 1 $runTimes`;
    do
        ./bin/packerWriteTime $j 1 125 4
    done
done

mv runTimes.csv results/timeAll.csv
