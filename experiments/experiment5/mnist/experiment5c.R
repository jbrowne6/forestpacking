library(ggplot2)
library(reshape)
library(scales)
library(plyr)
library(xgboost)
library(rerf)

runRerF <- TRUE
runXG <- TRUE
runRF <- FALSE
runRanger <-FALSE 
runFP <- FALSE

runMNIST <-TRUE# FALSE
runHiggs <-FALSE# TRUE
runP53 <- FALSE

nTimes <- 5
num_trees <- 512
num.threads <- 32
maxDepth <- 6
output <- data.frame()
output <- c("test", "test", 3,3,3)
fileName <- "experiment5c.csv"

numToPredictHolder <- 100000


runDepths <- c(6,10,14)
nTimes <- 2
num_trees <- c(128,256,512,1024,2048)
num.threads <- 16


if(file.exists(fileName)) file.remove(fileName)
#################################################################################
#############     MNIST    ######################################################
if(runMNIST){
  #Size of the labels is 1 whereas everything else is 4
  #Open and position the image file
  image_block <- file("../../../../experiments/data/ubyte/train-images-idx3-ubyte", "rb")
  q <- readBin(image_block, integer(), n=1, endian="big")
  num_images <- readBin(image_block, integer(), n=1, endian="big")
  num_col <- readBin(image_block, integer(), n=1, endian="big")
  num_row <- readBin(image_block, integer(), n=1, endian="big")

  #Open and position the label file
  label_block = file("../../../../experiments/data/ubyte/train-labels-idx1-ubyte", "rb")
  q <- readBin(label_block, integer(), n=1, endian="big")
  num_labels <- readBin(label_block, integer(), n=1, endian="big")

  Xtr <- readBin(image_block, integer(), n=num_images*num_col*num_row, size=1, signed=FALSE)
  Xtr <- matrix(Xtr, ncol=num_col*num_row, byrow=TRUE)

  Ytr <- as.numeric(readBin(label_block, integer(), n=num_labels, size=1, signed=FALSE)+1)

  close(image_block)
  close(label_block)

  image_block <- file("../../../../experiments/data/ubyte/t10k-images-idx3-ubyte", "rb")
  q <- readBin(image_block, integer(), n=1, endian="big")
  num_images <- readBin(image_block, integer(), n=1, endian="big")
  num_col <- readBin(image_block, integer(), n=1, endian="big")
  num_row <- readBin(image_block, integer(), n=1, endian="big")

  #Open and position the label file
  label_block = file("../../../../experiments/data/ubyte/t10k-labels-idx1-ubyte", "rb")
  q <- readBin(label_block, integer(), n=1, endian="big")
  num_labels <- readBin(label_block, integer(), n=1, endian="big")

  Xte <- readBin(image_block, integer(), n=num_images*num_col*num_row, size=1, signed=FALSE)
  Xte <- matrix(Xte, ncol=num_col*num_row, byrow=TRUE)

  Yte <- as.numeric(readBin(label_block, integer(), n=num_labels, size=1, signed=FALSE)+1)

  close(image_block)
  close(label_block)
  image_block <- NULL
  label_block <- NULL

    numToPredict <- nrow(Xte)

  if(runRerF){
    gc()
for(depthToRun in runDepths){
      for(treesToRun in num_trees){
				print(paste("running rf ", depthToRun, ", ", treesToRun))
        forestRerFMnist <- RerF(Xtr,Ytr, trees=treesToRun, max.depth=depthToRun, num.cores=num.threads, seed=sample(1:100000,1))
        for (i in 1:nTimes){
					start <- 1
          ptm <- proc.time()
          for(m in 1:2){
					stop <- m*5000	
            predictions <- Predict(Xte[start:stop,,drop=FALSE], forestRerFMnist, num.cores =48)
					start <- stop+1
          }
          ptmHold <- (proc.time() - ptm)[3]
          output<- rbind(output, c("RerF-Batch(MC)", "MNIST", ptmHold,treesToRun,depthToRun))
        }
      }
    }
      }



  if(runXG){
    num_classes <- length(unique(Ytr))
    train <- apply(Xtr,2,as.numeric)
    label <- Ytr-1
    gc()
    for(depthToRun in runDepths){
      for(treesToRun in num_trees){

				print(paste("running xg ", depthToRun, ", ", treesToRun))
        forest <- xgboost(data=train, label=label, objective="multi:softmax",nrounds=treesToRun,num_class=num_classes, nthread=num.threads,max_depth=depthToRun)
        warnings()
        #save(forestXGBoostHiggs, file="forestXGBoostHiggs.Rdata")

        testS <- apply(Xte,2,as.numeric)
        testlabel <- Yte-1
        for (i in 1:nTimes){
					start <- 1
          ptm <- proc.time()
          for(m in 1:2){
					stop <- m*5000	
            #		forest <- xgb.load("xgboost.model")
            pred <- predict(forest, testS[start:stop,,drop=FALSE], ntreelimit=treesToRun) 
					start <- 	stop+1
          }
          #pred <- matrix(pred, ncol=num_classes, byrow=TRUE)
          #pred_labels <- max.col(pred) - 1
          ptmHold <- (proc.time() - ptm)[3]
          output<- rbind(output, c("XGBoost-Batch(MC)", "MNIST", ptmHold,treesToRun,depthToRun))
        }
      }
    }
  }

  
}

#################################################################################
#############     Higgs    ######################################################

if(runHiggs){
  mydata <- read.csv(file="../../res/higgs/training.csv", header=TRUE, sep=",")
  Xtr <- as.matrix(mydata[,2:31])
  Ytr <- as.numeric(mydata[,33])

  testObservations <- sample(1:nrow(Xtr), 25000)

  Xte <- Xtr[testObservations,]
  Yte <- Ytr[testObservations]

  mydata <- NA
  gc()

  numToPredict <- length(Yte)

  if(runRerF){
    gc()

    for(depthToRun in runDepths){
      for(treesToRun in num_trees){
				print(paste("running rf ", depthToRun, ", ", treesToRun))
        forestRerFHiggs <- RerF(Xtr,Ytr, trees=treesToRun, max.depth=depthToRun, num.cores=num.threads, seed=sample(1:100000,1))
        #		save(forestRerFHiggs, file="forestRerFHiggs.Rdata")
        for( q in 1:treesToRun){
          m <- which(is.na(forestRerFHiggs$trees[[q]]$ClassProb))
          forestRerFHiggs$trees[[q]]$ClassProb[m] <- .5
        }
        for (i in 1:nTimes){
					start <- 1
          ptm <- proc.time()
          for(m in 1:5){
					stop <- m*5000	
            predictions <- Predict(Xte[start:stop,,drop=FALSE], forestRerFHiggs, num.cores =48)
					start <- stop+1
          }
          ptmHold <- (proc.time() - ptm)[3]
          output<- rbind(output, c("RerF-Batch(MC)", "Higgs", ptmHold,treesToRun,depthToRun))
        }
      }
    }
  }


  if(runXG){
    num_classes <- length(unique(Ytr))
    train <- apply(Xtr,2,as.numeric)
    label <- Ytr-1
    gc()
    for(depthToRun in runDepths){
      for(treesToRun in num_trees){

				print(paste("running xg ", depthToRun, ", ", treesToRun))
        forest <- xgboost(data=train, label=label, objective="multi:softmax",nrounds=treesToRun,num_class=num_classes, nthread=num.threads,max_depth=depthToRun)
        warnings()
        #save(forestXGBoostHiggs, file="forestXGBoostHiggs.Rdata")

        testS <- apply(Xte,2,as.numeric)
        testlabel <- Yte-1
        for (i in 1:nTimes){
					start <- 1
          ptm <- proc.time()
          for(m in 1:5){
					stop <- m*5000	
            #		forest <- xgb.load("xgboost.model")
            pred <- predict(forest, testS[start:stop,,drop=FALSE], ntreelimit=treesToRun) 
					start <- 	stop+1
          }
          #pred <- matrix(pred, ncol=num_classes, byrow=TRUE)
          #pred_labels <- max.col(pred) - 1
          ptmHold <- (proc.time() - ptm)[3]
          output<- rbind(output, c("XGBoost-Batch(MC)", "Higgs", ptmHold,treesToRun,depthToRun))
        }
      }
    }
  }


}


#################################################################################
#############     p53    ######################################################

if(runP53){
  mydata <- read.csv(file="../../data/p53.csv", header=TRUE, sep=",")
  X <- as.matrix(mydata[,1:(ncol(mydata)-1)])
  Y <- as.numeric(mydata[,ncol(mydata)])
  mydata <- NA
  gc()

  if(numToPredictHolder < (.2*length(Y))){
    numToPredict <- numToPredictHolder
  } else {
    numToPredict <- (.2*length(Y))
  }

  if(runRerF){
    ptm_hold <- NA
    X1 <- sample(1:length(Y[Y==1]), .8 *length(Y[Y==1]), replace=FALSE)
    X2 <- sample(1:length(Y[Y==2]), .8 *length(Y[Y==2]), replace=FALSE)
    Xtr <- rbind(X[Y==1,][X1,],X[Y==2,][X2,])
    Ytr <- c(Y[Y==1][X1], Y[Y==2][X2])
    Xte <- rbind(X[Y==1,][-X1,],X[Y==2,][-X2,])
    Yte <- c(Y[Y==1][-X1], Y[Y==2][-X2])
    gc()
    forestRerFp53 <- RerF(Xtr,Ytr, trees=num_trees, max.depth=6, num.cores=num.threads,seed=sample(1:100000,1))
    #save(forestRerFp53, file="forestRerFp53.Rdata")

    for (i in 1:nTimes){
      ptm <- proc.time()
      for(m in 1:numToPredict){
        predictions <- Predict(Xte[m,,drop=FALSE], forestRerFp53, num.cores = 1)
      }
      ptmHold <- (proc.time() - ptm)[3]
      output<- rbind(output, c("RerF", "p53", ptmHold))

    }
  }

  if(runFP){
    gc()
    forestFPp53 <-RerF(Xtr,Ytr,min.parent =1, max.depth=6, trees=num_trees, seed=sample(1:10000,1), mat.options = list(p = ncol(X), d =ceiling(sqrt(ncol(X))), random.matrix = "rf", rho = 1/ncol(X)), num.cores = num.threads) 
    z<- PackForest(Xtr, Ytr, forestFPp53)
    forest <- methods::new(forestPredict,"forest.out")
    for (i in 1:nTimes){
      ptm <- proc.time()
      for(m in 1:numToPredict){
        #	predictions <- PackPredict(Xte[m,,drop=FALSE], 1)
        predictions <- forest$pred(Xt[m,,drop=FALSE])
      }
      ptmHold <- (proc.time() - ptm)[3]
      output<- rbind(output, c("FP", "p53", ptmHold))
    }
  }

  if(runXG){
    num_classes <- length(unique(Y))

    X1 <- sample(1:length(Y[Y==1]), .8 *length(Y[Y==1]), replace=FALSE)
    X2 <- sample(1:length(Y[Y==2]), .8 *length(Y[Y==2]), replace=FALSE)
    Xtr <- rbind(X[Y==1,][X1,],X[Y==2,][X2,])
    Ytr <- c(Y[Y==1][X1], Y[Y==2][X2])
    Xte <- rbind(X[Y==1,][-X1,],X[Y==2,][-X2,])
    Yte <- c(Y[Y==1][-X1], Y[Y==2][-X2])
    train <- apply(Xtr,2,as.numeric)
    label <- Ytr-1

    gc()
    forest <- xgboost(data=train, label=label, objective="multi:softmax",nrounds=num_trees,max_depth=6, num_class=num_classes, nthread=num.threads)
    #		save(forestXGBoostp53, file="forestXGBoostp53.Rdata")
    testS <- apply(Xte,2,as.numeric)
    testlabel <- Yte-1
    for (i in 1:nTimes){
      ptm <- proc.time()
      for(m in 1:numToPredict){
        #			forest <- xgb.load("xgboost.model")
        pred <- predict(forest, testS[m,,drop=FALSE], ntreelimit=num_trees) 
      }
      #pred <- matrix(pred, ncol=num_classes, byrow=TRUE)
      #pred_labels <- max.col(pred) - 1
      ptmHold <- (proc.time() - ptm)[3]
      output<- rbind(output, c("XGBoost", "p53", ptmHold))
    }
  }


  if(runRF){

    X1 <- sample(1:length(Y[Y==1]), .8 *length(Y[Y==1]), replace=FALSE)
    X2 <- sample(1:length(Y[Y==2]), .8 *length(Y[Y==2]), replace=FALSE)
    Xtr <- rbind(X[Y==1,][X1,],X[Y==2,][X2,])
    Ytr <- c(Y[Y==1][X1], Y[Y==2][X2])
    Xte <- rbind(X[Y==1,][-X1,],X[Y==2,][-X2,])
    Yte <- c(Y[Y==1][-X1], Y[Y==2][-X2])
    Yrf<-as.factor(as.character(Ytr))

    gc()
    forestRFp53 <- randomForest(Xtr,Yrf, ntree=num_trees)
    #		save(forestRFp53, file="forestRFp53.Rdata")
    for (i in 1:nTimes){
      ptm <- proc.time()
      pred <- predict(forestRFp53, Xte)
      ptmHold <- (proc.time() - ptm)[3]
      output<- rbind(output, c("RF", "p53", ptmHold))

    }
  }


  if(runRanger){
    X1 <- sample(1:length(Y[Y==1]), .8 *length(Y[Y==1]), replace=FALSE)
    X2 <- sample(1:length(Y[Y==2]), .8 *length(Y[Y==2]), replace=FALSE)
    Xtr <- rbind(X[Y==1,][X1,],X[Y==2,][X2,])
    Ytr <- c(Y[Y==1][X1], Y[Y==2][X2])
    Xte <- rbind(X[Y==1,][-X1,],X[Y==2,][-X2,])
    Yte <- c(Y[Y==1][-X1], Y[Y==2][-X2])
    Xtr <- cbind(Xtr, Ytr)
    colnames(Xtr) <- as.character(1:ncol(Xtr))
    gc()
    forestRangerp53 <- ranger(dependent.variable.name = as.character(ncol(Xtr)), data = Xtr, num.trees = num_trees, num.threads =num.threads, classification=TRUE)
    #		save(forestRangerp53, file="forestRangerp53.Rdata")
    colnames(Xte) <- as.character(1:ncol(Xte))
    for (i in 1:nTimes){
      ptm <- proc.time()
      for(m in 1:numToPredict){
        pred <- predict(forestRangerp53,Xte[m,,drop=FALSE],num.threads=1)
      }
      ptmHold <- (proc.time() - ptm)[3]
      output<- rbind(output, c("Ranger", "p53", ptmHold))
    }
  }
}

#################################################################################
#############     create output    ##############################################
output <- output[2:nrow(output),]
output <- data.frame(output)
output[,1] <- as.factor(output[,1])
output[,2] <- as.factor(output[,2])
output[,3] <- as.numeric(as.character(output[,3]))
output[,4] <- as.factor(output[,4])
output[,5] <- as.factor(output[,5])

write.table(output, file=fileName, col.names=FALSE, row.names=FALSE, append=FALSE, sep=",")

