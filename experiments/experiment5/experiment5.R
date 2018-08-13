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
mydata1 <- mydata1[,c(1,5,4,3)]

mydata <- read.csv(file="experiment5a.csv", header=FALSE)
mydata <- rbind(mydata,mydata1)

mydata$V1 <- as.factor(mydata$V1);
mydata$V2 <- as.factor(mydata$V2);
mydata$V3 <- as.factor(mydata$V3);
mydata$V4 <- mydata$V4/25000;


levels(mydata$V3) <- c("128 Trees", "256 Trees", "512 Trees")

mydata <- data_summary(mydata,varname="V4",groupnames=c("V1","V2","V3"))
leg <- theme(legend.text = element_text(size = 12), legend.title=element_text(size = 12), plot.title = element_text(size = 16,  face="bold"), axis.title.x = element_text(size=15), axis.text.x = element_text(size=15), axis.title.y = element_text(size=15), axis.text.y = element_text(size=15), strip.text.x = element_text(size=15))

p <- ggplot(mydata, aes(x=V2, y=V4, group=V1, color=V1)) + geom_line()
  
p <- p + scale_fill_brewer(palette="Paired") + theme_minimal()
p <- p + guides(fill=guide_legend(title="Technique"))
p <- p + labs(x = "Max Depth of Forest", y =expression(paste("Mean Inference Time per Observation (", mu,"s)")))

p <- p + scale_colour_manual(values=c("red2", "blue2"), name="System" )
p <- p + leg
p <- p + facet_grid(. ~ V3)


png(file="System.png")
print(p)
dev.off()

