#!/bin/bash

#improv6---------------------------------------------------
sudo rm perf/improv6bin.csv

#number of batches to use, power of 2
for j in `seq 0 1`;
do
    var=$((2**$j))

    #number of levels to intertwine.
    for i in `seq 0 1`;
    do
        sudo -v
        sudo echo $var, $i >> perf/improv6bin.csv
        sudo perf stat -r 1 -x - -o perf/improv6bin.csv --append -e "{instructions, task-clock, cache-misses, cache-references,L1-dcache-loads}" ./bin/packer 6 0 $var $i 

        sudo -v
        sudo perf stat -r 1 -x - -o perf/improv6bin.csv --append -e "{L1-dcache-loads,L1-dcache-load-misses, L1-dcache-prefetches, L1-dcache-prefetch-misses, cpu-clock}" ./bin/packer 6 1 $var $i
    done
done
