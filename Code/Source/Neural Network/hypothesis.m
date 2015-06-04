function p = hypothesis(Theta,hidden_layer_size,output_layer_size,X)
	%Takes in the optimum Theta, the number of hidden_layers and the number of output_layers 
	%and then computes a pridiction vector p (m * 1) for every training example.

	[m n] = size(X);
	%Converting Theta into Theta1 and Theta2

	Theta1 = reshape( Theta( 1:(hidden_layer_size * (n+1) ) ) ,hidden_layer_size,n+1);
	Theta2 = reshape( Theta( (1 + (hidden_layer_size * (n+1)) ):end ), output_layer_size,hidden_layer_size+1 );
	num_labels = size(Theta2,1);
	p = zeros(X,1);
	h1 = sigmoid([ones(m, 1) X] * Theta1');
	h2 = sigmoid([ones(m, 1) h1] * Theta2');
	[val,p] = max(h2,[],2);
end