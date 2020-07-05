#include "Common.h"

using namespace std;

// Этот файл сдаётся на проверку
// Здесь напишите реализацию необходимых классов-потомков `IShape`
#include <iostream>

// Точка передаётся в локальных координатах
bool IsPointInSize(Point p, Size s) {
  return p.x >= 0 && p.y >= 0 && p.x < s.width && p.y < s.height;
}

Size GetImageSize(const Image& image) {
  auto width = image.empty() ? 0 : image[0].size();
  auto height = image.size();
  return {(int)width, (int)height};
}

class Shape : public IShape {
 public:
  Shape() {
    _size = {0, 0};
    _position = {0, 0};
  }

  std::unique_ptr<IShape> Clone() const override = 0;

  void SetPosition(Point point) override {
    _position = point;
  }

  Point GetPosition() const  override {
    return _position;
  }

  void SetSize(Size size) override {
    _size = size;
  }

  Size GetSize() const override {;
    return _size;
  }

  void SetTexture(std::shared_ptr<ITexture> texture) override {
    _texture = texture;
  }

  ITexture* GetTexture() const override {
    return _texture.get();
  }

  // Рисует фигуру на указанном изображении
  void Draw(Image& img) const override {
    Point p;
    auto image_size = GetImageSize(img);
    for (p.y = 0; p.y < _size.height; ++p.y) {
      for (p.x = 0; p.x < _size.width; ++p.x) {
        if (IsPointInShape(p)) {
          char pixel = '.';
          if (_texture && IsPointInSize(p, _texture->GetSize())) {
            pixel = _texture->GetImage()[p.y][p.x];
          }
          Point dp = {_position.x + p.x, _position.y + p.y};
          if (IsPointInSize(dp, image_size)) {
            img[dp.y][dp.x] = pixel;
          }
        }
      }
    }
  }

 protected:
  virtual bool IsPointInShape(Point) const = 0;
  Size _size;
  Point _position;
  std::shared_ptr<ITexture> _texture;

};

namespace Shapes {
class Rectangle : public Shape {
 public:
  unique_ptr<IShape> Clone() const override {
    return make_unique<Rectangle>(*this);
  }

 private:
  bool IsPointInShape(Point p) const override {
    return true;
  }
};

class Ellipse : public Shape {
 public:
  unique_ptr<IShape> Clone() const override {
    return make_unique<Ellipse>(*this);
  }

 private:
  bool IsPointInShape(Point p) const override {
    return IsPointInEllipse(p, GetSize());
  }
};
}

// Напишите реализацию функции
unique_ptr<IShape> MakeShape(ShapeType shape_type) {
  switch (shape_type) {
    case ShapeType::Rectangle: {
      return std::make_unique<Shapes::Rectangle>();
    }
    case ShapeType::Ellipse: {
      return std::make_unique<Shapes::Ellipse>();
    }
    default: {
      throw std::logic_error("Wrong shape type");
    }
  }
}
