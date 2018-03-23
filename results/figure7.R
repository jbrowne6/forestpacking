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


mydata <- read.csv(file="figure7.csv", header=FALSE)
mydata <- data_summary(mydata,varname="V4",groupnames=c("V1","V2"))
mydata$V1 <- as.character(mydata$V1)
mydata$V2 <- as.numeric(mydata$V2)

for(z in unique(mydata$V1)){
base <- mydata[(mydata$V2 == 1)&(mydata$V1==z) ,]$V4
q <- mydata$V1==z
mydata$V5[q] <- base / mydata$V4[q]
}

for(z in unique(mydata$V2)){
mydata <- rbind(c("ideal", z, z, 0,z),mydata )
}

mydata$V2 <- as.numeric(mydata$V2)
mydata$V4 <- as.numeric(mydata$V4)
mydata$V5 <- as.numeric(mydata$V5)

if(max(mydata$V2 >= 16)){
mnistAhmNum8 <- mydata[(mydata$V2 == 8)&(mydata$V1=="mnist ") ,]$V4
mnistAhmNum16 <- mydata[(mydata$V2 == 16)&(mydata$V1=="mnist ") ,]$V4
mnistAhm <- 2-2/(mnistAhmNum8/mnistAhmNum16)

higgsAhmNum8 <- mydata[(mydata$V2 == 8)&(mydata$V1=="higgs ") ,]$V4
higgsAhmNum16 <- mydata[(mydata$V2 == 16)&(mydata$V1=="higgs ") ,]$V4
higgsAhm <- 2-2/(higgsAhmNum8/higgsAhmNum16)

allstateAhmNum8 <- mydata[(mydata$V2 == 8)&(mydata$V1=="allstate ") ,]$V4
allstateAhmNum16 <- mydata[(mydata$V2 == 16)&(mydata$V1=="allstate ") ,]$V4
allstateAhm <- 2-2/(allstateAhmNum8/allstateAhmNum16)

}


mydata$V1 <- as.factor(mydata$V1)


leg <- theme(legend.text = element_text(size = 12), legend.title=element_blank(), plot.title = element_text(size = 16,  face="bold"), plot.subtitle = element_text(size = 12),axis.title.x = element_text(size=12), axis.text.x = element_text(size=12), axis.title.y = element_text(size=12), axis.text.y = element_text(size=12))


p <- ggplot(mydata,aes(x=V2, y=V5, group=V1, color=V1))+geom_line()

#p <- p + labs(title = "Strong Scaling") + leg
p <- p + labs(title = "Strong Scaling") + theme_classic() + leg
p <- p + labs(x = "Number of Cores", y = "Speed Up")
    p <- p + theme(legend.position = c(.8,.6))

p <- p + geom_text(x = 15, y =40 , color="black", size=5, label =paste("Amdahl Number(c=8to16)\nMNIST: ",signif(mnistAhm, digits=2),"\nAllstate: ", signif(allstateAhm, digits=2), "\nHiggs: ", signif(higgsAhm,digits=2)))

p <- p +scale_color_discrete(name="Dataset")

pWidth = 300
pHeight = 300


#png(file="figure7.png", width=pWidth, height=pHeight)
png(file="figure7.png")
print(p)
dev.off()

