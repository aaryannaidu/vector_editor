#ifndef CIRCLE_H
#define CIRCLE_H

#include "GraphicsObject.h"
class Circle : public GraphicsObject {
    public:
        Circle(int cx,int cy,int r);
        void move (int dx,int dy) override;
        std::string toSVG() const override;
        void draw(QPainter& painter) const override;
        bool contains(int x, int y) const override;
        std::unique_ptr<GraphicsObject> clone() const override;
        void resize(int dx, int dy) override;
        QRect boundingRect() const override;
    private:
        int cx_,cy_,r_; // center postion and radius
};

#endif