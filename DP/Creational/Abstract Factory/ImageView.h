#ifndef _IMAGE_VIEW_H_
#define _IMAGE_VIEW_H_

#include <iostream>

struct IImageView
{
    virtual ~IImageView() = default;

    virtual void SetWidth() = 0;
    virtual void SetHeight() = 0;
    virtual void SetTitle() = 0;
    virtual void ShowImage(void*) = 0;
};

class ImageViewMac : public IImageView
{
private:
    /* data */
public:
    ImageViewMac(/* args */) = default;
    ~ImageViewMac() = default;

    void SetWidth() override
    {
        std::cout<<"[IV Mac] SetWidth"<<std::endl;
    }

    void SetHeight() override
    {
        std::cout<<"[IV Mac] SetHeight"<<std::endl;
    }

    void SetTitle() override
    {
        std::cout<<"[IV Mac] SetTitle"<<std::endl;
    }

    void ShowImage(void*) override
    {
        std::cout<<"[IV Mac] ShowImage"<<std::endl;
    }

};

class ImageViewWindows : public IImageView
{
private:
    /* data */
public:
    ImageViewWindows(/* args */) = default;
    ~ImageViewWindows() = default;

    void SetWidth() override
    {
        std::cout<<"[IV Windows] SetWidth"<<std::endl;
    }

    void SetHeight() override
    {
        std::cout<<"[IV Windows] SetHeight"<<std::endl;
    }

    void SetTitle() override
    {
        std::cout<<"[IV Windows] SetTitle"<<std::endl;
    }

    void ShowImage(void*) override
    {
        std::cout<<"[IV Windows] ShowImage"<<std::endl;
    }

};


#endif