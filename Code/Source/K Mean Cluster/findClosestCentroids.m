function idx = findClosestCentroids(X, centroids)
	%Takes in the data points, the centroids and the mapping of the ith data item to the cluster number
	%size X = m * n; size centroids = K * n; size idx = m * 1;
	% m = #(training examples); n = #(features); k = #(clusters)
	
	[m n] = size(X);
	k = size(centroids,1);
	idx = zeros(m, 1);

	for i = 1:m
		vec = X(i,:);
		Diff = centroids - ones(k,1) * vec;
		Cost = sum(Diff .^ 2,2);
		[min_cost, idx(i,:)] = min(Cost);
	end

end