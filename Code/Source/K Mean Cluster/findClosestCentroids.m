function idx = findClosestCentroids(X, centroids)
	%Takes in the data points, the centroids and the mapping of the ith data item to the cluster number
	%size X = m * n; size centroids = K * n; size idx = m * 1;
	% m = #(training examples); n = #(features); k = #(clusters)
	
	[m n] = size(X);
	k = size(centroids,1);
	idx = zeros(m, 1);

	for i = 1:m
		minimum_ind = 1;
		minimum_value = (centroids(1,:)' - X(i,:)')'*(centroids(1,:)' - X(i,:)');
		for j = 2:k
		if((centroids(j,:)' - X(i,:)')'*(centroids(j,:)' - X(i,:)') < minimum_value) 
			minimum_value = (centroids(j,:)' - X(i,:)')'*(centroids(j,:)' - X(i,:)');
			minimum_ind = j;
		end
	end
	idx(i,:) = minimum_ind;
end

end