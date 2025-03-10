# Exercise 13.1
library(ggplot2)
library(dplyr)
library(car)

# Question (a)
# Load the data
data <- read.csv("vis_type.csv")

# Inspect the data
print(summary(data))

# Convert variables to factors
data$ID <- as.factor(data$ID)
data$visualization_type <- as.factor(data$visualization_type)
data$color <- as.factor(data$color)
data$reaction_time <- as.numeric(data$reaction_time)

# Question (b)
print(levels(data$visualization_type))

summary_visualization_type <- data %>%
    group_by(visualization_type) %>%
    summarise(mean_reaction_time = mean(reaction_time),
              min_reaction_time = min(reaction_time),
              max_reaction_time = max(reaction_time),
              sd_reaction_time = sd(reaction_time))

print(summary_visualization_type)

# Remove extreme outliners
filtered_data <- data %>%
    filter(reaction_time < quantile(reaction_time, 0.95))

# Boxplot
ggplot(filtered_data, aes(x = visualization_type, y = reaction_time, fill = visualization_type)) +
    geom_boxplot() +
    labs(title = "Boxplot of Reaction Time (Without Extreme Outliers)",
         x = "Visualization Type",
         y = "Reaction Time") +
    theme_minimal()

# Question (c)
print(levels(data$color))

summary_color <- data %>%
    group_by(color) %>%
    summarise(mean_reaction_time = mean(reaction_time),
              min_reaction_time = min(reaction_time),
              max_reaction_time = max(reaction_time),
              sd_reaction_time = sd(reaction_time))

print(summary_color)

# Boxplot
ggplot(filtered_data, aes(x = color, y = reaction_time, fill = color)) +
    geom_boxplot() +
    labs(title = "Boxplot of Reaction Time by Color",
         x = "Color",
         y = "Reaction Time") +
    theme_minimal()

# Question (d)
summary_data <- data %>%
    group_by(visualization_type, color) %>%
    summarise(mean_reaction_time = mean(reaction_time),
              sd_reaction_time = sd(reaction_time),
              n = n()) %>%
    mutate(se = sd_reaction_time / sqrt(n),
           lower_ci = mean_reaction_time - qt(0.975, n - 1) * se,
           upper_ci = mean_reaction_time + qt(0.975, n - 1) * se)

print(summary_data)

# 95% CI plot
ggplot(summary_data, aes(x = visualization_type, y = mean_reaction_time, color = color)) +
    geom_point(size = 4, position = position_dodge(width = 0.5)) +
    geom_errorbar(aes(ymin = lower_ci, ymax = upper_ci), 
                  width = 0.2, position = position_dodge(width = 0.5)) +
    labs(title = "95% Confidence Interval of Reaction Time",
         x = "Visualization Type",
         y = "Mean Reaction Time") +
    theme_minimal()

# Exercise 13.2
library(nortest)
library(ARTool)
library(emmeans)

# Question (a)
# Check the independence of the data
chisq.test(table(data$visualization_type, data$color))

# Check the normality of the data
ad.test(data$reaction_time)

# Check the homogeneity of variance
leveneTest(reaction_time ~ visualization_type * color, data = data)

# Question (b)
# Log transformation
data$log_reaction_time <- log(data$reaction_time)

# Square root transformation
data$sqrt_reaction_time <- sqrt(data$reaction_time)

# Remove extreme outliners
Q1 <- quantile(data$reaction_time, 0.25)
Q3 <- quantile(data$reaction_time, 0.75)
IQR <- Q3 - Q1
lower_bound <- Q1 - 1.5 * IQR
upper_bound <- Q3 + 1.5 * IQR
data_filtered <- data[data$reaction_time >= lower_bound & data$reaction_time <= upper_bound, ]

# Question (c)
# Log transformation)
ad.test(data$log_reaction_time)
# Square root transformation)
ad.test(data$sqrt_reaction_time)
# Remove extreme outliners
ad.test(data_filtered$reaction_time)

# Generate the Q-Q plots
par(mfrow = c(2, 2))
qqPlot(data$reaction_time, distribution = "norm", 
       main = "Q-Q Plot of Reaction Time", id = FALSE)
qqPlot(data$log_reaction_time, distribution = "norm", 
       main = "Q-Q Plot of Log Reaction Time", id = FALSE)
qqPlot(data$sqrt_reaction_time, distribution = "norm", 
       main = "Q-Q Plot of Square Root Reaction Time", id = FALSE)
qqPlot(data_filtered$reaction_time, distribution = "norm", 
       main = "Q-Q Plot (Without Extreme Outliers)", id = FALSE)
par(mfrow = c(1,1))

# Question (d)
# ANOVA on the log-transformed data
anova_log <- aov(log_reaction_time ~ visualization_type * color, data = data)
summary(anova_log)

# ART ANOVA on the original data
model_art <- art(reaction_time ~ visualization_type * color, data = data)
anova(model_art)

# Question (e)
# Post-hoc test
posthoc_interaction <- emmeans(
    artlm(model_art, "visualization_type:color"), 
    ~ visualization_type:color, 
    adjust = "bonferroni"
)

df_means <- as.data.frame(posthoc_interaction)

print(df_means)

# 95% CI plot
ggplot(df_means, aes(x = visualization_type, y = emmean, color = color)) +
    geom_point(position = position_dodge(width = 0.5), size = 2) +
    geom_errorbar(aes(ymin = lower.CL, ymax = upper.CL),
                  position = position_dodge(width = 0.5), width = 0.2) +
    labs(x = "Visualization Type",
        y = "Aligned Rank Means (from ART)",
        title = "95% CIs by Visualization Type and Color") +
    theme_bw()