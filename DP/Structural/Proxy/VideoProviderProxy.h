#ifndef _VP_P_H_
#define _VP_P_H_

#include "VideoProvider.h"
#include <memory>

class VideoProviderProxy : public IVideoProvider
{
private:
    std::shared_ptr<IVideoProvider> _service{nullptr};
    //Also we can implement some sort of Catch stuff for our service in this proxy class
public:
    VideoProviderProxy(/* args */)
    :_service(std::make_shared<VideoProvider>())
    {}
    explicit VideoProviderProxy(std::shared_ptr<IVideoProvider> service)
    :_service(service)
    {}
    ~VideoProviderProxy() = default;

    const std::vector<size_t>& GetVideosList() const override
    {
        //We can do anything before the function call, that is the advantage of proxy
        std::cout<<"[P]:GetVideosList -> ";
        if(_service){
            const auto& ret = _service->GetVideosList();
            //We also can do anything after the function call, that is the advantage of proxy
            return ret;
        }
        throw "Error";
    }

    void PrintVideoInfo(size_t id) override
    {
        //We can do anything before the function call, that is the advantage of proxy
        std::cout<<"[P]:PrintVideoInfo -> ";
        if(_service){
            _service->PrintVideoInfo(id);
            //We also can do anything after the function call, that is the advantage of proxy
        }
    }

    void DownloadVideo(size_t id, const std::string& path) override
    {
        //We can do anything before the function call, that is the advantage of proxy
        std::cout<<"[P]:DownloadVideo -> ";
        if(_service){
            _service->DownloadVideo(id, path);
            //We also can do anything after the function call, that is the advantage of proxy
        }
    }

};

#endif