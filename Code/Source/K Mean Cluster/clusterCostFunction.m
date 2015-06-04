function cost = clusterCostFunction(X,centroids,idx)
	%Takes in the data points, the centroids and the mapping of the ith data item to the cluster number
	%size X = m * n; size centroids = K * n; size idx = m * 1;
	% m = #(training examples); n = #(features); k = #(clusters) 
	m = size(X,1);
	n = size(X,2);
	k = size(centroids,1); 
	cost = 0;
	for i = 1:m
		tmp_cost = (( X(i,:)' - ( centroids(idx(i,:),:)' ))')*( X(i,:)' - ( centroids(idx(i,:),:)' ));
		cost = cost + tmp_cost;
	end
	cost = 1/m * cost;
end
