#ifndef ROUNDED_RECTANGLE_H
#define ROUNDED_RECTANGLE_H

#include "GraphicsObject.h"

class RoundedRectangle:public GraphicsObject {
    private:
        int x_,y_,w_,h_,r_;  // same as rectangle but have rounded corner 
    public:
        RoundedRectangle(int x,int y,int w,int h,int r);
        void move(int dx,int dy) override;
        std::string toSVG() const override;
        void draw(QPainter& painter) const override;
        bool contains(int x, int y) const override;
        std::unique_ptr<GraphicsObject> clone() const override;
        void resize(int dx, int dy) override;
        QRect boundingRect() const override;
};
#endif