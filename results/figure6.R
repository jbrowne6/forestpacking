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


mydata <- read.csv(file="figure6.csv", header=FALSE)
mydata$V1 <- as.character(mydata$V1)
#normalize based on number of test observations
z <- mydata$V1 == "mnist "
mydata[z,]$V3 <- mydata[z,]$V3/10000*100000
mydata[z,]$V1 <- "MNIST"
z <- mydata$V1 == "higgs "
mydata[z,]$V3 <- mydata[z,]$V3/25000*100000
mydata[z,]$V1 <- "Higgs"
z <- mydata$V1 == "allstate "
mydata[z,]$V3 <- mydata[z,]$V3/50000*100000
mydata[z,]$V1 <- "Allstate"

mydata <- data_summary(mydata,varname="V3",groupnames=c("V1","V2"))
mydata$V1 <- as.factor(mydata$V1)
mydata$V2 <- as.character(mydata$V2)

#just show 0,2,and7
z <- mydata$V2 == "0" | mydata$V2 == "6" | mydata$V2 == "7"
mydata <- mydata[z,]

mydata$V2 <- revalue(mydata$V2, c("0"="BF", "1"="DF", "2"="DF-","4"="Stat", "6"="Bin", "7"="Bin+"))

leg <- theme(legend.text = element_text(size = 15), legend.title=element_blank(), plot.title = element_text(size = 16,  face="bold"), plot.subtitle = element_text(size = 12),axis.title.x = element_text(size=15), axis.text.x = element_text(size=15), axis.title.y = element_text(size=15), axis.text.y = element_text(size=15))

p <- ggplot(mydata, aes(x=V1, y=V3, fill=V2)) + 
       geom_bar(stat="identity", position=position_dodge()) +
         geom_errorbar(aes(ymin=V3-sd, ymax=V3+sd), width=.2,
                                        position=position_dodge(.9))
  
p <- p + scale_fill_brewer(palette="Paired") + theme_classic() + leg
p <- p + guides(fill=guide_legend(title="Layout Scheme"))
    p <- p + theme(legend.position = c(.8,.8))
#p <- p + labs(title = "Memory Layout Prediction Time")
p <- p + labs(x = "Dataset", y =expression(paste("Mean Prediction Time per Observation (", mu, "s)")))




png(file="figure6.png")
print(p)
dev.off()

