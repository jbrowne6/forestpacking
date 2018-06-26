library(ggplot2)
library(plyr)

higgsdepth <- read.csv(file="depthhiggs.csv", header=FALSE)

hist <- NULL
for(i in 1:nrow(higgsdepth)){
hist <- c(hist, rep(i, higgsdepth[i,]))
}
hist <- data.frame(hist)

leg <- theme(legend.text = element_text(size = 15), legend.title=element_blank(), plot.title = element_text(size = 16,  face="bold"), plot.subtitle = element_text(size = 12),axis.title.x = element_text(size=15), axis.text.x = element_text(size=15), axis.title.y = element_text(size=15), axis.text.y = element_text(size=15))

p <- ggplot(hist, aes(hist)) + geom_histogram(breaks=1:nrow(higgsdepth))

p <- p + labs(title = "Depth of Forest Leaf Nodes -- higgs", subtitle = "2000 trees, 250000 samples")
p <- p + labs(x = "Depth of Leaf Node", y ="count")


png(file="depthHiggs.png")
print(p)
dev.off()

