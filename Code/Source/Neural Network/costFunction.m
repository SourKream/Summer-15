function [J grad] = costFunction(nn_params,hidden_layer_size,num_labels,X,y,lambda)
	% nn_params is the unrolled version of theta1 and theta2
	% X is the training set, without X0
	% input_layer_size is the # features in the Training Set and m is the # examples in the training set.
	% y is the output set. yi belong in {1,2,...output_layer_size}
	% lambda is the regularization parameter.
	input_layer_size = size(X,2);
	Theta1 = reshape(nn_params(1:(hidden_layer_size*(input_layer_size+1))),hidden_layer_size,input_layer_size+1);
	Theta2 = reshape(nn_params((1 + (hidden_layer_size * (input_layer_size + 1))):end), ...
                 num_labels, (hidden_layer_size + 1));
	m = size(X,1);
	J=0;
	Theta1_grad = zeros(size(Theta1));
	Theta2_grad = zeros(size(Theta2));
		for i = 1:m
			%Forward Prop
			a1 = [1;X(i,:)'];
			z2 = Theta1*a1;
			a2 = [1;sigmoid(z2)];
			z3 = Theta2*a2;
			a3 = sigmoid(z3);
			yi = zeros(num_labels,1);
			yi(y(i,:),:) = 1;   
			J = J + ( yi' * log(a3) + (1-yi)' * log(1-a3) );
			%Back Prop
			smallDelta3  = a3 - yi;
			smallDelta2 = (( Theta2' * smallDelta3 ) .* sigmoidGradient([1;z2]))(2:end,:);
			Theta1_grad = Theta1_grad + (smallDelta2 * a1');
			Theta2_grad = Theta2_grad + (smallDelta3 * a2');
		end
			J = (-1/m * J) + (lambda/(2*m)*( sum(sum(Theta1(:,2:end).*Theta1(:,2:end))) + sum(sum(Theta2(:,2:end).*Theta2(:,2:end))) ) ) ;
			Theta1_grad = Theta1_grad ./ m;
			Theta2_grad = Theta2_grad ./ m;
			Theta1_grad = Theta1_grad + (lambda/m .* [zeros( size(Theta1,1), 1) , Theta1(:,2:end)]);
			Theta2_grad = Theta2_grad + (lambda/m .* [zeros( size(Theta2,1), 1) , Theta2(:,2:end)]);
	grad = [Theta1_grad(:) ; Theta2_grad(:)];
end

