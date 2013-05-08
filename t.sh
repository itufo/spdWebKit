g++ -o cmd Source/test/test.cpp -g -Wall -O0 -lspdwebkit -lcurl -lsqlite3 -ljpeg -lpng -L/usr/local/lib -I/usr/local/include 2>./TODO
g++ -o spdWebKit Source/test/spdWebKit.cpp -g -Wall -O0 -lspdwebkit -lcurl -lsqlite3 -ljpeg -lpng -L/usr/local/lib -I/usr/local/include 2>./TODO

cat TODO|wc -l


g++ -o spdWebKitd Source/test/spdWebKitd.cpp -g -Wall -O0 -lspider -lspdwebkit -lcurl -lsqlite3 -ljpeg -lpng -L/usr/local/lib -I/usr/local/include 2>./TODO

cat TODO|wc -l
