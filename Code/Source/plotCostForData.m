function plotCost = plotCostForData (data, drawMode ,peak, epsilon, option='b')
	%TAKES IN RAW DATA MATRIX.

	%	data is a 951 * winNumber matrix
	%	plotCost is a 951 * 1 matrix, with plotCost(1,:) denoting the cost for subwinsize 50 ,plotCost(2,:) the cost for subwinsize 51 ... 
	%	plotCost(951,:)  the subwinsize 10000 
	
	if ~exist('drawMode','var') || isempty(drawMode)
		drawMode = false;
	end
	
	plotCost = [];

	[a,b] = max(data,'',2);
	if ~exist('epsilon','var') || isempty(epsilon)
		epsilon = sqrt(mean((b - mode(b)).^2));
		if(epsilon==0)
			epsilon=1;
		end
	end
	if ~exist('peak','var') || isempty(peak)
		peak = mode(b);
	end
	
	for i=1:size(data,1)
		plotCost = [plotCost; cost(data(i,:), peak, epsilon)];
	end

	if(drawMode)
		plot([50:1000], plotCost, 'o', 'color', option);
	end
end