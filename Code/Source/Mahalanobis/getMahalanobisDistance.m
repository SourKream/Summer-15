function [dis] = getMalanobisDistance(point,mu,Cov_Matrix_inv)
	%Takes in the point whose distance is to be calculated (n* 1) where n is the dimensionality of features
	%Takes in mu, the average of the features, again n * 1
	%Takes in the Cov_Matrix (n*n) Matrix
	%Returns a real valued distance dis

	dis = sqrt( (point - mu)' * Cov_Matrix_inv * (point - mu) );