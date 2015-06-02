filelist = readdir (pwd);
for ii = 1:numel(filelist)

  ## skip special files . and ..
  if (regexp (filelist{ii}, ".*\.txt$"))
  	load(filelist{ii});
  endif

endfor
clear ii;
clear filelist;