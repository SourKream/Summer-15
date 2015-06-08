function data = loadDataInMatrix()

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

endfor

data = [label, data];
end