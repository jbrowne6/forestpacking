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

#says higgs but actually MNIST
forest <- readRDS("~/gitrepos/experiments/data/ubyte/higgsForest.rds")
forestSize <- as.numeric(object.size(forest)/1000000)
fileSizeRDS <- as.numeric(file.size("~/gitrepos/experiments/data/ubyte/higgsForest.rds")/1000000)
fileSizeCSV <- as.numeric(file.size("~/gitrepos/experiments/data/ubyte/forest.csv")/1000000)

mydata <- data.frame(dataset="MNIST", type="CSV", size=fileSizeCSV,stringsAsFactors=F)
mydata <- rbind(mydata, c("MNIST", "RDS", fileSizeRDS))
mydata <- rbind(mydata, c("MNIST", "Memory", forestSize))

forest <- readRDS("~/gitrepos/experiments/data/higgs/higgsForest.rds")
forestSize <- as.numeric(object.size(forest)/1000000)
fileSizeRDS <- as.numeric(file.size("~/gitrepos/experiments/data/higgs/higgsForest.rds")/1000000)
fileSizeCSV <- as.numeric(file.size("~/gitrepos/experiments/data/higgs/forest.csv")/1000000)

mydata <- rbind(mydata, c("higgs", "CSV", fileSizeCSV))
mydata <- rbind(mydata, c("higgs", "RDS", fileSizeRDS))
mydata <- rbind(mydata, c("higgs", "Memory", forestSize))

mydata$dataset <- as.factor(mydata$dataset)
mydata$type <- as.factor(mydata$type)
mydata$size <- round(as.numeric(mydata$size))


leg <- theme(legend.text = element_text(size = 12), legend.title=element_text(size = 12), plot.title = element_text(size = 16,  face="bold"), plot.subtitle = element_text(size = 12),axis.title.x = element_text(size=15), axis.text.x = element_text(size=15), axis.title.y = element_text(size=15), axis.text.y = element_text(size=15))

p <- ggplot(mydata, aes(x=dataset, y=size, fill=type))
p <- p + geom_bar(stat="identity", position=position_dodge()) 

p <- p + scale_fill_brewer(palette="Paired") + theme_minimal()
p <- p + guides(fill=guide_legend(title="dataset"))
p <- p + labs(title = "Forest Size2 in Memory and Storage", subtitle = "100 Trees")
p <- p + labs(x = "type", y = "size (MB)")
p <- p + leg



png(file="forestSize.png")
print(p)
dev.off()

