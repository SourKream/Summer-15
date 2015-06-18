function [index,plotCost] = costFunc(src,drawMode,numBins)
	if ~exist('numBins','var') || isempty(numBins)
		numBins = 20;
	end
	if ~exist('drawMode','var') || isempty(drawMode)
		drawMode = false;
	end
	cd (src);
	X = loadDataInMatrix();
	if(drawMode)
		subplot(1,2,2);
	end
	p = plotCostForData(X);
	index = p(:,1);
	plotCost = p(:,2);
	if(drawMode)
		subplot(1,2,1);
		hist(plotCost,numBins);
	end
	cd ../..
	
end