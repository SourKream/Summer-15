function [plotCost] = costFunc(genome,drawMode,numBins)

	%Takes in a genome name and returns a vector of 951 * 1, with each element being the cost of the corresponding graph.
	
	if ~exist('numBins','var') || isempty(numBins)
		numBins = 20;
	end
	if ~exist('drawMode','var') || isempty(drawMode)
		drawMode = false;
	end

	X = loadDataInMatrix(genome);
	if(drawMode)
		subplot(1,2,2);
	end
	plotCost = plotCostForData(X,drawMode);
	if(drawMode)
		subplot(1,2,1);
		hist(plotCost,numBins);
	end
	
end