# our base image
FROM ubuntu:16.04

RUN apt-get update && apt-get -y install git && apt-get -y install r-base
RUN git clone https://github.com/jbrowne6/forestpacking.git
RUN make -C forestpacking -f Makefile

RUN Rscript -e "install.packages('rerf',repos='http://cran.rstudio.com/')"
RUN Rscript -e "install.packages('ggplot2',repos='http://cran.rstudio.com/')"

RUN mkdir forestpacking/res/allstate
COPY allstate/forest.csv forestpacking/res/allstate/
COPY allstate/testObservations.csv forestpacking/res/allstate/
COPY allstate/traversal.csv forestpacking/res/allstate/

RUN mkdir forestpacking/res/mnist
COPY mnist/forest.csv forestpacking/res/mnist/
COPY mnist/testObservations.csv forestpacking/res/mnist/
COPY mnist/traversal.csv forestpacking/res/mnist/

RUN mkdir forestpacking/res/higgs
COPY higgs/forest.csv forestpacking/res/higgs/
COPY higgs/testObservations.csv forestpacking/res/higgs/
COPY higgs/traversal.csv forestpacking/res/higgs/

COPY runAll.sh forestpacking/experiments/

