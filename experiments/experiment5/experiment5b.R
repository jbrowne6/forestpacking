library(ggplot2)
library(reshape)
library(scales)
library(plyr)
library(randomForest)
library(ranger)
library(xgboost)
library(rerf)

runRerF <- TRUE
runXG <- TRUE
runRF <- FALSE
runRanger <-FALSE 
runFP <- FALSE

runMNIST <- FALSE
runHiggs <- FALSE
runP53 <- FALSE

nTimes <- 10
num_trees <- 512
num.threads <- 64
maxDepth <- 6
output <- data.frame()
output <- c("test", "test", 3,3,3)
fileName <- "predTimes.csv"

numToPredictHolder <- 1000


runDepths <- c(2,4)
nTimes <- 2
num_trees <- c(16,32)
num.threads <- 16




if(file.exists(fileName)) file.remove(fileName)
#################################################################################
#############     MNIST    ######################################################
if(runMNIST){
	#Size of the labels is 1 whereas everything else is 4
	#Open and position the image file
	image_block <- file("../../data/ubyte/train-images-idx3-ubyte", "rb")
	q <- readBin(image_block, integer(), n=1, endian="big")
	num_images <- readBin(image_block, integer(), n=1, endian="big")
	num_col <- readBin(image_block, integer(), n=1, endian="big")
	num_row <- readBin(image_block, integer(), n=1, endian="big")

	#Open and position the label file
	label_block = file("../../data/ubyte/train-labels-idx1-ubyte", "rb")
	q <- readBin(label_block, integer(), n=1, endian="big")
	num_labels <- readBin(label_block, integer(), n=1, endian="big")

	X <- readBin(image_block, integer(), n=num_images*num_col*num_row, size=1, signed=FALSE)
	X <- matrix(X, ncol=num_col*num_row, byrow=TRUE)

	Y <- as.numeric(readBin(label_block, integer(), n=num_labels, size=1, signed=FALSE)+1)

	close(image_block)
	close(label_block)

	image_block <- file("../../data/ubyte/t10k-images-idx3-ubyte", "rb")
	q <- readBin(image_block, integer(), n=1, endian="big")
	num_images <- readBin(image_block, integer(), n=1, endian="big")
	num_col <- readBin(image_block, integer(), n=1, endian="big")
	num_row <- readBin(image_block, integer(), n=1, endian="big")

	#Open and position the label file
	label_block = file("../../data/ubyte/t10k-labels-idx1-ubyte", "rb")
	q <- readBin(label_block, integer(), n=1, endian="big")
	num_labels <- readBin(label_block, integer(), n=1, endian="big")

	Xt <- readBin(image_block, integer(), n=num_images*num_col*num_row, size=1, signed=FALSE)
	Xt <- matrix(Xt, ncol=num_col*num_row, byrow=TRUE)

	Yt <- as.numeric(readBin(label_block, integer(), n=num_labels, size=1, signed=FALSE)+1)

	close(image_block)
	close(label_block)
	image_block <- NULL
	label_block <- NULL

	if(numToPredictHolder < nrow(Xt)){
		numToPredict <- numToPredictHolder
	} else {
		numToPredict <- nrow(Xt)
	}

	if(runRerF){
		gc()

		forestRerFMnist <- RerF(X,Y, trees=num_trees, min.parent=1, max.depth=6, num.cores=num.threads)
		#		save(forestRerFMnist, file="forestRerFMnist.Rdata")
		for (i in 1:nTimes){
			ptm <- proc.time()
			for(m in 1:numToPredict){
				predictions <- Predict(Xt[m,,drop=FALSE], forestRerFMnist, num.cores = 1)
			}
			ptmHold <- (proc.time() - ptm)[3]
			output<- rbind(output, c("RerF", "MNIST", ptmHold))
		}
	}

	if(runFP){
		gc()
		forestFPMnist <-RerF(X,Y,min.parent =1, max.depth=6, trees=num_trees, seed=sample(1:10000,1), mat.options = list(p = ncol(X), d =ceiling(sqrt(ncol(X))), random.matrix = "rf", rho = 1/ncol(X)), num.cores = num.threads) 
		z<- PackForest(X, Y, forestFPMnist)
		forest <- methods::new(forestPredict,"forest.out")
		for (i in 1:nTimes){
			ptm <- proc.time()
			for(m in 1:numToPredict){
				predictions <- forest$pred(Xt[m,,drop=FALSE])
				#predictions <- PackPredict(Xt[m,,drop=FALSE], 1)
			}
			ptmHold <- (proc.time() - ptm)[3]
			output<- rbind(output, c("FP", "MNIST", ptmHold))
		}
	}


	if(runXG){
		num_classes <- length(unique(Y))
		train <- apply(X,2,as.numeric)
		label <- Y-1
		ptm_hold <- NA
		gc()
		forest <- xgboost(data=train, label=label, objective="multi:softmax", nrounds=num_trees,num_class=num_classes, nthread=num.threads, max_depth=6)
		#		save(forestXGBoostMnist, file="forestXGBoostMnist.Rdata")
		testS <- apply(Xt,2,as.numeric)
		testlabel <- Yt-1


		for (i in 1:nTimes){
			ptm <- proc.time()
			for(m in 1:numToPredict){
				#			forest <- xgb.load("xgboost.model")
				pred <- predict(forest, testS[m,,drop=FALSE], ntreelimit=num_trees) 
				#pred <- matrix(pred, ncol=num_classes, byrow=TRUE) 
				#pred_labels <- max.col(pred) - 1
			}
			ptmHold <- (proc.time() - ptm)[3]
			output<-rbind(output, c("XGBoost", "MNIST", ptmHold))
		}
	}

	if(runRF){
		Yrf<-as.factor(as.character(Y))
		gc()
		forestRFMnist <- randomForest(X,Yrf, ntree=num_trees)
		#		save(forestRFMnist, file="forestRFMnist.Rdata")
		for (i in 1:nTimes){
			ptm <- proc.time()
			pred <- predict(forestRFMnist, Xt)
			ptmHold <- (proc.time() - ptm)[3]
			output<-rbind(output, c("RF", "MNIST", ptmHold))
		}
	}


	if(runRanger){
		X <- cbind(X,Y)
		colnames(X) <- as.character(1:ncol(X))

		gc()
		forestRangerMnist <- ranger(dependent.variable.name = as.character(ncol(X)), data = X, num.trees = num_trees, num.threads = num.threads, classification=TRUE)
		#		save(forestRangerMnist, file="forestRangerMnist.Rdata")
		colnames(Xt) <- as.character(1:ncol(Xt))

		for (i in 1:nTimes){
			ptm <- proc.time()
			for(m in 1:numToPredict){
				pred <- predict(forestRangerMnist,Xt[m,,drop=FALSE], num.threads=1)
			}
			ptmHold <- (proc.time() - ptm)[3]
			output<-rbind(output, c("Ranger", "MNIST", ptmHold))
		}
	}
}

#################################################################################
#############     Higgs    ######################################################

if(runHiggs){
	mydata <- read.csv(file="~/gitrepos/experiments/data/higgs/training.csv", header=TRUE, sep=",")
	X <- as.matrix(mydata[,2:31])
	Y <- as.numeric(mydata[,33])
	mydata <- NA
	gc()

	if(numToPredictHolder < (.2*length(Y))){
		numToPredict <- numToPredictHolder
	} else {
		numToPredict <- (.2*length(Y))
	}

	if(runRerF){
		X1 <- sample(1:length(Y[Y==1]), .8 *length(Y[Y==1]), replace=FALSE)
		X2 <- sample(1:length(Y[Y==2]), .8 *length(Y[Y==2]), replace=FALSE)
		Xtr <- rbind(X[Y==1,][X1,],X[Y==2,][X2,])
		Ytr <- c(Y[Y==1][X1], Y[Y==2][X2])
		Xte <- rbind(X[Y==1,][-X1,],X[Y==2,][-X2,])
		Yte <- c(Y[Y==1][-X1], Y[Y==2][-X2])

		gc()

		for(depthToRun in runDepth){
		for(treesToRun in num_trees){
		forestRerFHiggs <- RerF(Xtr,Ytr, trees=treesToRun, max.depth=depthToRun, num.cores=num.threads, seed=sample(1:100000,1))
		#		save(forestRerFHiggs, file="forestRerFHiggs.Rdata")
		for( q in 1:num_trees){
			m <- which(is.na(forestRerFHiggs$trees[[q]]$ClassProb))
			forestRerFHiggs$trees[[q]]$ClassProb[m] <- .5
		}
		for (i in 1:nTimes){
			ptm <- proc.time()
			for(m in 1:numToPredict){
				predictions <- Predict(Xte[m,,drop=FALSE], forestRerFHiggs, num.cores =1)
			}
			ptmHold <- (proc.time() - ptm)[3]
			output<- rbind(output, c("RerF", "Higgs", ptmHold,treesToRun,depthToRun))
		}
		}
		}
	}


	if(runFP){
		gc()
		forestFPHiggs <-RerF(Xtr,Ytr,min.parent =1, max.depth=6, trees=num_trees, seed=sample(1:10000,1), mat.options = list(p = ncol(X), d =ceiling(sqrt(ncol(X))), random.matrix = "rf", rho = 1/ncol(X)), num.cores = num.threads) 
		for( q in 1:num_trees){
			m <- which(is.na(forestFPHiggs$trees[[q]]$ClassProb))
			forestFPHiggs$trees[[q]]$ClassProb[m] <- .5
		}
		z<- PackForest(Xtr, Ytr, forestFPHiggs)
		forest <- methods::new(forestPredict,"forest.out")
		for (i in 1:nTimes){
			ptm <- proc.time()
			for(m in 1:numToPredict){
				#	predictions <- PackPredict(Xte[m,,drop=FALSE], 1)
				predictions <- forest$pred(Xt[m,,drop=FALSE])
			}
			ptmHold <- (proc.time() - ptm)[3]
			output<- rbind(output, c("FP", "Higgs", ptmHold))
		}
	}


	if(runXG){
		num_classes <- length(unique(Y))
		train <- apply(X,2,as.numeric)
		label <- Y-1

		X1 <- sample(1:length(Y[Y==1]), .8 *length(Y[Y==1]), replace=FALSE)
		X2 <- sample(1:length(Y[Y==2]), .8 *length(Y[Y==2]), replace=FALSE)
		Xtr <- rbind(X[Y==1,][X1,],X[Y==2,][X2,])
		Ytr <- c(Y[Y==1][X1], Y[Y==2][X2])
		Xte <- rbind(X[Y==1,][-X1,],X[Y==2,][-X2,])
		Yte <- c(Y[Y==1][-X1], Y[Y==2][-X2])
		train <- apply(Xtr,2,as.numeric)
		label <- Ytr-1
		gc()
for(depthToRun in runDepth){
		for(treesToRun in num_trees){

		forest <- xgboost(data=train, label=label, objective="multi:softmax",nrounds=treesToRun,num_class=num_classes, nthread=num.threads,max_depth=depthToRun)
		warnings()
		#save(forestXGBoostHiggs, file="forestXGBoostHiggs.Rdata")

		testS <- apply(Xte,2,as.numeric)
		testlabel <- Yte-1
		for (i in 1:nTimes){
			ptm <- proc.time()
			for(m in 1:numToPredict){
				#		forest <- xgb.load("xgboost.model")
				pred <- predict(forest, testS[m,,drop=FALSE], ntreelimit=num_trees) 
			}
			#pred <- matrix(pred, ncol=num_classes, byrow=TRUE)
			#pred_labels <- max.col(pred) - 1
			ptmHold <- (proc.time() - ptm)[3]
			output<- rbind(output, c("XGBoost", "Higgs", ptmHold,treesToRun,depthToRun))
		}
		}
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
		forestRFHiggs <- randomForest(Xtr,Yrf, ntree=num_trees)
		#		save(forestRFHiggs, file="forestRFHiggs.Rdata")
		for (i in 1:nTimes){
			ptm <- proc.time()
			pred <- predict(forestRFHiggs, Xte)
			ptmHold <- (proc.time() - ptm)[3]
			output<- rbind(output, c("RF", "Higgs", ptmHold))

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
		forestRangerHiggs <- ranger(dependent.variable.name = as.character(ncol(Xtr)), data = Xtr, num.trees = num_trees, num.threads =num.threads, classification=TRUE)
		#		save(forestRangerHiggs, file="forestRangerHiggs.Rdata")
		colnames(Xte) <- as.character(1:ncol(Xte))
		for (i in 1:nTimes){
			ptm <- proc.time()
			for(m in 1:numToPredict){
				pred <- predict(forestRangerHiggs,Xte[m,,drop=FALSE],num.threads=1)
			}
			ptmHold <- (proc.time() - ptm)[3]
			output<- rbind(output, c("Ranger", "Higgs", ptmHold))

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

