function [indexVector,costVector] = processData(numGraphs)
	if ~exist('numGraphs','var') || isempty(numGraphs)
		numGraphs = 500;
	end
	indexVector = zeros(numGraphs,951);
	costVector = zeros(numGraphs,951);
	fid = fopen('ListOfGenomes.txt');
	n = 500;
	genomelist = cell(n,1);
	for i = 1:n
		line = fgets(fid);
		[name,ext] = strtok(line,'.');
		genomelist{i} = strtrim(name);
	end
	for i = 1:numGraphs
		[index,mCost] = costFunc(genomelist{i});
		indexVector(i,:) = index';
		costVector(i,:) = mCost';
		fprintf('Genome:%3i Processed...\r',i);
		fflush(stdout);
	end
	fprintf('\n');
end