function data = loadDataInMatrix(genomeName='')
if (strcmp(genomeName,'')==0)
	genomeName=strcat(genomeName,'/AutoCorrelate/');
	cd (genomeName);
end
filelist = readdir (pwd);
data = [];
label = [];
for ii = 1:numel(filelist)

  if (regexp (filelist{ii}, ".*\.txt$"))
  	record = load(filelist{ii});
  	A = filelist{ii};
  	label = [label; str2num(A(findstr(A,'_')(end)+1:findstr(A,'.txt')-1))];
  	data = [data; record'];
  endif

end

data = [label, data];
if (strcmp(genomeName,'')==0)
	cd ../..
end
end