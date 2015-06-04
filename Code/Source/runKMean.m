function [centroids,idx,cost] = runKMean(X,k)
	%Takes in data set and number of clusters and returns the centroids and the mappings
	[m n] = size(X);
	max_iter = 10;
	centroids = zeros(k,n);
	idx = zeros(m,1);
	tmp_centroids = centroids;
	tmp_idx = idx;
	minCost = 100000;
	for i = 1:max_iter
		initial_centroids = initializeCentroids(X,k);
		%Running K Mean 20 times
		[tmp_centroids,tmp_idx,cost] = clusterFormation(X,initial_centroids,20);
		if(cost<minCost)
			minCost = cost;
			centroids = tmp_centroids;
			idx = tmp_idx;
		end
	end
end