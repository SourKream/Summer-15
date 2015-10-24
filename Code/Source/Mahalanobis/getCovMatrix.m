function [Sigma,mu] = getCovMatrix(cluster_data)
	%Takes in the points belonging to a single cluster and returns the Covariance Matrix.
	% cluster_data is a p * n matrix where p is the number of points belonging to a single cluster and n is the dimensionality of the features
	[m,n] = size(cluster_data);
	mu = mean(cluster_data);
	x_norm = bsxfun(@minus, cluster_data,mu);
	Sigma = 1 / m .* (x_norm' * x_norm);
