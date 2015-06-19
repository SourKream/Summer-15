function plotCost = plotCostForData (data, drawMode ,peak, epsilon, option='b')
	%TAKES IN RAW DATA MATRIX.
	if ~exist('drawMode','var') || isempty(drawMode)
		drawMode = false;
	end
	X = data(:,2:end);
	index = data(:,1);
	plotCost = [];

	[a,b] = max(X,'',2);
	if ~exist('epsilon','var') || isempty(epsilon)
		epsilon = sqrt(mean((b - mode(b)).^2));
		if(epsilon==0)
			epsilon=1;
		end
	end
	if ~exist('peak','var') || isempty(peak)
		peak = mode(b);
	end
	
	for i=1:size(X,1)
		plotCost = [plotCost; cost(X(i,:), peak, epsilon)];
	end
	if(drawMode)
		plot(index, plotCost, 'o', 'color', option);
	end
	plotCost = [index, plotCost];

end