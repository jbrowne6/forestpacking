#!/bin/bash

for i in `seq 1 10`;
do
sudo perf stat -x - -o perf/naive.out --append -e "{instructions, branch-misses, cache-misses, cache-references, l1d.replacement}" ./bin/packer 0 0
done
