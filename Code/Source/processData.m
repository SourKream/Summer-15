function [indexVector,costVector] = processData(numGraphs)
	if ~exist('numGraphs','var') || isempty(numGraphs)
		numGraphs = 372;
	end
	indexVector = zeros(numGraphs,951);
	costVector = zeros(numGraphs,951);
	fid = fopen('GenomeList.txt');
	n = 372;
	genomelist = cell(n,1);
	for i = 1:n
		line = fgets(fid);
		[name,ext] = strtok(line,'.');
		genomelist{i} = strtrim(name);
	end
	for i = 1:numGraphs
		directory = strcat(genomelist{i},'/AutoCorrelate/');
		[index,mCost] = costFunc(directory);
		indexVector(i,:) = index';
		costVector(i,:) = mCost';
	end
end