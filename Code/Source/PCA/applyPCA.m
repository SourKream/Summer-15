function [X_Red,k,U_red] = applyPCA(X,tolerance)
	%tolerance is the fraction of variance retained i.e if tolerance = 0.99, then 99% of the tolerance is retained.
	if ~exist('tolerance','var') || isempty(tolerance)
		tolerance = 0.99;
	end
	[m n] = size(X);
	[X,mu,sigma] = featureNormalize(X);
	Sigma = 1/m * (X'*X);
	[U,S,V] = svd(Sigma);
	tolerance = tolerance * trace(S);
	k = 0;
	for i = 1:n
		if  ( trace(S(1:i,1:i)) >= tolerance)
			k = i;
			break;
		end
	end
	if (k==0)
		X_Red = X;
	else
	 	U_red = U(:,1:k);
	 	X_Red = X * U_red;
	end
end

