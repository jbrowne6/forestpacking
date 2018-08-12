library(ggplot2)

fileName <- "predTimes.csv"

mydata <- read.csv(file=fileName, header=FALSE)

leg <- theme(legend.text = element_text(size = 12), legend.title=element_blank(), plot.title = element_text(size = 16,  face="bold"), plot.subtitle = element_text(size = 12),axis.title.x = element_text(size=12), axis.text.x = element_text(size=12), axis.title.y = element_text(size=12), axis.text.y = element_text(size=12))

p <- ggplot(mydata, aes(x=V2, y=V3, group=V1, color=V1)) + geom_point(position="jitter")

p <- p + guides(fill=guide_legend(title="System"))
p <- p + labs(x = "Dataset", y = "Test Prediction Time (s)")
p <- p + scale_y_log10(breaks=c(.01,.1,1,10,100,1000))
p <- p + scale_colour_manual(values=c("red2", "blue2", "green2", "orange2"),
														 name="Encoding",
														 breaks=c("Ranger","XGBoost","RerF","FP"),
														 labels=c("Ranger","XGBoost","RerF","Forest Packing"))
p <- p + leg

png(file="exp0051.png")
print(p)
dev.off()
