function centroids = initializeCentroids(X,K)
	%Randomly initializes the centroids
	centroids = zeros(K, size(X, 2));
	randidx = randperm(size(X, 1));
	centroids = X(randidx(1:K), :);
end