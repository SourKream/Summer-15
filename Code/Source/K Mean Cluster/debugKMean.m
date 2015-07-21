function [cenVector,idxVector,mincost] = debugKMean(X)
	%Testing for K = 1 to 10
	mincost = zeros(10,1);
	cenVector = zeros(10,10*951);
	idxVector = zeros(10,1500);
	fprintf('Starting....\n');
	fflush(stdout);
	for i = 1:10;
		[cen,idx,mincost(i,1)] = runKMean(X,i);
		cenVector(i,1:i*951) = cen(:)';
		idxVector(i,:) = idx';
		fprintf('Cluster number: %2i Done.....\r',i);
		fflush(stdout);
	end
	fprintf('\n');
plot(1:10,mincost(:,1),'r');
end