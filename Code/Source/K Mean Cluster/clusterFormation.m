function [centroids, idx, cost] = clusterFormation(X,initial_centroids, max_iters)
	%Given a random initialization, runs K means on X. Returns the centroids, the mappings(idx) and the cost associated with this mapping
	%size X = m * n; size centroids = K * n; size idx = m * 1;
	% m = #(training examples); n = #(features); k = #(clusters)
	[m n] = size(X);
	k = size(initial_centroids,1);
	centroids = initial_centroids;
	previous_centroids = centroids;
	idx = zeros(m,1);

	for i = 1:max_iters
		idx = findClosestCentroids(X,centroids);

		centroids = computeCentroids(X,idx,k);
		k = size(centroids,1);
	end
	cost = clusterCostFunction(X,centroids,idx);
end


