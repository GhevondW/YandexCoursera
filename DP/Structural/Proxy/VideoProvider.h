#ifndef _VIDEO_PROVIDER_H_
#define _VIDEO_PROVIDER_H_

#include <utility>
#include <vector>
#include <iostream>

struct IVideoProvider
{
    IVideoProvider() = default;
    virtual ~IVideoProvider() = default;

    virtual const std::vector<size_t>& GetVideosList() const = 0;
    virtual void PrintVideoInfo(size_t id) = 0;
    virtual void DownloadVideo(size_t id, const std::string& path) = 0;
};

class VideoProvider: public IVideoProvider
{
private:
    std::vector<size_t> _data{};
public:
    VideoProvider(/* args */) = default;
    ~VideoProvider() = default;

    const std::vector<size_t>& GetVideosList() const override
    {
        std::cout<<"[VP] GetVideosList"<<std::endl;
        return _data;
    }

    void PrintVideoInfo(size_t id) override
    {
        std::cout<<"[VP] PrintVideoInfo"<<std::endl;
    }

    void DownloadVideo(size_t id, const std::string& path) override
    {
        std::cout<<"[VP] DownloadVideo"<<std::endl;
    }
};


#endif