#!/bin/bash
cd ~/forestpacking/experiments
echo "starting run for 1st figure"
./figure5.sh
echo "starting run for 2nd figure"
#./figure6.sh
echo "starting run for 3rd figure"
#./figure4.sh
echo "starting run for 4th figure"
#./figure7.sh

cd ../results
echo "Creating figures based on calculated data."
#Rscript figure4.R
Rscript figure5.R
#Rscript figure6.R
#Rscript figure7.R

if [ -d /resultpngs ]; then
	cp *.png /resultpngs;
fi
