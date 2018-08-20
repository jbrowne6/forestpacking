#!/bin/bash

./bin/experiment1 32
#./bin/experiment3
cd experiments/experiment5/
Rscript experiment5c.R
cd ../..
./bin/experiment5d
