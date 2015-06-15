function cost = cost(data, peak)

	cost = sigmoid(max(abs(findGradient(data)))-2.5);
	[xx, x] = max(data);
	cost = cost * sin(pi * (exp(-(((x-peak)^2)/(0.5))) - 0.5));

end