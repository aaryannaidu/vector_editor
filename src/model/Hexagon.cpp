#include "model/Hexagon.h"
#include<string>
#include <QPainter>
Hexagon:: Hexagon(int cx, int cy,int r)
    : cx_(cx),cy_(cy),r_(r) {}

void Hexagon::move (int dx,int dy){
    cx_ +=dx;
    cy_ +=dy;
}

std::string Hexagon::toSVG() const {
    std::string points;
    for (int i =0;i<6;i++){
        double angle = i*3.141592653589793/3.0;
        int x = cx_ + static_cast<int>(r_ * std::cos(angle));
        int y = cy_ + static_cast<int>(r_ * std::sin(angle));
        points += std::to_string(x) + "," + std::to_string(y) + " ";
    }
    std::string fillvalue;
    if (fillColor_ ==Qt::transparent) fillvalue = "none";
    else fillvalue = fillColor_.name().toStdString();
    return "<polygon points=\""+points+"\" stroke=\"" + strokeColor_.name().toStdString() +
        "\" stroke-width=\"" + std::to_string(strokeWidth_) +"\" fill=\"" 
        + fillvalue +"\" />\n";
}

bool Hexagon::contains(int x, int y) const{
    QPolygon polygon;

    for (int i = 0; i < 6; ++i){
        double angle = i * M_PI / 3;
        int px = cx_ + r_ * cos(angle);
        int py = cy_ + r_ * sin(angle);
        polygon << QPoint(px, py);
    }
    return polygon.containsPoint(QPoint(x, y), Qt::OddEvenFill);
}
void Hexagon::draw(QPainter& painter) const{
    QPen pen(strokeColor_);
    pen.setWidth(strokeWidth_);
    painter.setPen(pen);
    painter.setBrush(fillColor_);

    QPolygon polygon;
    for (int i = 0; i < 6; ++i){
        double angle = i * M_PI / 3;
        int x = cx_ + r_ * cos(angle);
        int y = cy_ + r_ * sin(angle);
        polygon << QPoint(x, y);
    }

    painter.drawPolygon(polygon);

    if (selected_){
        QPen dashPen(Qt::blue);
        dashPen.setStyle(Qt::DashLine);
        dashPen.setWidth(2);
        painter.setPen(dashPen);
        painter.setBrush(Qt::NoBrush);
        painter.drawPolygon(polygon);
    }
}
std::unique_ptr<GraphicsObject> Hexagon::clone() const {
  return std::make_unique<Hexagon>(*this);
}
QRect Hexagon::boundingRect() const{
    return QRect(cx_-r_,cy_-r_,2*r_,2*r_);
}
void Hexagon::resize(int dx,int dy){
    int delta=std::max(dx, dy);
    r_ += delta;
    if (r_ < 10) r_=10;
}

