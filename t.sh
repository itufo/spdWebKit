g++ Source/test/test.cpp -g -Wall -O0 -lspdwebkit -levent -lcurl -lsqlite3 -ljpeg -lpng -L/usr/local/lib -I/usr/local/include 2>./TODO
cat TODO|wc -l
