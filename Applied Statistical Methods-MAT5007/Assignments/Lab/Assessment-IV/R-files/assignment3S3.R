#Moeenul Islam
#21MCA0269
#QUESTION3
n=1000
mean=35
sd=5
#(a)
#p(25<=x<40)
p=pnorm(40,mean,sd)-pnorm(25,mean,sd)
p
stnum=p*n
stnum
#(b)
#p(x>40)
p2=pnorm(40,mean,sd,lower.tail = FALSE)
p2
stnum=n*p2
stnum
#(c)
#p(X<20)
p3=pnorm(20,mean,sd)
p3
stnum=n*p3
stnum

