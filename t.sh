g++ Source/test/test.cpp  -lspdwebkit -lcurl -lsqlite3 -ljpeg -lpng 2>./TODO
cat TODO|wc -l
