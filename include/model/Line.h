#ifndef LINE_H
#define LINE_H

#include "GraphicsObject.h"

class Line:public GraphicsObject{
    private:
        int x1_,y1_,x2_,y2_ ;// two end of line 
    public:
        Line (int x1,int y1,int x2,int y2);
        void move(int dx,int dy) override;
        std::string toSVG() const override;
        void draw(QPainter& painter) const override;
        bool contains(int x, int y) const override;
        std::unique_ptr<GraphicsObject> clone() const override;
        void resize(int dx, int dy) override;
        QRect boundingRect() const override;
};
#endif


