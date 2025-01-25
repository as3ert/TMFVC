# Exercise 12.2
library(ggplot2)
library(dplyr)
library(readxl)
library(car)

# Question (c)
# Load the data
data <- read_excel("hand-washing.xlsx")

summary <- data %>%
    group_by(Method) %>%
    summarise(mean=mean(Bacterial_Counts),
              median=median(Bacterial_Counts),
              sd=sd(Bacterial_Counts))

# Print the summary
print(summary)

# Visualize the data
# Box plot
ggplot(data, aes(x=Method, y=Bacterial_Counts, fill=Method)) +
    geom_boxplot() +
    geom_jitter(width=0.2, alpha=0.5) +
    labs(title="Bacterial Counts by Hand-Washing Method (Box Plot)",
         x="Hand-Washing Method",
         y="Bacterial Counts") +
    theme_minimal()

# Violin plot
ggplot(data, aes(x=Method, y=Bacterial_Counts, fill=Method)) +
    geom_violin(trim=FALSE, alpha=0.7) +
    labs(title="Bacterial Counts by Hand-Washing Method (Violin Plot)",
         x="Hand-Washing Method",
         y="Bacterial Counts") +
    theme_minimal()

# Question (d)
# Test Homogeneity of Variance
data$Method <- as.factor(data$Method)
levene_test <- leveneTest(Bacterial_Counts ~ Method, data = data)

print(levene_test)

# Question (e)
# Perform ANOVA
anova_result <- aov(Bacterial_Counts ~ Method, data = data)

# Print the ANOVA table
print(summary(anova_result))

# Question (g)
# Perform Tukey's HSD test
tukey_result <- TukeyHSD(anova_result)

# Print the Tukey's HSD test results
print(tukey_result)

# Convert Tukey HSD results to a data frame
tukey_data <- as.data.frame(tukey_result$Method)

# Add group comparison labels
tukey_data$Comparison <- rownames(tukey_data)

# View the processed data
print(tukey_data)

# Create the plot
ggplot(tukey_data, aes(x=Comparison, y=diff)) +
    geom_point(size=4, color="blue") +
    geom_errorbar(aes(ymin=lwr, ymax=upr), width=0.3,
                  color="darkgray") +
    labs(
        title="Tukey HSD Confidence Intervals",
        x="Group Comparisons",
        y="Mean Difference"
    ) +
    theme_minimal() +
    theme(axis.text.x = element_text(angle = 45, hjust = 1))

