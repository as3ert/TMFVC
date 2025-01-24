# Exercise 11.1

# a) Read and inspect the data
data <- read.csv("DatasaurusDozen.csv")

str(data)
print(unique(data$dataset))

# b) Compute the mean and standard deviation of the x and y values for each dataset
library(dplyr)

result <- data %>%
    group_by(dataset) %>%
    summarise(
        mean_x = mean(x), 
        sd_x = sd(x), 
        mean_y = mean(y), 
        sd_y = sd(y))

print(result)

# c) Scatter plot of the data
library(ggplot2)

p <- data %>%
    ggplot(aes(x = x, y = y, group = dataset)) +
    geom_point() +
    facet_wrap(~dataset)

# Save the plot
ggsave("scatter_plot.png", plot = p, width = 10, height = 8, dpi = 300)
