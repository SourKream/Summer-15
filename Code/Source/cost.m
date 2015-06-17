function cost = cost(data, peak, epsilon)

	cost = sigmoid(max(abs(findGradient(data)))-2.5);
	[xx, x] = max(data);
	cost = cost * sin(pi * (exp(-((((x-peak)/epsilon)^2)*(log(2)))) - 0.5));

end