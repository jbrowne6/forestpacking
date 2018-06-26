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


mydata <- read.csv(file="experiment1.csv", header=FALSE)

mydata <- data_summary(mydata,varname="V6",groupnames=c("V2","V4","V5"))
mydata$V4 <- as.factor(mydata$V4)
mydata$V2 <- as.factor(mydata$V2)
mydata$V5 <- as.numeric(mydata$V5)
mydata$V6 <- mydata$V6/1000000

sCore <- mydata$V4==" SingleCore"
mydata <- rbind(mydata, mydata[sCore,])
mydata$V5[(length(mydata$V5)-sum(sCore)):length(mydata$V5)] <- 64

leg <- theme(legend.text = element_text(size = 12), legend.title=element_text(size = 12), plot.title = element_text(size = 16,  face="bold"), axis.title.x = element_text(size=15), axis.text.x = element_text(size=15), axis.title.y = element_text(size=15), axis.text.y = element_text(size=15))

p <- ggplot(mydata, aes(x=V5, y=V6, group=V2, color=V2)) + geom_line()
  
p <- p + scale_fill_brewer(palette="Paired") + theme_minimal()
p <- p + guides(fill=guide_legend(title="Technique"))
p <- p + labs(x = "Cores Used", y = "Test Set Prediction Time (s)")
p <- p + leg
p <- p + facet_grid(V4 ~ .)


png(file="experiment1.png")
print(p)
dev.off()

