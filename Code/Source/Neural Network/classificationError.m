function err = classificationError(X_val,y_val,optimTheta,hidden_layer_size,output_layer_size)
	if ~exist('hidden_layer_size', 'var') || isempty(hidden_layer_size)
    	hidden_layer_size = 25;
	end
	if ~exist('output_layer_size','var') || isempty(output_layer_size)
		output_layer_size = 10;
	end
	p = hypothesis(optimTheta,hidden_layer_size,output_layer_size,X_val);
	err = sum(p==y_val)/size(p,1);
end