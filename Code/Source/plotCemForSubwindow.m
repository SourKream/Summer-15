function plotCemForSubwindow (data, subwin, option='b')

	% data is raw data from loadDataInMatrix
	% subwin is subwindow number for the CEM to be plotted

	plot(data(find(data(:,1)==subwin)(1),2:end),option);

end