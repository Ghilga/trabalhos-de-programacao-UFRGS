data <- read.csv("Table.csv")


plot(x, y, type = 'l')
binaryInsertion = c(2.013, 136.126, 1303.799)
plot(x, binaryInsertion, type = 'l')

xdata <- c(1000,10000, 100000)
Bubble <- data$tempo[1:3]
Insertion <-
insertion <- c(2.158, 158.35, 16053.568)
BinInsertion <- c(2.013, 136.126, 1303.799)
y3 <- c(1, 6, 14, 28, 47, 73, 106 )

# plot the first curve by calling plot() function
# First curve is plotted
plot(xdata, insertion, type="o", col="blue", pch="o", lty=1, ylim=c(0,max(insertion)) )

# Add second curve to the same plot by calling points() and lines()
# Use symbol '*' for points.
points(xdata, y2, col="red", pch="*")
lines(xdata, y2, col="red",lty=2)

# Add Third curve to the same plot by calling points() and lines()
# Use symbol '+' for points.
points(xdata, y3, col="dark red",pch="+")
lines(xdata, y3, col="dark red", lty=3)

