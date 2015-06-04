function found = findOri(Data)

grad = findGradient(Data);
N = size(grad)(1);
M = size(find(abs(grad)>2.5))(1);

if M>=1&&M<0.15*N
found = true;
else
found = false;
end

end