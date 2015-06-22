function output = plotHistForData(data,epsilon,flag=false)
	if ~exist('epsilon','var') || isempty(epsilon)
		epsilon = 10;
	end
	index = data(:,1);
	X = data(:,2:end);
	found = [];
	for i=1:size(X,1)
		f = findOri(X(i,:)');
		found = [found; f];
	end
	[a,b] = max(X,'',2);
	if (flag)
		hist(b(find(found==1)),epsilon);
	else
		hist(b,epsilon);
	end
	output = [index, found, b];

end
