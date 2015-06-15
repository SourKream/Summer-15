function grad = findGradient(data)

s = length(data);
grad = data(2:s) - data(1:s-1);
grad = grad - mean(grad);
grad = grad./std(grad);

end