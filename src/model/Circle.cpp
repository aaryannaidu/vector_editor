#include "model/Circle.h"
#include<string>
#include <QPainter>

Circle::Circle(int cx,int cy,int r): cx_(cx),cy_(cy),r_(r){}

void Circle::move(int dx, int dy) {
    cx_ += dx;
    cy_ += dy;
}

std::string Circle::toSVG() const{
    std::string fillvalue;
    if (fillColor_ ==Qt::transparent) fillvalue = "none";
    else fillvalue = fillColor_.name().toStdString();
    return "<circle cx=\""+ std::to_string(cx_)+"\" cy=\""+std::to_string(cy_)
    +"\" r=\""+std::to_string(r_)+"\" stroke=\"" + strokeColor_.name().toStdString() +
    "\" stroke-width=\"" + std::to_string(strokeWidth_) +"\" fill=\"" + 
    fillvalue +"\" />\n";
}

void Circle::draw(QPainter& painter) const{
    QPen pen(strokeColor_);
    pen.setWidth(strokeWidth_);
    painter.setPen(pen);
    painter.setBrush(fillColor_);
    painter.drawEllipse(QPoint(cx_, cy_), r_, r_);

    if (selected_){
        QPen dashPen(Qt::blue);
        dashPen.setStyle(Qt::DashLine);
        dashPen.setWidth(2);
        painter.setPen(dashPen);
        painter.setBrush(Qt::NoBrush);
        painter.drawEllipse(QPoint(cx_, cy_), r_, r_);
    }
}

bool Circle::contains(int x, int y) const{
    int dx = x - cx_;
    int dy = y - cy_;
    return (dx*dx + dy*dy) <= r_*r_;
}

std::unique_ptr<GraphicsObject> Circle::clone() const {
  return std::make_unique<Circle>(*this);
}
void Circle::resize(int dx, int dy) {
    r_ += std::max(dx, dy);
    if (r_< 5) r_=5;
}
QRect Circle::boundingRect() const {
    return QRect(cx_-r_,cy_-r_,2*r_,2*r_);
}

