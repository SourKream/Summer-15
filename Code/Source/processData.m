function [indexVector,costVector] = processData(numGenomes)

	%	Takes in the number of genomes to be processed. By default acts on 1500 genomes. 

	if ~exist('numGenomes','var') || isempty(numGenomes)
		numGenomes = 1500;
	end

	% Index vector is a vector from 50 ... 1000, signifying the way the data is loaded i.e in the data matrix, data(1,:) corresponds
	% to the cem run with subwinsize = 50 and so forth.

	% Cost vector corresponds to the cost given to each graph. Thus, cost(50,1) corresponds to the cost given to the 50th genome in the
	% GenomeList, run with subwinsize = 50

	
	indexVector = zeros(951,1);
	costVector = zeros(numGenomes,951);
	fid = fopen('ListOfGenomes.txt');
	n = 1500;
	genomelist = cell(n,1);
	for i = 1:n
		line = fgets(fid);
		[name,ext] = strtok(line,'.');
		genomelist{i} = strtrim(name);
	end
	for i = 50:1000
		indexVector(i-49,:) = i;
	end
	for i = 1:numGenomes
		[mCost] = costFunc(genomelist{i});
		costVector(i,:) = mCost';
		fprintf('Genome:%3i Processed...\r',i);
		fflush(stdout);
	end
	fprintf('\n');
end