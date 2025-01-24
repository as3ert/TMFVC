

# more info on the data here:
# https://stat.ethz.ch/R-manual/R-devel/library/datasets/html/warpbreaks.html 

# check out warpbreaks data
summary(warpbreaks)

# create factor
warpbreaks$wool <- as.factor(warpbreaks$wool)
warpbreaks$tension <- as.factor(warpbreaks$tension)

# check dependent variable
summary(warpbreaks$breaks)


boxplot(warpbreaks$breaks)
density(warpbreaks$breaks)


### per level
# plot
library(ggplot2)

ggplot(warpbreaks, aes(tension, breaks, colour = wool))+
geom_boxplot()


library(dplyr)

warpbreaks %>% 
group_by(wool, tension) %>% 
summarize(mean = mean(breaks),
          median = median(breaks),
          IQR = IQR(breaks))


### normal
library(rstatix)

warpbreaks %>% 
group_by(wool, tension) %>% 
shapiro_test(breaks) 

ggplot(warpbreaks, aes(x=breaks)) + 
geom_histogram()+
facet_grid(tension ~ wool)


### Which wool breaks least? ttest
t.test(breaks~wool, data=warpbreaks)

ggplot(warpbreaks, aes(wool, breaks))+
geom_boxplot()


### Which tension leads to the least breaks? ANOVA
ggplot(warpbreaks, aes(tension, breaks))+
geom_boxplot()

aov_res <- aov(breaks~tension, data=warpbreaks)
summary(aov_res)

TukeyHSD(aov_res)


### Which tension results in the least breaks per wool type? - two-way anova
res_aov2 <- aov(breaks ~ tension * wool, data = warpbreaks)
summary(res_aov2)

TukeyHSD(res_aov2)

#create confidence interval for each comparison
plot(TukeyHSD(res_aov2, conf.level=.95), las = 2)