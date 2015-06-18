function plotCost = plotCostForData (data, peak, epsilon, option='b')

	X = data(:,2:end);
	index = data(:,1);
	plotCost = [];

	[a,b] = max(X,'',2);
	if ~exist('epsilon','var') || isempty(epsilon)
		epsilon = sqrt(mean((b - mode(b)).^2));
	end
	if ~exist('peak','var') || isempty(peak)
		peak = mode(b);
	end
	
	for i=1:size(X,1)
		plotCost = [plotCost; cost(X(i,:), peak, epsilon)];
	end

	plot(index, plotCost, 'o', 'color', option);
	plotCost = [index, plotCost];

end