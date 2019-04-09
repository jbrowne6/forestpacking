#!/bin/bash
make

echo 'starting experiment1'
echo 'starting experiment1' >> output.log
./bin/experiment1 32 >> output.log 2>&1

echo 'starting experiment2'
echo 'starting experiment2' >> output.log
./bin/experiment2 >> output.log 2>&1

echo 'starting experiment3'
echo 'starting experiment3' >> output.log
./bin/experiment3 >> output.log 2>&1

echo 'starting experiment4'
echo 'starting experiment4' >> output.log
./bin/experiment4 >> output.log 2>&1

echo 'starting experiment5'
echo 'starting experiment5' >> output.log
echo 'making mini forests'
echo 'making mini forests' >> output.log
cd experiments/experiment5
Rscript writeForest.R >> ../../output.log 2>&1
echo 'testing other systems'
echo 'testing other systems' >> output.log
Rscript experiment5c.R >> ../../output.log 2>&1
cd ../..
echo 'testing forest packing'
echo 'testing forest packing' >> output.log
./bin/experiment5d >> output.log 2>&1

echo 'printing all results and saving in results directory'
echo 'printing all results and saving in results directory' >> output.log
cd experiments/experiment1
Rscript experiment1.R >> ../../output.log 2>&1
cp scaling.png ../../results/
cp speedUp.png ../../results/
cd ../experiment2
Rscript experiment2.R >> ../../output.log 2>&1
cp stripeAndCore.png ../../results/
cd ../experiment3
Rscript experiment3.R >> ../../output.log 2>&1
cp depthAndStripe.png ../../results/
cd ../experiment4
Rscript experiment4.R >> ../../output.log 2>&1
cp EncodingContributions.png ../../results/
cd ../experiment5
Rscript experiment5MC.R >> ../../output.log 2>&1
cp SystemMC.png ../../results/
