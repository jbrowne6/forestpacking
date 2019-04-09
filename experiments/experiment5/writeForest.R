
trees <- 2048
nCs <- 32 # this is the number of cores to use
dataSetSelect <- "higgs" #"MNIST" "IRIS" "allstate" "higgs"

wForest <- function(forest, depth, numTrees){

  treeNum <- length(forest$trees)
  treeSizes <- NA
  datWrite <- c(treeNum, ncol(forest$trees[[1]]$ClassProb))

  for(i in 1:treeNum){
    classProbs <- NA
    features <- NA
    for(z in 1:length(forest$trees[[i]]$ClassProb[,1])){
      classProbs[z] <- which.max(forest$trees[[i]]$ClassProb[z,])-1
    }
    features <- forest$trees[[i]]$matAstore[seq(1,length(forest$trees[[i]]$matAstore),2)]-1
    treeSizes[i] <- length(forest$trees[[i]]$treeMap)  
    datWrite <- c(datWrite, treeSizes[i], forest$trees[[i]]$treeMap, forest$trees[[i]]$CutPoint, classProbs, features)
  }

  write.table(datWrite, file =paste("forest",depth,numTrees,".csv", sep="-"),row.names=FALSE, na="",col.names=FALSE, sep=" ", append=FALSE)
}

library(rerf)

observedError <- FALSE

if(dataSetSelect == "IRIS"){
  numberOfTestObservations <- 100
  X <- as.matrix(iris[,1:4])
  Y <- as.numeric(iris[,5])
} else if(dataSetSelect == "MNIST"){

  numberOfTestObservations <- 10000
  #Size of the labels is 1 whereas everything else is 4
  #Open and position the image file
  image_block <- file("~/gitrepos/experiments/data/ubyte/train-images-idx3-ubyte", "rb")

  #image_block <- file("../gitRepos/R-RerF/data/ubyte/train-images-idx3-ubyte", "rb")
  #image_block <- file("~/dropbox/gitRepos/R-RerF/data/ubyte/train-images-idx3-ubyte", "rb")
  q <- readBin(image_block, integer(), n=1, endian="big")
  num_images <- readBin(image_block, integer(), n=1, endian="big")
  num_col <- readBin(image_block, integer(), n=1, endian="big")
  num_row <- readBin(image_block, integer(), n=1, endian="big")

  #Open and position the label file
  label_block <- file("~/gitrepos/experiments/data/ubyte/train-labels-idx1-ubyte", "rb")
  #label_block = file("../gitRepos/R-RerF/data/ubyte/train-labels-idx1-ubyte", "rb")
  q <- readBin(label_block, integer(), n=1, endian="big")
  num_labels <- readBin(label_block, integer(), n=1, endian="big")

  X <- readBin(image_block, integer(), n=num_images*num_col*num_row, size=1, signed=FALSE)
  X <- matrix(X, ncol=num_col*num_row, byrow=TRUE)
  print(nrow(X))
  print(ncol(X))
  Y <- as.numeric(readBin(label_block, integer(), n=num_labels, size=1, signed=FALSE)+1)

  close(image_block)
  close(label_block)
  gc()
  if(nrow(X) < 1000){
    print("MNIST not read properly")
    observedError <- TRUE
  }
} else if(dataSetSelect == "allstate"){
  numberOfTestObservations <- 50000
  obsToUse <- 500000

  print("loading allstate")
  mydata <- read.csv(file="train_set.csv", header=TRUE, sep=",")
  mydata <- as.data.frame(lapply(mydata, as.numeric))
  X <- as.matrix(mydata[,2:34])
  Y <- as.numeric(mydata[,35])
  mydata <- NA
  notZeroes <- Y>0
  numOfZeroesToUse <- obsToUse-sum(notZeroes)

  cuts <- cut(Y[notZeroes], breaks=4,labels=2:5)
  Y[notZeroes] <- as.numeric(cuts)+1
  Y[!notZeroes] <- 1

  print("allstate loaded")
  print("randomly choosing 500000 obs of allstate")
  m <- c(sample(which(!notZeroes), numOfZeroesToUse), which(notZeroes))

  X <- X[m,]
  Y <- Y[m]

  if(nrow(X) != obsToUse ){
    print("allstate not read properly")
    observedError <- TRUE
  }

}else if(dataSetSelect == "higgs"){

  numberOfTestObservations <- 25000
  print("loading higgs")
  mydata <- read.csv(file="../../res/higgs/training.csv", header=TRUE, sep=",")
  X <- as.matrix(mydata[,2:31])
  Y <- as.numeric(mydata[,33])
  mydata <- NA

  print("higgs loaded")
  gc()

  if(nrow(X) != 250000){
    print("higgs not read properly")
    observedError <- TRUE
  }

} else{
  print("no dataset chosen")
  observedError <- TRUE
}

if(!observedError){
runDepth <- c(6,10,14)
runTrees <- c(128,256,512,1024,2048)
  for (depthToRun in runDepth){
    for(treesToRun in runTrees){

  print("growing forest")
  forest <- RerF(X,Y,min.parent =1, max.depth=depthToRun, trees=treesToRun, seed=sample(1:10000,1),mat.options = list(p = ncol(X), d =ceiling(sqrt(ncol(X))), random.matrix = "rf", rho = 1/ncol(X)), num.cores = nCs)

  print("Saving forest to CSV")
  wForest(forest, depthToRun,treesToRun)

      }
  }
}else{
  print("forest not created because error observed")
}
