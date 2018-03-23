# ---
# title: "Test speed-up and scale-up of R-Rerf against xg and ranger"
# author: "James Browne"
# date: "Oct 10 2017"
# output: html_document
# ---
library(gridExtra)

table2 <- data.frame(dataset=c("Allstate", "Higgs", "MNIST"), training_size=c(500000,250000,60000), testing_size=c(50000,25000,10000), features=c(33,31,784), avg_number_internal_nodes=c(90020,23964.84,5010), num_trees=c(2048,2048,2048), avg_depth_of_test=c(14.6,13.28,18.32), largest_tree_depth=c(74,65,50), bias=c(.000195,.000755,.00295))


png(file="table2.png")
grid.table(table2)
dev.off()

