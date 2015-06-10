function [X_approx] = RecoverData(U_red,X_red)
	%Takes in the U_red matrix and the X_red matrix and computes approximate value of X
	X_approx = X_red * (U_red');
end