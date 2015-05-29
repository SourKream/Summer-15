cd ../Data;
filelist = readdir (pwd);
for ii = 1:numel(filelist)

  ## skip special files . and ..
  if (regexp (filelist{ii}, "^\\.*"))
    continue;
  endif

  ## load your file
  load(filelist{ii});
endfor
clear ii;
clear filelist;
cd ../Source;