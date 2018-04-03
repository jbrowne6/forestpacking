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


mydatamnist <- read.csv(file="figure7mnist.csv", header=FALSE)
mydatamnist$V2 <- mydatamnist$V2/10000
mydatamnist <- data_summary(mydatamnist,varname="V2",groupnames=c("V1"))
mydatamnist$V4 <- "MNIST"

mydatahiggs <- read.csv(file="figure7higgs.csv", header=FALSE)
mydatahiggs$V2 <- mydatahiggs$V2/25000
mydatahiggs <- data_summary(mydatahiggs,varname="V2",groupnames=c("V1"))
mydatahiggs$V4 <-  "Higgs"

mydataallstate <- read.csv(file="figure7allstate.csv", header=FALSE)
mydataallstate$V2 <- mydataallstate$V2/50000
mydataallstate <- data_summary(mydataallstate,varname="V2",groupnames=c("V1"))
mydataallstate$V4 <- "Allstate"

mydata <- rbind(mydatamnist, mydatahiggs, mydataallstate)
mydata <- mydata[mydata$V1 != 64, ]


mydata$V1 <- as.numeric(mydata$V1)
mydata$V2 <- as.numeric(mydata$V2)
mydata$V4 <- as.factor(mydata$V4)

leg <- theme(legend.text = element_text(size = 15), legend.title=element_blank(), plot.title = element_text(size = 16,  face="bold"), plot.subtitle = element_text(size = 12),axis.title.x = element_text(size=15), axis.text.x = element_text(size=15), axis.title.y = element_text(size=15), axis.text.y = element_text(size=15))

p <- ggplot(mydata,aes(x=V1, y=V2, group=V4, color=V4))+geom_line()

#p <- p + labs(title = "Strong Scaling") 
p <- p + theme_classic() + leg
p <- p + labs(x = "Number of Cores", y = expression(paste("Mean Prediction Time per Observation (", mu, "s)")))
    p <- p + theme(legend.position = c(.8,.7))


p <- p +scale_color_discrete(name="Dataset")

pWidth = 300
pHeight = 300


#png(file="figure7.png", width=pWidth, height=pHeight)
png(file="figure7a.png")
print(p)
dev.off()

