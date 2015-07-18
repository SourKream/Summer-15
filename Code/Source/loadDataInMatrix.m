function data = loadDataInMatrix(genomeName='')
	
	% data is a 951 * winSize matrix

	if (strcmp(genomeName,'')==0)
		cd ('GenomeData');
	end

	data = load(strcat('Data_',genomeName,'.txt'));

	if (strcmp(genomeName,'')==0)
		cd ..
	end

end