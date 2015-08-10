function [cenVector,idxVector,mincost] = debugKMean(X)
	%Testing for K = 1 to MaxNumClusters
	MaxNumClusters = 10;
	[m n] = size(X);
	FeaturesPerElement = n;
	NumElements = m;
	mincost = zeros(MaxNumClusters,1);
	cenVector = zeros(MaxNumClusters,MaxNumClusters*FeaturesPerElement);
	idxVector = zeros(MaxNumClusters,NumElements);
	fprintf('Starting....\n');
	fflush(stdout);
	for i = 1:MaxNumClusters;
		[cen,idx,mincost(i,1)] = runKMean(X,i);
		cenVector(i,1:i*FeaturesPerElement) = cen(:)';
		idxVector(i,:) = idx';
		fprintf('Cluster number: %2i Done.....\r',i);
		fflush(stdout);
	end
	fprintf('\n');
plot(1:MaxNumClusters,mincost(:,1),'r');
end