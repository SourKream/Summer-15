function X_Grad = findGradientForMatrix(X)
	%Takes in an m * n matrix 
	X_Grad = [];
	[m n] = size(X);
	for i = 1:m
		X_Grad = [X_Grad ; (findGradient( (X(i,:))' ) )' ];
	end
end