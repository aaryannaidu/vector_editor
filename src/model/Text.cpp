#include "model/Text.h"
#include <QPainter>
#include <QPainterPath>
Text::Text(int x,int y,const std::string& content)
    : x_(x),y_(y),content_(content) {}

void Text::move (int dx,int dy){
    x_+=dx;
    y_+=dy;
}
std::string Text::toSVG() const {
    return "<text x=\""+std::to_string(x_)+"\" y=\""+std::to_string(y_)
    +"\" fill=\"" + fillColor_.name().toStdString()+"\">" +
    content_+"</text>";
}
void Text::draw(QPainter& painter) const{
    QFont font;
    font.setPointSize(fontSize_);
    painter.setFont(font);
    QPen pen(strokeColor_);   
    painter.setPen(pen);
     painter.drawText(x_, y_, QString::fromStdString(content_));
    if (selected_){
        QPen dashPen(Qt::blue);
        dashPen.setStyle(Qt::DashLine);
        painter.setPen(dashPen);
        painter.drawRect(boundingRect());
    }
}
bool Text::contains(int x, int y) const{
    int width = content_.length() * 8;   
    int height = 20;

    return (x >= x_ &&
            x <= x_ + width &&
            y >= y_ - height &&
            y <= y_);
}
std::unique_ptr<GraphicsObject> Text::clone() const {
  return std::make_unique<Text>(*this);
}
QRect Text::boundingRect() const {
    QFont font;
    font.setPointSize(fontSize_);
    QFontMetrics fm(font);
    QRect rect = fm.boundingRect(QString::fromStdString(content_));
    rect.moveTopLeft(QPoint(x_,y_-rect.height()));
    return rect;
}
void Text::resize(int dx, int dy) {
    fontSize_+=(dx+dy)/6;
    if (fontSize_<6) fontSize_=6;
}