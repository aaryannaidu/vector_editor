#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "GraphicsObject.h"

class Rectangle: public GraphicsObject{
    private:
        int x_,y_,w_,h_; // top left postion and width and height
    public:
        Rectangle(int x,int y,int w,int h);
        void move(int dx,int dy) override;
        std::string toSVG() const override;
        void draw(QPainter& painter) const override;
        bool contains(int x, int y) const override;
        std::unique_ptr<GraphicsObject> clone() const override;
        void resize(int dx, int dy) override;
        QRect boundingRect() const override;
};
#endif