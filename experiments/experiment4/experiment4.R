# ---
# title: "Prediction times for three datasets (allstate, higgs, mnist) for each iteration of forestpacking"
# author: "James Browne"
# date: "May 10, 2018"
# output: figure5.png
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


mydata <- read.csv(file="../experiment1/experiment1.csv", header=FALSE)
mydata <- rbind(mydata,read.csv(file="../experiment1/experiment1a.csv", header=FALSE))

#mydata$V2  <- relevel(mydata$V2, " Bin")
mydata$V2  <- relevel(mydata$V2, " Stat")
mydata$V2  <- relevel(mydata$V2, " DF-")
mydata$V2  <- relevel(mydata$V2, " DF")
mydata$V2  <- relevel(mydata$V2, " BF")

mydata <- mydata[mydata$V5==1,]
mydata <- mydata[mydata$V2!=" Bin+",]

z <- mydata$V3 == " MNIST"
mydata[z,]$V6 <- mydata[z,]$V6/10000
z <- mydata$V3 == " Higgs"
mydata[z,]$V6 <- mydata[z,]$V6/25000
z <- mydata$V3 == " Allstate"
mydata[z,]$V6 <- mydata[z,]$V6/50000



mydata <- data_summary(mydata, varname="V6",groupnames=c("V2", "V3"))


data_Relative <- function(data, varnameTimes, varnameTechnique, groupnames){
	require(plyr)
	summary_func <- function(x, col1, col2){
		binTime <- x[[col1]][x[[col2]]==" Bin"]
		x[[col1]] = x[[col1]]/binTime
		x
	}
	data_sum<-ddply(data, groupnames, .fun=summary_func, varnameTimes, varnameTechnique)
	#data_sum <- rename(data_sum, c("su" = varnameTimes))
	return(data_sum)
}
mydata <- data_Relative(mydata,varnameTimes="V6",varnameTechnique="V2",groupnames=c("V3"))


leg <- theme(legend.text = element_text(size = 19), legend.title=element_blank(), plot.title = element_text(size = 19,  face="bold"), plot.subtitle = element_text(size = 19),axis.title.x = element_text(size=19), axis.text.x = element_text(size=19), axis.title.y = element_text(size=19), axis.text.y = element_text(size=19))

p <- ggplot(mydata, aes(x=V3, y=V6, fill=V2)) + 
	geom_bar(stat="identity", position=position_dodge())

p <- p +  theme_minimal() 

p <- p + labs(x = NULL, y ="Inference Time Relative to Bin")

p <- p + theme(legend.position="bottom",axis.title.x=element_blank(), axis.text.x=element_blank(), legend.title=element_text(" "))
p <- p + scale_fill_manual(values=c(" Bin+"="#e41a1c", " Bin"="#377eb8", " Stat"="#984ea3", " DF"="#ff7f00", " DF-"="#ffff33", " BF"="#4daf4a"), name=" " )

p <- p + leg

png(file="EncodingContributions.png")
print(p)
dev.off()



mydata <- read.csv(file="../experiment1/experiment1.csv", header=FALSE)
mydata <- rbind(mydata,read.csv(file="../experiment1/experiment1a.csv", header=FALSE))

mydata <- mydata[mydata$V5==1,]
mydata <- mydata[mydata$V2==" Bin+" | mydata$V2==" BF" | mydata$V2==" Bin",]

z <- mydata$V3 == " MNIST"
mydata[z,]$V6 <- mydata[z,]$V6/10000
z <- mydata$V3 == " Higgs"
mydata[z,]$V6 <- mydata[z,]$V6/25000
z <- mydata$V3 == " Allstate"
mydata[z,]$V6 <- mydata[z,]$V6/50000


mydata <- data_summary(mydata, varname="V6",groupnames=c("V2", "V3"))


data_Relative <- function(data, varnameTimes, varnameTechnique, groupnames){
	require(plyr)
	summary_func <- function(x, col1, col2){
		binTime <- x[[col1]][x[[col2]]==" Bin+"]
		x[[col1]] = x[[col1]]/binTime
		x
	}
	data_sum<-ddply(data, groupnames, .fun=summary_func, varnameTimes, varnameTechnique)
	#data_sum <- rename(data_sum, c("su" = varnameTimes))
	return(data_sum)
}
mydata <- data_Relative(mydata,varnameTimes="V6",varnameTechnique="V2",groupnames=c("V3"))

p <- ggplot(mydata, aes(x=V3, y=V6, fill=V2)) + 
	geom_bar(stat="identity", position=position_dodge())

p <- p + theme_minimal() 
p <- p + labs(x = NULL, y ="Inference Time Relative to Bin+")
p <- p + scale_fill_manual(name=" ", values=c(" Bin+"="#e41a1c", " Bin"="#377eb8", " Stat"="#984ea3", " DF"="#ff7f00", " DF-"="#ffff33", " BF"="#4daf4a"))
p <- p + theme(legend.position="bottom", axis.text.x=element_blank(), legend.title=element_text(" "))
p <- p + leg

png(file="AlgorithmContributions.png")
print(p)
dev.off()

