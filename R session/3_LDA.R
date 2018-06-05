# Data Mining 2018-1
# Lab session for R

# 3. LDA

# install and load packages
install.packages("MASS")
install.packages("ggplot2")
library(MASS)
library(ggplot2)
library(scales)

# load dataset
data(lg_40_routers_8_classes.normalized)
data <- lg_40_routers_8_classes.normalized

# partition data into training and test dataset
set.seed(100) # setting seed to generate random number
train_index <- sample(1:nrow(data), 0.7*nrow(data))
train_set <- data[train_index,]
test_set <- data[-train_index,]

# make linear discriminant analysis model
# "." in the formula argument means that we use all the remaining variables in data as covariates
# The prior argument sets the prior probabilities of class membership
# If unspecified, the class proportions for the training set are used
# If present, the probabilities should be specified in the order of the factor levels
LDAModel <- lda(signal ~ ., data, subset=train_index)
                  
# compute the amount of the between-group variance that is explained by each linear discriminant
prop = LDAModel$svd^2/sum(LDAModel$svd^2)

# predict classes of test set
predicted <- predict(object = LDAModel, newdata = test_set)
head(predicted$class) # classification result
head(predicted$posterior, 3) # posterior probabilities
head(predicted$x, 3) # LD projections

LDAModel <- lda(signal ~ ., data)
predicted <- predict(object = LDAModel, newdata = lg_40_routers_8_classes.normalized)
# visualize LDA model                         
dataset = data.frame(species = lg_40_routers_8_classes.normalized[,"signal"], lda = predicted$x)
plt <- ggplot(dataset) + 
  geom_point(aes(lda.LD1, lda.LD2, colour = species, shape = species), size = 2.5) + 
  labs(x = paste("LD1 (", percent(prop[1]), ")", sep=""),
       y = paste("LD2 (", percent(prop[2]), ")", sep="")) +
  scale_shape_manual(values=seq(15,25))

plt
