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
          c(mean = median(x[[col]], na.rm=TRUE),
                  sd = sd(x[[col]], na.rm=TRUE))
    }
    data_sum<-ddply(data, groupnames, .fun=summary_func,
                                      varname)
    data_sum <- rename(data_sum, c("mean" = varname))
     return(data_sum)
}


mydata <- read.csv(file="experiment1.csv", header=FALSE)
mydata$V2  <- relevel(mydata$V2, " Bin")
mydata$V2  <- relevel(mydata$V2, " Stat")
mydata$V2  <- relevel(mydata$V2, " DF-")
mydata$V2  <- relevel(mydata$V2, " DF")
mydata$V2  <- relevel(mydata$V2, " BF")
mydata$V2 <- factor(mydata$V2, levels=c(levels(mydata$V2),"ideal"))



mydata$V4 <- as.factor(mydata$V4)
mydata$V2 <- as.factor(mydata$V2)
mydata$V3 <- as.factor(mydata$V3)
mydata$V5 <- as.numeric(mydata$V5)

z <- mydata$V3 == " MNIST"
mydata[z,]$V6 <- mydata[z,]$V6/10000
z <- mydata$V3 == " Higgs"
mydata[z,]$V6 <- mydata[z,]$V6/25000
z <- mydata$V3 == " Allstate"
mydata[z,]$V6 <- mydata[z,]$V6/50000


mydata <- data_summary(mydata,varname="V6",groupnames=c("V2","V3","V4","V5"))

leg <- theme(legend.text = element_text(size = 12), legend.title=element_text(size = 12), plot.title = element_text(size =12 ,  face="bold"), axis.title.x = element_text(size=12), axis.text.x = element_text(size=12), axis.title.y = element_text(size=12), axis.text.y = element_text(size=10, angle=90), strip.text.x = element_text(size=12))

p <- ggplot(mydata, aes(x=V5, y=V6, group=V2, color=V2)) + geom_line(size=1)
  
p <- p + scale_fill_brewer(palette="Paired") + theme_minimal()
p <- p + labs(x = "Number of Threads Used", y =expression(paste("Mean Latency(", mu,"s)")))
p <- p + scale_y_continuous(trans = 'log10')
p <- p + scale_color_manual(values=c(" Bin+"="#b2182b", " Bin"="#ef8a62", " Stat"="#fddbc7", " DF"="#d1e5f0", " DF-"="#67a9cf", " BF"="#2166ac", "ideal"="black"), labels=c("BF","DF","DF-","Stat","Bin","Bin+","Ideal"),  name=NULL, guide=guide_legend(nrow=1))
p <- p + leg
p <- p + facet_grid(. ~ V3)
p <- p + theme(strip.background = element_rect(fill="grey95"))
p <- p + guides(color=FALSE)

ggsave("scaling.png", width=6.5, height=1.75, units="in")




leg <- theme(legend.text = element_text(size = 12), legend.title=element_text(size = 12), plot.title = element_text(size =12 ,  face="bold"), axis.title.x = element_text(size=12), axis.text.x = element_text(size=12), axis.title.y = element_text(size=12), axis.text.y = element_text(size=10), strip.text.x = element_text(size=12))
data_speedUp <- function(data, varnameTimes, varnameCores, groupnames){
      require(plyr)
  summary_func <- function(x, col1, col2){
		oneCoreTime <- x[[col1]][x[[col2]]==1]
           x[[col1]] = oneCoreTime/x[[col1]]
		x
    }
    data_sum<-ddply(data, groupnames, .fun=summary_func, varnameTimes, varnameCores)
     return(data_sum)
}



mydata <- mydata[,1:5]
mydata <- data_speedUp(mydata,varnameTimes="V6",varnameCores="V5",groupnames=c("V2","V3","V4"))

p <- ggplot(mydata, aes(x=V5, y=V6, group=V2, color=V2)) + geom_line(size=1)
  
p <- p + theme_minimal()
p <- p + guides(fill=FALSE)
p <- p + labs(x = "Number of Threads Used", y = "Speed Up")

p <- p + scale_color_manual(values=c(" Bin+"="#b2182b", " Bin"="#ef8a62", " Stat"="#fddbc7", " DF"="#d1e5f0", " DF-"="#67a9cf", " BF"="#2166ac", "ideal"="black"), labels=c("BF","DF","DF-","Stat","Bin","Bin+","Ideal"),  name=NULL, guide=guide_legend(nrow=1))

p <- p + leg
p <- p + facet_grid(. ~ V3, scales="free")
p <- p + geom_abline(intercept = 0 , slope = 1, color="black", size=1)
p <- p + theme(legend.position="bottom",legend.margin=margin(t=-0.30, r=0, b=-0.25, l=0, unit="cm"))
p <- p + theme(strip.text.x=element_blank())
ggsave("speedUp.png", width=6.5, height=1.75, units="in")


