function mincost = debugKMean(X)
	%Testing for K = 1 to 10
	mincost = zeros(10,2);
	for i = 1:10;
		mincost(i,1) = i;
		[dummy1,dummy2,mincost(i,2)] = runKMean(X,i);
		fprintf('Cluster number: %2i Done.....\r',i);
		fflush(stdout);
	end
	fprintf('\n');
plot(mincost(:,1),mincost(:,2),'r');
end