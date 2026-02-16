#ifndef FREEHAND_H
#define FREEHAND_H

#include "GraphicsObject.h"
#include <vector>
#include <utility>

class FreeHand:public GraphicsObject{
    private:
        std::vector<std::pair<int,int>> points_;// store List of Points
    public:
        FreeHand(const std::vector<std::pair<int,int>>& points);
        void move(int dx,int dy) override;
        std::string toSVG() const override;
        void draw(QPainter& painter) const override;
        bool contains(int x, int y) const override;
        std::unique_ptr<GraphicsObject> clone() const override;
        void resize(int dx, int dy) override;
        QRect boundingRect() const override;
};
#endif