function centroids = computeCentroids(X,idx,k)
	%Takes in the data points, the mapping of the ith data item to the cluster number and returns the new centroid values
	%size X = m * n; size centroids = K * n; size idx = m * 1;
	% m = #(training examples); n = #(features); k = #(clusters) 

	[m n] = size(X);
	centroids = zeros(k,n);
	numElem = zeros(k,1);

	for i=1:k
		group = find(idx==i);
		if length(group)>0
			centroids(i,:) = mean(X(group,:));
		end
	end
end


