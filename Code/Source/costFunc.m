function [index,plotCost] = costFunc(genome,drawMode,numBins)
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
	p = plotCostForData(X,drawMode);
	index = p(:,1);
	plotCost = p(:,2);
	if(drawMode)
		subplot(1,2,1);
		hist(plotCost,numBins);
	end
	
end