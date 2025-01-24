library(ggplot2)

# check out warpbreaks data
breaks <- warpbreaks$breaks

mean(breaks)
median(breaks)
range(breaks)

ggplot(warpbreaks, aes(x = "", y = breaks)) +
    geom_boxplot(fill = "lightblue") +
    labs(title = "Boxplot of Warpbreaks", y = "Breaks") +
    theme_minimal()

ggplot(warpbreaks, aes(x = breaks)) +
    geom_density(fill = "lightblue", alpha = 0.5) +
    labs(title = "Density Plot of Warpbreaks", x = "Breaks", y = "Density") +
    theme_minimal()

ggplot(warpbreaks , aes(tension, breaks, colour = wool)) + geom_boxplot()

library(dplyr)

warpbreaks %>% 
    group_by(wool, tension) %>% 
    summarize(mean = mean(breaks),
              median = median(breaks),
              IQR = IQR(breaks))

library(rstatix)

warpbreaks %>% 
    group_by(wool, tension) %>% 
    shapiro_test(breaks)

t.test(breaks ~ wool, data = warpbreaks)
