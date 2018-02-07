# To install rerf for use with this funciton you have to install rerf into a folder called "rerf"
# command: install.packages("rerf", destdir="rerf")
sink("testRSpeed.txt")
trees <- 2000
dataSetSelect <- "MNIST" #"MNIST" "IRIS"

library(rerf, lib.loc="rerf")

observedError <- FALSE

if(dataSetSelect == "IRIS"){
numberOfTestObservations <- 100
    X <- as.matrix(iris[,1:4])
    Y <- as.numeric(iris[,5])
} else if(dataSetSelect == "MNIST"){

numberOfTestObservations <- 10000
    #Size of the labels is 1 whereas everything else is 4
    #Open and position the image file
    #image_block <- file("../gitRepos/R-RerF/data/ubyte/train-images-idx3-ubyte", "rb")
    image_block <- file("~/dropbox/gitRepos/R-RerF/data/ubyte/train-images-idx3-ubyte", "rb")
    q <- readBin(image_block, integer(), n=1, endian="big")
    num_images <- readBin(image_block, integer(), n=1, endian="big")
    num_col <- readBin(image_block, integer(), n=1, endian="big")
    num_row <- readBin(image_block, integer(), n=1, endian="big")

    #Open and position the label file
    #label_block = file("../gitRepos/R-RerF/data/ubyte/train-labels-idx1-ubyte", "rb")
    label_block = file("~/dropbox/gitRepos/R-RerF/data/ubyte/train-labels-idx1-ubyte", "rb")
    q <- readBin(label_block, integer(), n=1, endian="big")
    num_labels <- readBin(label_block, integer(), n=1, endian="big")

    X <- readBin(image_block, integer(), n=num_images*num_col*num_row, size=1, signed=FALSE)
    X <- matrix(X, ncol=num_col*num_row, byrow=TRUE)

    Y <- as.numeric(readBin(label_block, integer(), n=num_labels, size=1, signed=FALSE)+1)

    close(image_block)
    close(label_block)
    gc()
    if(nrow(X) < 1000){
        print("MNIST not read properly")
        observedError <- TRUE
    }
} else{
    print("no dataset chosen")
    observedError <- TRUE
}

if(!observedError){
    print("growing forest")
    forest <- RerF(X,Y,min.parent =1, max.depth=0, trees=trees, seed=sample(1:10000,1),mat.options = list(p = ncol(X), d =ceiling(sqrt(ncol(X))), random.matrix = "rf", rho = 1/ncol(X)))

    numberOfFeatures <- ncol(X)
    testObservations <- sample(1:nrow(X), numberOfTestObservations, replace=TRUE)
ptm <- proc.time()
#for(z in 1:5000){
#predictions <- Predict(X[testObservations[c(z, z+5000)],], forest, num.cores = 1)
#}
predictions <- Predict(X[testObservations,], forest, num.cores = 1)
ptm_hold <- (proc.time() - ptm)[3]

print(paste("Just tested ", length(predictions), " observations of the ", dataSetSelect, " dataset"))
print(paste("It took ", ptm_hold, " seconds."))
    }else{
    print("forest not created because error observed")
}
sink()
