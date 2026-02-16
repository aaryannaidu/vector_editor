#include "model/RoundedRectangle.h"
#include <string>
#include <QPainter>

RoundedRectangle::RoundedRectangle(int x,int y,int w,int h,int r)
    : x_(x),y_(y),w_(w),h_(h),r_(r) {}

void RoundedRectangle::move (int dx,int dy){
    x_+=dx;
    y_+=dy;
}
std::string RoundedRectangle::toSVG() const{
    std::string fillvalue;
    if (fillColor_ ==Qt::transparent) fillvalue = "none";
    else fillvalue = fillColor_.name().toStdString();
    return "<rect x=\""+std::to_string(x_)+"\" y=\""
    +std::to_string(y_)+"\" width=\""+std::to_string(w_)+"\" height=\""
    +std::to_string(h_)+"\" rx=\""+std::to_string(r_)+"\" ry=\""
    +std::to_string(r_)+"\" stroke=\"" + strokeColor_.name().toStdString() +
    "\" stroke-width=\"" + std::to_string(strokeWidth_) +
    "\" fill=\"" + fillvalue +"\" />";
}

void RoundedRectangle::draw(QPainter& painter) const
{
    QPen pen(strokeColor_);
    pen.setWidth(strokeWidth_);
    painter.setPen(pen);
    painter.setBrush(fillColor_);

    painter.drawRoundedRect(x_, y_, w_, h_, r_, r_);

    if (selected_)
    {
        QPen dashPen(Qt::blue);
        dashPen.setStyle(Qt::DashLine);
        dashPen.setWidth(2);
        painter.setPen(dashPen);
        painter.setBrush(Qt::NoBrush);
        painter.drawRoundedRect(x_, y_, w_, h_, r_, r_);
    }
}
bool RoundedRectangle::contains(int x, int y) const {
    return (x>=x_ && x<=x_+w_ &&
            y>=y_ && y<=y_+h_);
}
std::unique_ptr<GraphicsObject> RoundedRectangle::clone() const {
  return std::make_unique<RoundedRectangle>(*this);
}
QRect RoundedRectangle::boundingRect() const {
    return QRect(x_,y_,w_,h_);
}
void RoundedRectangle::resize(int dx, int dy) {
    w_+= dx;
    h_+= dy;
    if(w_< 10) w_=10;
    if(h_< 10) h_=10;
}