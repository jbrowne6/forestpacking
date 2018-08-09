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

mydata <- data_summary(mydata,varname="V6",groupnames=c("V2","V3","V4","V5"))
mydata$V4 <- as.factor(mydata$V4)
mydata$V2 <- as.factor(mydata$V2)
mydata$V3 <- as.factor(mydata$V3)
mydata$V5 <- as.numeric(mydata$V5)
mydata$V6 <- mydata$V6/1000000

#sCore <- mydata$V4==" SingleCore"
#mydata <- rbind(mydata, mydata[sCore,])
#mydata$V5[(length(mydata$V5)-sum(sCore)+1):length(mydata$V5)] <- max(mydata$V5)

leg <- theme(legend.text = element_text(size = 12), legend.title=element_text(size = 12), plot.title = element_text(size = 16,  face="bold"), axis.title.x = element_text(size=15), axis.text.x = element_text(size=15), axis.title.y = element_text(size=15), axis.text.y = element_text(size=15))

p <- ggplot(mydata, aes(x=V5, y=V6, group=V2, color=V2)) + geom_line()
  
p <- p + scale_fill_brewer(palette="Paired") + theme_minimal()
p <- p + guides(fill=guide_legend(title="Technique"))
p <- p + labs(x = "Cores Used", y = "Test Set Prediction Time (s)")
p <- p + scale_colour_manual(values=c("red2", "blue2", "orange2", "green2", "purple2", "cyan2"), 
														 name="Encoding", 
														 breaks=c(" BF"," DF"," DF-"," Stat"," Bin"," Bin+"), 
														 labels=c("BF","DF","DF-","Stat","Bin","Bin+"))
p <- p + leg
p <- p + facet_grid(. ~ V3)
#p <- p + facet_grid(V4 ~ V3)


png(file="experiment1.png")
print(p)
dev.off()




data_speedUp <- function(data, varnameTimes, varnameCores, groupnames){
      require(plyr)
  summary_func <- function(x, col1, col2){
		oneCoreTime <- x[[col1]][x[[col2]]==1]
           x[[col1]] = oneCoreTime/x[[col1]]
		x
    }
    data_sum<-ddply(data, groupnames, .fun=summary_func, varnameTimes, varnameCores)
    #data_sum <- rename(data_sum, c("su" = varnameTimes))
     return(data_sum)
}

mydata <- mydata[,1:5]

mydata <- data_speedUp(mydata,varnameTimes="V6",varnameCores="V5",groupnames=c("V2","V3","V4"))

leg <- theme(legend.text = element_text(size = 12), legend.title=element_text(size = 12), plot.title = element_text(size = 16,  face="bold"), axis.title.x = element_text(size=15), axis.text.x = element_text(size=15), axis.title.y = element_text(size=15), axis.text.y = element_text(size=15))

p <- ggplot(mydata, aes(x=V5, y=V6, group=V2, color=V2)) + geom_line()
  
p <- p + scale_fill_brewer(palette="Paired") + theme_minimal()
p <- p + guides(fill=guide_legend(title="Technique"))
p <- p + labs(x = "Cores Used", y = "Speed Up")
p <- p + scale_colour_manual(values=c("red2", "blue2", "orange2", "green2", "purple2", "cyan2"), 
														 name="Encoding", 
														 breaks=c(" BF"," DF"," DF-"," Stat"," Bin"," Bin+"), 
														 labels=c("BF","DF","DF-","Stat","Bin","Bin+"))
p <- p + leg
p <- p + facet_grid(. ~ V3)
#p <- p + facet_grid(V4 ~ V3)


png(file="experiment1SpeedUp.png")
print(p)
dev.off()


