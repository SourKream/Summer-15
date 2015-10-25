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
	if ~exist('peak','var') || isempty(peak)

		%%%%% Added Later	(To define a small window of subwindowsizes with more genomes as peak instead of single subwindowsize)
		bb = zeros(size(data,2),1);
		for i=1:size(b,1)
			bb(b(i)) = bb(b(i)) + 1;
		end
		[maxb, peak] = max(bb(1:end-2) + bb(2:end-1) + bb(3:end));
		[maxb, ppeak] = max(bb(peak : (peak + 2)));
		peak = peak + ppeak - 1; 
		%%%%%%%%%%%%%%
		
		%peak = mode(b);
	end
	
	if ~exist('epsilon','var') || isempty(epsilon)
		epsilon = sqrt(mean((b - peak).^2));
		if(epsilon==0)
			epsilon=1;
		end
		if (epsilon < 2.5)		% Added later
			epsilon = 2.5;
		end
		epsilon;
	end

	for i=1:size(data,1)
		plotCost = [plotCost; cost(data(i,:), peak, epsilon)];
	end

	if(drawMode)
		plot([50:1000], plotCost, 'o', 'color', option);
	end
end