#!/bin/bash

#naive-----------------------------------------------------
for i in `seq 1 10`;
do
sudo perf stat -x - -o perf/naive.csv --append -e "{instructions, task-clock, cache-misses, cache-references, l1d.replacement}" ./bin/packer 0 0
done

for i in `seq 1 10`;
do
sudo perf stat -x - -o perf/naiveA.csv --append -e "{instructions, task-clock, cache-misses, cache-references, l1d.replacement}" ./bin/packer 0 1
done

#improv1---------------------------------------------------
for i in `seq 1 10`;
do
sudo perf stat -x - -o perf/improv1.csv --append -e "{instructions, task-clock, cache-misses, cache-references, l1d.replacement}" ./bin/packer 1 0
done

for i in `seq 1 10`;
do
sudo perf stat -x - -o perf/improv1A.csv --append -e "{instructions, task-clock, cache-misses, cache-references, l1d.replacement}" ./bin/packer 1 1
done

#improv2---------------------------------------------------
for i in `seq 1 10`;
do
sudo perf stat -x - -o perf/improv2.csv --append -e "{instructions, task-clock, cache-misses, cache-references, l1d.replacement}" ./bin/packer 2 0
done

for i in `seq 1 10`;
do
sudo perf stat -x - -o perf/improv2A.csv --append -e "{instructions, task-clock, cache-misses, cache-references, l1d.replacement}" ./bin/packer 2 1
done

#improv3---------------------------------------------------
for i in `seq 1 10`;
do
sudo perf stat -x - -o perf/improv3.csv --append -e "{instructions, task-clock, cache-misses, cache-references, l1d.replacement}" ./bin/packer 3 0
done

for i in `seq 1 10`;
do
sudo perf stat -x - -o perf/improv3A.csv --append -e "{instructions, task-clock, cache-misses, cache-references, l1d.replacement}" ./bin/packer 3 1
done

#improv4---------------------------------------------------
for i in `seq 1 10`;
do
sudo perf stat -x - -o perf/improv4.csv --append -e "{instructions, task-clock, cache-misses, cache-references, l1d.replacement}" ./bin/packer 4 0
done

for i in `seq 1 10`;
do
sudo perf stat -x - -o perf/improv4A.csv --append -e "{instructions, task-clock, cache-misses, cache-references, l1d.replacement}" ./bin/packer 4 1
done

#improv5---------------------------------------------------
for i in `seq 1 10`;
do
sudo perf stat -x - -o perf/improv5.csv --append -e "{instructions, task-clock, cache-misses, cache-references, l1d.replacement}" ./bin/packer 5 0 200
done

for i in `seq 1 10`;
do
sudo perf stat -x - -o perf/improv5A.csv --append -e "{instructions, task-clock, cache-misses, cache-references, l1d.replacement}" ./bin/packer 5 1 200
done

#improv6---------------------------------------------------
for i in `seq 1 10`;
do
sudo perf stat -x - -o perf/improv6.csv --append -e "{instructions, task-clock, cache-misses, cache-references, l1d.replacement}" ./bin/packer 6 0 200 3
done

for i in `seq 1 10`;
do
sudo perf stat -x - -o perf/improv6A.csv --append -e "{instructions, task-clock, cache-misses, cache-references, l1d.replacement}" ./bin/packer 6 1 200 3
done
