#include <string>
#include "model/Line.h"
#include <QPainter>

Line::Line (int x1,int y1,int x2,int y2)
    : x1_(x1),y1_(y1),x2_(x2),y2_(y2) {}

void Line::move(int dx,int dy){
    x1_ +=dx ;x2_ +=dx;
    y1_ +=dy ;y2_ +=dy;
}


std::string Line::toSVG() const {
    return "<line x1=\""+std::to_string(x1_)+"\" y1=\""+std::to_string(y1_)
    +"\" x2=\""+std::to_string(x2_)+"\" y2=\""+std::to_string(y2_)+
    "\" stroke=\"" + strokeColor_.name().toStdString() +
    "\" stroke-width=\"" + std::to_string(strokeWidth_)+"\" fill=\"none\" />";
}

void Line::draw(QPainter& painter) const{
    QPen pen(strokeColor_);
    pen.setWidth(strokeWidth_);
    painter.setPen(pen);
    painter.drawLine(x1_, y1_, x2_, y2_);

    if (selected_){
        QPen dashPen(Qt::blue);
        dashPen.setStyle(Qt::DashLine);
        dashPen.setWidth(2);
        painter.setPen(dashPen);
        painter.drawLine(x1_, y1_, x2_, y2_);
    }
}
bool Line::contains(int x, int y) const{
    int minX = std::min(x1_, x2_);
    int maxX = std::max(x1_, x2_);
    int minY = std::min(y1_, y2_);
    int maxY = std::max(y1_, y2_);
    return (x >= minX && x <= maxX &&
            y >= minY && y <= maxY);
}
std::unique_ptr<GraphicsObject> Line::clone() const {
  return std::make_unique<Line>(*this);
}
QRect Line::boundingRect() const {
    return QRect(std::min(x1_, x2_),std::min(y1_, y2_),
                std::abs(x2_ - x1_),std::abs(y2_ - y1_)
    );
}
void Line::resize(int dx, int dy) {
    x2_+=dx;
    y2_+=dy;
}