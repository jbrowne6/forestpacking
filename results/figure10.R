# ---
# title: "Distributed forest packing results"
# author: "James Browne"
# date: "Mar 27 2018"
# output: .png
# notes: I manually copied the run times from the parallel runs and input data.
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
mydataA <- data.frame(nodes=c(1,2,4,8,16), time=c(14.57825,14.62134,14.627525,14.626425,14.489355), dataset="Allstate")
mydataA$time <- as.numeric(mydataA$time)
mydataA$nodes <- as.numeric(mydataA$nodes)
mydataA$time <- (50000*mydataA$nodes)/mydataA$time


mydatahiggs <- data.frame(nodes=c(1,2,4,8,16), time=c(5.48535,5.49962,5.50705,5.4799,5.45799), dataset="Higgs")
mydatahiggs$time <- as.numeric(mydatahiggs$time)
mydatahiggs$nodes <- as.numeric(mydatahiggs$nodes)
mydatahiggs$time <- (25000*mydatahiggs$nodes)/mydatahiggs$time

mydatamnist <- data.frame(nodes=c(1,2,4,8,16), time=c(1.44302,1.44884,1.44537,1.46665,1.42935), dataset="MNIST")
mydatamnist$time <- as.numeric(mydatamnist$time)
mydatamnist$nodes <- as.numeric(mydatamnist$nodes)
mydatamnist$time <- (10000*mydatamnist$nodes)/mydatamnist$time

mydata <- rbind(mydataA,mydatahiggs, mydatamnist)
mydata$time <- as.numeric(mydata$time)
mydata$nodes <- as.numeric(mydata$nodes)
mydata$dataset <- as.factor(mydata$dataset)

maxY <- max(mydata$time)


leg <- theme(legend.text = element_text(size = 15), legend.title=element_blank(), plot.title = element_text(size = 16,  face="bold"), plot.subtitle = element_text(size = 12),axis.title.x = element_text(size=15), axis.text.x = element_text(size=15), axis.title.y = element_text(size=15), axis.text.y = element_text(size=15))

p <- ggplot(mydata,aes(x=nodes, y=time, group=dataset, color=dataset))+geom_line(size=1.5)

p <- p + theme_classic() + leg
p <- p + labs(x = "Number of Nodes", y = "Throughput (observations/s)")
p <- p + theme(legend.position = c(.8,.2))
p <- p +scale_x_continuous(limits=c(1, 16))
p <- p +scale_y_continuous(limits=c(0, maxY))


cols <- c("Higgs"="gold3", "MNIST"="cyan3", "Allstate"="coral3", "Ideal"="olivedrab3" )
p <- p + scale_color_manual(values=cols)

png(file="figure10.png")
print(p)
dev.off()

