function W = initializeWeights(L_out,L_in,epsilon_init)
	W = (2*epsilon_init*rand(L_out,L_in+1)) - epsilon_init;
end