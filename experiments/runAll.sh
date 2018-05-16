#!/bin/bash
./figure5.sh
./figure6.sh
./figure4.sh
./figure7.sh
./figure7a.sh

cd ../results
Rscript figure4.R
Rscript figure5.R
Rscript figure6.R
Rscript figure7.R
Rscript figure7a.R
