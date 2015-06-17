function plotCost = plotCostForData (data, peak, epsilon, option='b')

	X = data(:,2:end);
	index = data(:,1);
	plotCost = [];
	for i=1:size(X,1)
		plotCost = [plotCost; cost(X(i,:), peak, epsilon)];
	end

	plot(index, plotCost, 'o', 'color', option);
	plotCost = [index, plotCost];

end