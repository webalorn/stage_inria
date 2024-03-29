pdf('_results/plots.pdf-1.pdf', height=6.000000, width=6.000000)
cols <- as.vector(c('#000000','#FF0000','#0000FF','#00FF00'))
pchs <- as.vector(c(4,19,17,15,25,0,2,5,6,3,1,7,8,9,10,24,23,18))
data0 <- matrix(c(1000.000000,10000.000000,100000.000000,200000.000000,500000.000000,1000000.000000,0.000592,0.005311,0.056483,0.109723,0.235258,0.514093),ncol=2)
data1 <- matrix(c(1000.000000,10000.000000,100000.000000,200000.000000,500000.000000,1000000.000000,0.011414,1.007353,NA,NA,NA,NA),ncol=2)
data2 <- matrix(c(1000.000000,10000.000000,100000.000000,200000.000000,500000.000000,1000000.000000,0.001124,0.017467,0.193951,0.432190,1.036300,2.188950),ncol=2)
data3 <- matrix(c(1000.000000,10000.000000,100000.000000,200000.000000,500000.000000,1000000.000000,0.000008,0.000064,0.000557,0.001226,0.004579,0.009389),ncol=2)
corner1 <- matrix(c(NA,NA),ncol=2)
corner2 <- matrix(c(NA,NA),ncol=2)
plot(rbind(data0,data1,data2,data3,corner1,corner2), type='n', xlab='n', ylab='exectime', log='x')
legend('topright', c('algo=optim2','algo=brutal','algo=classical','algo=projections'), col=cols, pch=pchs)
points(data0,col=cols[1],pch=pchs[1],type='l')
points(data0,col=cols[1],pch=pchs[1],type='p')
points(data1,col=cols[2],pch=pchs[2],type='l')
points(data1,col=cols[2],pch=pchs[2],type='p')
points(data2,col=cols[3],pch=pchs[3],type='l')
points(data2,col=cols[3],pch=pchs[3],type='p')
points(data3,col=cols[4],pch=pchs[4],type='l')
points(data3,col=cols[4],pch=pchs[4],type='p')
title(main='', col.main='black', font.main=1, cex.main=1)
dev.off()