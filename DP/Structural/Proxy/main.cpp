#include <iostream>
#include "VideoProviderProxy.h"
using namespace std;

int main()
{
    cout<<"Proxy"<<endl;

    VideoProviderProxy proxy{};
    
    proxy.GetVideosList();
    proxy.PrintVideoInfo(0);
    proxy.DownloadVideo(0, "Hello");

    return 0;
}