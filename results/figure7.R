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
         # c(mean = median(x[[col]], na.rm=TRUE),
          c(mean = min(x[[col]], na.rm=TRUE),
                  sd = sd(x[[col]], na.rm=TRUE))
    }
    data_sum<-ddply(data, groupnames, .fun=summary_func,
                                      varname)
    data_sum <- rename(data_sum, c("mean" = varname))
     return(data_sum)
}


mydatamnist <- read.csv(file="figure7mnist.csv", header=FALSE)
mydatamnist <- data_summary(mydatamnist,varname="V2",groupnames=c("V1"))
mydatamnist$V4 <- "MNIST"

mydatahiggs <- read.csv(file="figure7higgs.csv", header=FALSE)
mydatahiggs <- data_summary(mydatahiggs,varname="V2",groupnames=c("V1"))
mydatahiggs$V4 <-  "Higgs"

mydataallstate <- read.csv(file="figure7allstate.csv", header=FALSE)
mydataallstate <- data_summary(mydataallstate,varname="V2",groupnames=c("V1"))
mydataallstate$V4 <- "Allstate"

mydata <- rbind(mydatamnist, mydatahiggs, mydataallstate)

mydata <- mydata[mydata$V1 != 64, ]
mydata <- mydata[mydata$V1 != 48, ]

mydata$V1 <- as.numeric(mydata$V1)
mydata$V2 <- as.numeric(mydata$V2)


for(z in unique(mydata$V4)){
base <- mydata[(mydata$V1 == 1)&(mydata$V4==z) ,]$V2
q <- mydata$V4==z
mydata$V5[q] <- base / mydata$V2[q]
}


for(z in unique(mydata$V1)){
mydata <- rbind(c(z,z,z,"Ideal",z),mydata )
}

mydata$V4 <- factor(mydata$V4, levels=c("Ideal","Allstate","Higgs","MNIST"))
mydata$V2 <- as.numeric(mydata$V2)
#mydata$V4 <- as.numeric(mydata$V4)
mydata$V5 <- as.numeric(mydata$V5)
mydata$V1 <- as.numeric(mydata$V1)


if(max(mydata$V1 >= 16)){
mnistAhmNum8 <- mydata[(mydata$V1 == 8)&(mydata$V4=="mnist") ,]$V2
mnistAhmNum16 <- mydata[(mydata$V1 == 16)&(mydata$V4=="mnist") ,]$V2
mnistAhm <- 2-2/(mnistAhmNum8/mnistAhmNum16)

higgsAhmNum8 <- mydata[(mydata$V1 == 8)&(mydata$V4=="higgs") ,]$V2
higgsAhmNum16 <- mydata[(mydata$V1 == 16)&(mydata$V4=="higgs") ,]$V2
higgsAhm <- 2-2/(higgsAhmNum8/higgsAhmNum16)

allstateAhmNum8 <- mydata[(mydata$V1 == 8)&(mydata$V4=="allstate") ,]$V2
allstateAhmNum16 <- mydata[(mydata$V1 == 16)&(mydata$V4=="allstate") ,]$V2
allstateAhm <- 2-2/(allstateAhmNum8/allstateAhmNum16)

}

leg <- theme(legend.text = element_text(size = 15), legend.title=element_blank(), plot.title = element_text(size = 16,  face="bold"), plot.subtitle = element_text(size = 12),axis.title.x = element_text(size=15), axis.text.x = element_text(size=15), axis.title.y = element_text(size=15), axis.text.y = element_text(size=15))


p <- ggplot(mydata,aes(x=V1, y=V5, group=V4, color=V4))+geom_line(size=1.5)


#p <- p + labs(title = "Strong Scaling") 
p <- p + theme_classic() + leg
p <- p + labs(x = "Number of Cores", y = "Speed Up")
    p <- p + theme(legend.position = c(.8,.2))

p <- p + geom_text(x = 15, y =60 , color="black", size=5, label =paste("Amdahl Number(c=8to16)\nMNIST: ",signif(mnistAhm, digits=2),"\nAllstate: ", signif(allstateAhm, digits=2), "\nHiggs: ", signif(higgsAhm,digits=2)))

 cols <- c("Higgs"="gold3", "MNIST"="cyan3", "Allstate"="coral3", "Ideal"="olivedrab3" )
p <- p + scale_color_manual(values=cols)
#p <- p +scale_color_discrete(name="Dataset")

png(file="figure7.png")
print(p)
dev.off()

