#ifndef TEXT_H
#define TEXT_H

#include "GraphicsObject.h"
#include <string>
class Text: public GraphicsObject{
    private:
        int x_,y_;  // Text postion , Top left
        std::string content_; // Text content
    public:
        Text(int x,int y,const std::string& content);
        void move(int dx,int dy) override;
        std::string toSVG() const override;
        void draw(QPainter& painter) const override;
        bool contains(int x, int y) const override;
        std::unique_ptr<GraphicsObject> clone() const override;
        void resize(int dx, int dy) override;
        QRect boundingRect() const override;
        int fontSize_ = 14;
};
#endif