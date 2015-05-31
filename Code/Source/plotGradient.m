function plotGradient(data)

grad = findGradient(data);
plot(grad);
hold on;
plot(1:size(grad),2);
plot(1:size(grad),-2);
end