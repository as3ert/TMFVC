# Exercise 12.1
# Load the data
X <- c(3.24, 4.39, 5.24, 3.83, 3.50,
       3.75, 4.06, 3.83, 3.54, 3.20,
       4.28, 3.65, 3.01, 4.69, 3.32)

mu_0 <- 3.5
sigma <- 0.76
n <- length(X)

mean_X <- mean(X)
var_X <- var(X)

# Calculate the z-statistic
z_stat <- (mean_X - mu_0) / (sigma / sqrt(n))

# Calculate the p-value
normal_pdf <- function(x) {
    return(1 / sqrt(2 * pi) * exp(-x^2 / 2))
}

p_value <- integrate(normal_pdf, z_stat, Inf)$value

# Print the results
cat("Mean of X:", mean_X, "\n")
cat("Variance of X:", var_X, "\n")
cat("Z-statistic:", z_stat, "\n")
cat("P-value:", p_value, "\n")
