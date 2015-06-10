function [] = plotCluster(X,idx,k)
	% Takes in the data, the cluster mapping and the number of clusters
	colors = [0.25 0.89 0.71; 
			  0.25 0.76 0.89; 
			  0.33 0.20 0.91;
			  0.96 0.79 0.20;
			  0.87 0.39 0.22;
			  0.13 0.37 0.09;
			  0.91 0.24 0.89;
			  0.94 0.35 0.66;
			  1.00 0.96 0.05;
			  0.50 0.50 0.50];
	hold on;
	X_2D = applyPCAForFixedK(X,2);
	for i=1:k
		tmp_2D = X_2D(find(idx==i),:);
		plot(tmp_2D(:,1),tmp_2D(:,2),'o','color',colors(i,:));
	end
	hold off
end

