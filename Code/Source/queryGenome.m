function resultVector = queryGenome(indexVector)
	numQuery = length(indexVector);
	resultVector = cell(numQuery,1);
	fid = fopen('ListOfDownloadedGenomes.txt');
	n = 372;
	genomelist = cell(n,1);
	for i = 1:n
		line = fgets(fid);
		[name,ext] = strtok(line,'.');
		genomelist{i} = strtrim(name);
	end
	resultVector = genomelist(indexVector,:);
end
