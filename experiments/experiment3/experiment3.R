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


mydata <- read.csv(file="experiment3.csv", header=FALSE)

z <- mydata$V3 == " MNIST"
mydata[z,]$V7 <- mydata[z,]$V7/10000
z <- mydata$V3 == " Higgs"
mydata[z,]$V7 <- mydata[z,]$V7/25000
z <- mydata$V3 == " Allstate"
mydata[z,]$V7 <- mydata[z,]$V7/50000

mydata$V6 <- as.factor(mydata$V6)
mydata$V8 <- as.factor(mydata$V8)
levels(mydata$V8) <- c("1 Thread", "2 Threads", "4 Threads")

mydata <- data_summary(mydata, varname="V7",groupnames=c("V3", "V5", "V6", "V8"))
#mydata <- mydata[mydata$V6!=6,]

leg <- theme(legend.text = element_text(size = 12), legend.title=element_text(size = 12), plot.title = element_text(size = 16,  face="bold"), axis.title.x = element_text(size=15), axis.text.x = element_text(size=15), axis.title.y = element_text(size=15), axis.text.y = element_text(size=15), strip.text.x = element_text(size=15), strip.text.y = element_text(size=15))

p <- ggplot(mydata, aes(x=V5, y=V7, group=V6, color=V6)) + geom_line()
  


p <- p + scale_fill_brewer(palette="Paired") + theme_minimal()
#p <- p + scale_colour_manual(name="Depth")

p <- p + scale_colour_manual(values=c("0"="#f7f7f7", "1"="#d9d9d9", "2"="#bdbdbd", "3"="#969696", "4"="#636363", "5"="red3", "6"="green3"), name="Depth")
														 
p <- p + labs(x = "Trees Per Bin", y =expression(paste("Mean Prediction Time per Observation (", mu, "s)")))
p <- p + leg
p <- p + scale_x_continuous(trans='log2')
p <- p + scale_y_continuous(trans='log2')
p <- p + facet_grid(V8 ~ V3)

p <- p + theme(axis.text.x = element_text(angle = 45, hjust = 1), axis.text.y = element_text(angle=90, hjust=1))

png(file="depthAndStripe.png")
print(p)
dev.off()

