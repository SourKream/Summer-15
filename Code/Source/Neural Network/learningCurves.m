function [] = learningCurves(X_train,y_train,X_val,y_val,trainingFunc,costFunc)
	%Take a  subset of random 500 samples or less from the training set for plotting the Learning Curves.

	[m n] = size(X_train);
	J_train_error = zeros(m,2);
	J_val_error = zeros(m,2);
	for i = 1:m
		J_train_error(i,1) = i;
		J_val_error(i,1) = i;
		[theta] = trainingFunc(X_train(1:i,:),y_train(1:i,:));
		J_train_error(i,2) = costFunc(theta,X_train(1:i),y_train);
		J_val_error(i,2) = costFunc(theta,X_val,y_val);
	end
	
	plot(J_train_error(:,1),J_train_error(:,2),'r');
	hold on 
	plot(J_val_error(:,1), J_val_error(:,2),'b');
end
