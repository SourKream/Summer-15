function cost = cost(data, peak, epsilon)
% data is a 1 * winsize matrix
% cost is a float value
%	cost = sigmoid(max(abs(findGradient(data)))-2.5);
	stddev = std(data);
	if (stddev == 0)
		stddev =1;
	end
	data = (data - mean(data))./stddev;
	[maxData, posMaxData] = max(data);

	x = find(data >= max(data) - std(data));
	y = data(x);
	cost = sum(y./(1 + (x-posMaxData).^2)) / length(y);
	cost = 1 - exp(-cost);
	
	cost = cost *  sin(pi * (exp(-((((posMaxData-peak)/epsilon)^2)*(log(2)))) - 0.5));

end

