library(ggplot2)
library(plyr)

allstatedepth <- read.csv(file="depthallstate.csv", header=FALSE)
#V2 <- as.factor(1:nrow(mnistdepth))
#mnistdepth <- cbind(mnistdepth, V2)
#higgsdepth <- read.csv(file="depthhiggs.csv", header=FALSE)
#allstatedepth <- read.csv(file="depthallstate.csv", header=FALSE)

hist <- NULL
for(i in 1:nrow(allstatedepth)){
hist <- c(hist, rep(i, allstatedepth[i,]))
}
hist <- data.frame(hist)

leg <- theme(legend.text = element_text(size = 15), legend.title=element_blank(), plot.title = element_text(size = 16,  face="bold"), plot.subtitle = element_text(size = 12),axis.title.x = element_text(size=15), axis.text.x = element_text(size=15), axis.title.y = element_text(size=15), axis.text.y = element_text(size=15))

p <- ggplot(hist, aes(hist)) + geom_histogram(breaks=1:nrow(allstatedepth))

p <- p + labs(title = "Depth of Forest Leaf Nodes -- Allstate", subtitle = "2000 trees, 500000 samples")
p <- p + labs(x = "Depth of Leaf Node", y ="count")


png(file="depthAllstate.png")
print(p)
dev.off()

