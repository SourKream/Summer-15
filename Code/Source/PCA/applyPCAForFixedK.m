function [X_Red,U_red] = applyPCAForFixedK(X,k)
	%Takes in X and k and does reduction to a R^k subspace
	%Helps in visualization for k=2
	[m n] = size(X);
	[X,mu,sigma] = featureNormalize(X);
	Sigma = 1/m * (X'*X);
	[U,S,V] = svd(Sigma);
	U_red = U(:,1:k);
	X_Red = X * U_red;
end