function output = plotHistForData(data)

	index = data(:,1);
	X = data(:,2:end);
	found = [];
	for i=1:size(X,1)
		f = findOri(X(i,:)');
		found = [found; f];
	end
	[a,b] = max(X,'',2);
	hist(b(find(found==1)));
	output = [index, found, b];

end
