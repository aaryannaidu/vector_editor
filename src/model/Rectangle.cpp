#include "model/Rectangle.h"
#include "string"
#include <QPainter>

Rectangle::Rectangle(int x,int y,int w,int h)
    : x_(x),y_(y),w_(w),h_(h) {}

void Rectangle::move (int dx,int dy){
    x_ +=dx;
    y_ +=dy;
}


std::string Rectangle::toSVG() const{
    std::string fillvalue ;
    if (fillColor_ ==Qt::transparent) fillvalue = "none";
    else fillvalue = fillColor_.name().toStdString();
    return "<rect x=\""+std::to_string(x_)+"\" y=\""
    +std::to_string(y_)+"\" width=\""+std::to_string(w_)+"\" height=\""
    +std::to_string(h_)+"\" stroke=\"" + strokeColor_.name().toStdString() +
    "\" stroke-width=\"" + std::to_string(strokeWidth_) +
    "\" fill=\"" + fillvalue +"\" />";
}
void Rectangle::draw(QPainter& painter) const
{
    QPen pen(strokeColor_);
    pen.setWidth(strokeWidth_);
    painter.setPen(pen);
    painter.setBrush(fillColor_);

    painter.drawRect(x_, y_, w_, h_);

    if (selected_)
    {
        QPen dashPen(Qt::blue);
        dashPen.setStyle(Qt::DashLine);
        dashPen.setWidth(2);
        painter.setPen(dashPen);
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(x_, y_, w_, h_);
    }
}
bool Rectangle::contains(int x,int y) const{
    return (x>=x_ && x<=x_+w_ && y>=y_ && y<=y_ + h_);
}   
std::unique_ptr<GraphicsObject> Rectangle::clone() const {
  return std::make_unique<Rectangle>(*this);
}
void Rectangle::resize(int dx, int dy) {
    w_ += dx;
    h_ += dy;
    if (w_< 10) w_ = 10;
    if (h_< 10) h_ = 10;
}
QRect Rectangle::boundingRect() const {
    return QRect(x_,y_,w_,h_);
}

