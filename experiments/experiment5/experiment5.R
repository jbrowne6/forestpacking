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
mydata1 <- read.csv(file="experiment5b.csv", header=FALSE)
mydata1$V1 <- as.factor(as.character(mydata1$V1));
mydata1$V5 <- as.factor(as.character(mydata1$V5));
mydata1$V4 <- as.factor(as.character(mydata1$V4));
mydata1$V3 <- as.double(mydata1$V3)/25000.0 *1000000;

mydata1 <- mydata1[,c(1,5,4,3)]
mydata1 <- rename(mydata1,c("V5"="V2","V3"="V4","V4"="V3"))


#mydata2 <- read.csv(file="experiment5c.csv", header=FALSE)
#mydata2$V1 <- as.factor(as.character(mydata2$V1));
#mydata2$V5 <- as.factor(as.character(mydata2$V5));
#mydata2$V4 <- as.factor(as.character(mydata2$V4));
#mydata2$V3 <- as.double(mydata2$V3)/25000.0 *1000000;

#mydata2 <- mydata2[,c(1,5,4,3)]
#mydata2 <- rename(mydata2,c("V5"="V2","V3"="V4","V4"="V3"))


mydata <- read.csv(file="experiment5a.csv", header=FALSE)

mydata$V1 <- as.factor(mydata$V1);
mydata$V2 <- as.factor(mydata$V2);
mydata$V3 <- as.factor(mydata$V3);
mydata$V4 <- mydata$V4/25000;

mydata <- rbind(mydata,mydata1)
#mydata <- rbind(mydata,mydata2)

levels(mydata$V3) <- c("128 Trees", "256 Trees", "512 Trees")

mydata <- data_summary(mydata,varname="V4",groupnames=c("V1","V2","V3"))




data_Relative <- function(data, varnameTimes, varnameTechnique, groupnames){
      require(plyr)
  summary_func <- function(x, col1, col2){
		binTime <- x[[col1]][x[[col2]]=="Bin+"]
           x[[col1]] = x[[col1]]/binTime
		x
    }
    data_sum<-ddply(data, groupnames, .fun=summary_func, varnameTimes, varnameTechnique)
     return(data_sum)
}
mydata <- data_Relative(mydata,varnameTimes="V4",varnameTechnique="V1",groupnames=c("V2","V3"))



leg <- theme(legend.text = element_text(size = 12), legend.title=element_text(size = 12), plot.title = element_text(size = 16,  face="bold"), axis.title.x = element_text(size=15), axis.text.x = element_text(size=15), axis.title.y = element_text(size=15), axis.text.y = element_text(size=15), strip.text.x = element_text(size=15))

p <- ggplot(mydata, aes(x=V2, y=V4, group=V1, color=V1)) + geom_line(size=1)
  
p <- p + theme_minimal()
p <- p + labs(x = "Max Depth of Forest", y = "Inference Time Relative to Bin+")

p <- p + scale_y_continuous(trans='log10')
p <- p + scale_colour_manual(values=c("Bin+"="#e41a1c", " Bin"="#377eb8", " Stat"="#984ea3", " DF"="#ff7f00", " DF-"="#ffff33", "BF"="#4daf4a", "RerF"="#e78ac3", "XGBoost"="#fc8d62" ), name="System" )
p <- p + leg
p <- p + facet_grid(. ~ V3)


png(file="System.png")
print(p)
dev.off()

