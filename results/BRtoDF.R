# ---
# title: "Test speed-up and scale-up of R-Rerf against xg and ranger"
# author: "James Browne"
# date: "Oct 10 2017"
# output: html_document
# ---
library(ggplot2)
library(plyr)

data_summary <- function(data, varname, groupnames){
      require(plyr)
  summary_func <- function(x, col){
          c(mean = mean(x[[col]], na.rm=TRUE),
                  sd = sd(x[[col]], na.rm=TRUE))
    }
    data_sum<-ddply(data, groupnames, .fun=summary_func,
                                      varname)
    data_sum <- rename(data_sum, c("mean" = varname))
     return(data_sum)
}

intertwinedDepth <- 4

mydataMnist <- read.csv(file="figure5mnist.csv", header=FALSE)
mydataMnist$V4 <- mydataMnist$V4/1000000
mydataMnist$V2 <- "measured"
mydataMnist <- data_summary(mydataMnist,varname="V4",groupnames=c("V1", "V2", "V3"))
mydataMnist$V2 <- as.character(mydataMnist$V2)
mydataMnist$V1 <- as.character(mydataMnist$V1)
mydataMnist$V1 <- "MNIST"

#################
### set this based on the experiment
#################
bias <- .00295
avgLoad0 <- 1
avgLoad1 <- 1.5
avgLoad2 <- 1.5
avgLoad4 <- 1*(.5-bias)+2*(.5+bias)
avgLoad6b <- avgLoad4
avgLoad6t <- 32/18
avgDepth <- 18.32
timePerLoad <- mydataMnist$V4[1]/(avgDepth/avgLoad0)
timePerLoadPage <- mydataMnist$V4[1]/((avgDepth-8)/avgLoad0)

mydataMnist$V2 <- as.factor(mydataMnist$V2)
mydataMnist$V1 <- as.factor(mydataMnist$V1)
mydataMnist$V3 <- as.factor(mydataMnist$V3)

mydataMnist$sd <- as.numeric(mydataMnist$sd)
mydataMnist$V4 <- as.numeric(mydataMnist$V4)


mydataAllstate <- read.csv(file="figure5allstate.csv", header=FALSE)
mydataAllstate$V4 <- mydataAllstate$V4/1000000
mydataAllstate$V2 <- "measured"
mydataAllstate <- data_summary(mydataAllstate, varname="V4",groupnames=c("V1", "V2", "V3"))
mydataAllstate$V2 <- as.character(mydataAllstate$V2)
mydataAllstate$V1 <- as.character(mydataAllstate$V1)
mydataAllstate$V1 <- "Allstate"

#################
### set this based on the experiment
#################
bias <- .000195
avgLoad0 <- 1
avgLoad1 <- 1.5
avgLoad2 <- 1.5
avgLoad4 <- 1*(.5-bias)+2*(.5+bias)
avgLoad6b <- avgLoad4
avgLoad6t <- 32/18
avgDepth <- 14.6
timePerLoad <- mydataAllstate$V4[1]/(avgDepth/avgLoad0)
timePerLoadPage <- mydataAllstate$V4[1]/((avgDepth-8)/avgLoad0)

mydataAllstate$V2 <- as.factor(mydataAllstate$V2)
mydataAllstate$V1 <- as.factor(mydataAllstate$V1)
mydataAllstate$V3 <- as.factor(mydataAllstate$V3)

mydataAllstate$sd <- as.numeric(mydataAllstate$sd)
mydataAllstate$V4 <- as.numeric(mydataAllstate$V4)






mydataHiggs <- read.csv(file="figure5higgs.csv", header=FALSE)
mydataHiggs$V4 <- mydataHiggs$V4/1000000
mydataHiggs$V2 <- "measured"
mydataHiggs <- data_summary(mydataHiggs, varname="V4",groupnames=c("V1", "V2", "V3"))
mydataHiggs$V2 <- as.character(mydataHiggs$V2)
mydataHiggs$V1 <- as.character(mydataHiggs$V1)
mydataHiggs$V1 <- "Higgs"

#################
### set this based on the experiment
#################
bias <- .000775
avgLoad0 <- 1
avgLoad1 <- 1.5
avgLoad2 <- 1.5
avgLoad4 <- 1*(.5-bias)+2*(.5+bias)
avgLoad6b <- avgLoad4
avgLoad6t <- 32/18
avgDepth <- 13.28
timePerLoad <- mydataHiggs$V4[1]/(avgDepth/avgLoad0)


mydataHiggs$V2 <- as.factor(mydataHiggs$V2)
mydataHiggs$V1 <- as.factor(mydataHiggs$V1)
mydataHiggs$V3 <- as.factor(mydataHiggs$V3)

mydataHiggs$sd <- as.numeric(mydataHiggs$sd)
mydataHiggs$V4 <- as.numeric(mydataHiggs$V4)


mydata <- rbind(mydataAllstate, mydataHiggs, mydataMnist)

z <- mydata$V3 == "0" | mydata$V3 == "1" | mydata$V3 == "2"| mydata$V3 == "4"| mydata$V3 == "6"

mydata <- mydata[z,]


mydata$V3 <- revalue(mydata$V3, c("0"="BF", "1"="DF", "2"="DF-", "4"="Stat", "6"="Bin"))


leg <- theme(legend.text = element_text(size = 15), legend.title=element_blank(), plot.title = element_text(size = 16,  face="bold"), plot.subtitle = element_text(size = 12),axis.title.x = element_text(size=15), axis.text.x = element_text(size=15), axis.title.y = element_text(size=15), axis.text.y = element_text(size=15))

p <- ggplot(mydata, aes(x=V1, y=V4, fill=V3)) + 
    geom_bar(stat="identity", position=position_dodge()) +
    geom_errorbar(aes(ymin=V4-sd, ymax=V4+sd), width=.2, position=position_dodge(.9))

    p <- p + scale_fill_brewer(palette="Paired") + theme_minimal() + leg
    p <- p + scale_fill_brewer(palette="Paired") + theme_classic() + leg
    p <- p + guides(fill=guide_legend(title=" "))
    p <- p + theme(legend.position = c(.8,.7))
    p <- p + labs(title = "Layout Run Times")
    p <- p + labs(x = "Dataset", y =expression(paste("Prediction Run Time (s)")))
    #p <- p + labs(x = "Memory Layout", y =expression(paste("Mean Prediction Time per Observation (", mu, "s)")))
#p <- p + facet_grid(. ~ V1)
p <- p + theme(strip.text.x = element_text(size=15, face="bold"))

png(file="BRtoDF.png")
print(p)
dev.off()

