library(ggplot2)
df = read.csv("out.csv",sep=",",header = TRUE, strip.white= TRUE)

ggplot(df, aes(x = N, y = time*1000 , color = Algoritmo)) + 
geom_line() + geom_point()
 
ggsave("output.pdf", width = 7, height = 4)
