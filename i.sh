#sudo cp WebKitBuild/Release/lib/libspdwebkit.so.0.1.0 /usr/local/lib/libspdwebkit.so 
sudo cp WebKitBuild/Debug/lib/libspdwebkit.so.0.1.0 /usr/local/lib/libspdwebkit.so 
sudo mkdir /usr/local/include/spdWebKit/
#sudo cp Source/WebKit/spd/WebCoreSupport/DocumentLoaderSpd.h /usr/local/include/spdWebKit
#sudo cp Source/WebKit/spd/WebCoreSupport/spdWebKit.h /usr/local/include/spdWebKit
sudo cp Source/WebKit/spd/WebView.h /usr/local/include/spdWebKit
sudo cp Source/WebKit/spd/spdWebView.h /usr/local/include/spdWebKit
