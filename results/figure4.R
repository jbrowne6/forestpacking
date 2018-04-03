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


mydata <- read.csv(file="figure4.csv", header=FALSE)
#mydata$V4 <- mydata$V4/25000*100000

mydata <- data_summary(mydata,varname="V4",groupnames=c("V1","V2"))
mydata$V1 <- as.factor(mydata$V1)
mydata$V2 <- as.character(mydata$V2)


leg <- theme(legend.text = element_text(size = 12), legend.title=element_text(size = 12), plot.title = element_text(size = 16,  face="bold"), plot.subtitle = element_text(size = 12),axis.title.x = element_text(size=15), axis.text.x = element_text(size=15), axis.title.y = element_text(size=15), axis.text.y = element_text(size=15))

p <- ggplot(mydata, aes(x=V1, y=V4, fill=V2)) + 
       geom_bar(stat="identity", position=position_dodge()) +
         geom_errorbar(aes(ymin=V4-sd, ymax=V4+sd), width=.2,
                                        position=position_dodge(.9))
  
p <- p + scale_fill_brewer(palette="Paired") + theme_minimal()
p <- p + guides(fill=guide_legend(title="Intertwined\nDepth"))
#p <- p + labs(title = "Effects of Bin Size and Intertwined Depth\non Prediction Time", subtitle = "2048 Trees and 25000 Higgs Observations")
p <- p + labs(x = "Trees per Bin", y = "Test Set Prediction Time (s)")
p <- p + leg



png(file="figure4.png")
print(p)
dev.off()

