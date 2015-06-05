function [] = runLearningCurves(X_train,y_train,X_val,y_val,lambda,hidden_layer_size,output_layer_size,epsilon)
	%{
		TODO: Take random 500 samples of X_Train and corresponding y_train
	%}
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
	mTrainingFunc = @(t1,t2) trainNeuralNetwork(t1,t2,lambda,hidden_layer_size,output_layer_size,epsilon);
	mCostFunc = @(t1,t2,t3) costFunction(t1,hidden_layer_size,output_layer_size,t2,t3,0);
	learningCurves(X_train,y_train,X_val,y_val,mTrainingFunc,mCostFunc);
end