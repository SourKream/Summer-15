function centroids = computeCentroids(X,idx,k)
	%Takes in the data points, the mapping of the ith data item to the cluster number and returns the new centroid values
	%size X = m * n; size centroids = K * n; size idx = m * 1;
	% m = #(training examples); n = #(features); k = #(clusters) 
	[m n] = size(X);
	centroids = zeros(k,n);
	numElem = zeros(K,1);
	for i = 1:m
		centroids(idx(i,:),:) = centroids(idx(i,:),:) + X(i,:);
		numElem(idx(i,:),:) = numElem(idx(i,:),:) + 1;
	end
	%removing zero elements
	idx = (numElem(:,1) != 0);
	numElem = numElem(idx,:);
	centroids = centroids(idx,:);
	centroids = centroids ./ numElem;
end