# ---
# title: "Prediction times for three datasets (allstate, higgs, mnist) for each iteration of forestpacking"
# author: "James Browne"
# date: "May 10, 2018"
# output: figure5.png
# ---
library(ggplot2)
library(plyr)

data_summary <- function(data, varname, groupnames){
      require(plyr)
  summary_func <- function(x, col){
          c(mean = median(x[[col]], na.rm=TRUE),
                  sd = sd(x[[col]], na.rm=TRUE))
    }
    data_sum<-ddply(data, groupnames, .fun=summary_func,
                                      varname)
    data_sum <- rename(data_sum, c("mean" = varname))
     return(data_sum)
}


mydata <- read.csv(file="../experiment1/experiment1.csv", header=FALSE)
mydata$V2  <- relevel(mydata$V2, " Bin")
mydata$V2  <- relevel(mydata$V2, " Stat")
mydata$V2  <- relevel(mydata$V2, " DF-")
mydata$V2  <- relevel(mydata$V2, " DF")
mydata$V2  <- relevel(mydata$V2, " BF")

mydata <- mydata[mydata$V5==1,]
mydata <- mydata[mydata$V2!=" Bin+",]

z <- mydata$V3 == " MNIST"
mydata[z,]$V6 <- mydata[z,]$V6/10000
z <- mydata$V3 == " Higgs"
mydata[z,]$V6 <- mydata[z,]$V6/25000
z <- mydata$V3 == " Allstate"
mydata[z,]$V6 <- mydata[z,]$V6/50000



mydata <- data_summary(mydata, varname="V6",groupnames=c("V2", "V3"))

leg <- theme(legend.text = element_text(size = 15), legend.title=element_blank(), plot.title = element_text(size = 16,  face="bold"), plot.subtitle = element_text(size = 12),axis.title.x = element_text(size=15), axis.text.x = element_text(size=15), axis.title.y = element_text(size=15), axis.text.y = element_text(size=15))

p <- ggplot(mydata, aes(x=V3, y=V6, fill=V2)) + 
    geom_bar(stat="identity", position=position_dodge()) +
    geom_errorbar(aes(ymin=V6-sd, ymax=V6+sd), width=.2, position=position_dodge(.9))

    p <- p + scale_fill_brewer(palette="Paired") + theme_minimal() 
    p <- p + guides(fill=guide_legend(title=" "))
    p <- p + theme(legend.position = c(.8,.7))

    p <- p + labs(x = "Memory Encoding", y =expression(paste("Mean Prediction Time per Observation (", mu, "s)")))

p <- p + scale_colour_manual(values=c("cyan2", "purple2", "orange2", "green2", "red2"), name="Encoding" )
#p <- p + scale_colour_manual(values=c("red2", "blue2", "orange2", "green2", "purple2", "cyan2"), name="Encoding" )

#		p <- p + scale_colour_manual(name="Encoding", values=c(' BF'='red2',' DF'='blue2',' DF-'='orange2',' Stat'='green2',' Bin'='purple2',' Bin+'='cyan2'))

p <- p + leg

png(file="EncodingContributions.png")
print(p)
dev.off()

