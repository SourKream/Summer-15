function cost = clusterCostFunction(X,centroids,idx)
	%Takes in the data points, the centroids and the mapping of the ith data item to the cluster number
	%size X = m * n; size centroids = K * n; size idx = m * 1;
	% m = #(training examples); n = #(features); k = #(clusters) 

	m = size(X,1);
	n = size(X,2);
	k = size(centroids,1); 

	resp_centroids = [];
	for i = 1:m
		resp_centroids = [resp_centroids; centroids(idx(i,:),:)];
	end

	cost = (1/m) * sum(sum((X - resp_centroids).^2));

end
