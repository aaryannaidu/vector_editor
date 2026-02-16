#ifndef HEXAGON_H
#define HEXAGON_H
#include "GraphicsObject.h"
class Hexagon: public GraphicsObject{
    private:
        int cx_,cy_,r_; // center and radius
    public:
        Hexagon(int cx,int cy,int r);
        void move(int dx,int dy) override;
        std::string toSVG() const override;
        void draw(QPainter& painter) const override;
        bool contains(int x, int y) const override;
        std::unique_ptr<GraphicsObject> clone() const override;
        void resize(int dx, int dy) override;
        QRect boundingRect() const override;
};
#endif