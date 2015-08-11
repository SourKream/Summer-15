function [Distance,index] =  calcDist(X,minPts=100)
	% minPts correponds to minPts
	[m n] = size(X);
	if(m <= 100)
		minPts = m - 1;
	end
	Distance = zeros(m,minPts);
	index = zeros(m,,minPts);
	for i =1:m
		tmp = ones(m,1) * X(i,:);
		tmp = sqrt(sum((tmp - X).*(tmp - X),2));
		locDist = (sort(tmp))(2:(2+minPts-1),:);
		indtmp = [];
		for j = 1:minPts
			indtmp = [indtmp ; find(tmp==locDist(j,:))];
		end
		Distance(i,:) = locDist';
		index(i,:) = indtmp';
	end