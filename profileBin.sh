#!/bin/bash

#improv6---------------------------------------------------
sudo rm perf/improv6bin.csv

#number of batches to use, power of 2
for j in `seq 0 6`;
do
    var=$((2**$j))

    #number of levels to intertwine.
    for i in `seq 0 6`;
    do
        sudo -v
        sudo echo $var, $i >> perf/improv6bin.csv
        sudo perf stat -r 5 -x - -o perf/improv6bin.csv --append -e "{instructions, task-clock, cache-misses, cache-references, l1d.replacement}" ./bin/packer 6 0 $var $i 

        sudo -v
        sudo perf stat -r 5 -x - -o perf/improv6bin.csv --append -e "{instructions, task-clock, cache-misses, cache-references, l1d.replacement}" ./bin/packer 6 1 $var $i
    done
done
