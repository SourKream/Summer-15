function [optimTheta,cost] = trainNeuralNetwork(X_train,y_train,lambda,hidden_layer_size,output_layer_size,epsilon)
	%Takes in X_train and y_train and produces optimal theta
	
	%Setting default value if not given by user.
	if ~exist('hidden_layer_size', 'var') || isempty(hidden_layer_size)
    	hidden_layer_size = 25;
	end
	if ~exist('output_layer_size','var') || isempty(output_layer_size)
		output_layer_size = 10;
	end
	if ~exist('lambda') || isempty(lambda)
		lambda = 1.0;
	end
	if ~exist('epsilon', 'var') || isempty(epsilon)
    	epsilon = 0.12;
	end
	
	%By Default Debug Mode is off
	dVal = false;

	%randomly initializing the theta values.
	initTheta1 = initializeWeights(hidden_layer_size,size(X_train,2),epsilon);
	initTheta2 = initializeWeights(output_layer_size,hidden_layer_size,epsilon);
	initTheta = [initTheta1(:); initTheta2(:)];

	%setting the maximum iterations to 100
	options = optimset('MaxIter', 100);

	%Using conjugate gradient method along the Polak-Riberie direction and line search, as given in the fmincg function.
	mCostFunction = @(t) costFunction(t, hidden_layer_size, output_layer_size, X_train, y_train,lambda);
	[optimTheta, cost,dummy,Jval] = fmincg(mCostFunction, initTheta, options);
	if (dVal==true)
    	plot(Jval(:,1),Jval(:,2),'r');
 	end	
end