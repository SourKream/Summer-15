function grad = findGradient(data)

s = size(data);
s = s(1) - 1;
grad = data(2:s) - data(1:s-1);
grad = grad - mean(grad);
grad = grad./std(grad);

end
