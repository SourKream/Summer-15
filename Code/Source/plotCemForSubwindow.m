function plotCemForSubwindow (data, subwin, option='b')

	% data is raw data from loadDataInMatrix
	% subwin is subwindow number for the CEM to be plotted

	plot(data(subwin - 49,:),option);

end