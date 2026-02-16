#include "model/FreeHand.h"
#include "string"
#include <QPainter>
#include <cmath>

FreeHand::FreeHand(const std::vector<std::pair<int,int>>& points)
    : points_(points) {}

void FreeHand::move(int dx,int dy){
    for(auto&p :points_){
        p.first +=dx;
        p.second +=dy;
    }
}

std::string FreeHand::toSVG() const {
    std::string points;
    for(const auto&p :points_){
        points +=std::to_string(p.first)+","+std::to_string(p.second)+" ";
    }
    return "<polyline points=\""+points +"\" stroke=\"" + strokeColor_.name().toStdString() +
    "\" stroke-width=\"" + std::to_string(strokeWidth_) +"\" fill=\"none\" />\n";
}

void FreeHand::draw(QPainter& painter) const
{
    QPen pen(strokeColor_);
    pen.setWidth(strokeWidth_);
    painter.setPen(pen);

    for(size_t i = 1; i < points_.size(); ++i){
        painter.drawLine(
            points_[i - 1].first,
            points_[i - 1].second,
            points_[i].first,
            points_[i].second
        );
    }
    if (selected_){
        QPen dashPen(Qt::blue);
        dashPen.setStyle(Qt::DashLine);
        dashPen.setWidth(2);
        painter.setPen(dashPen);
        painter.setBrush(Qt::NoBrush);
        
        int minX = points_[0].first, maxX = points_[0].first;
        int minY = points_[0].second, maxY = points_[0].second;
        for (const auto& p : points_){
            minX = std::min(minX, p.first);
            maxX = std::max(maxX, p.first);
            minY = std::min(minY, p.second);
            maxY = std::max(maxY, p.second);
        }
        painter.drawRect(minX, minY, maxX - minX, maxY - minY);
    }
}

bool FreeHand::contains(int x, int y) const{
    const double threshold = 5.0;
    for(size_t i = 1; i < points_.size(); ++i){
        double x1 = points_[i - 1].first;
        double y1 = points_[i - 1].second;
        double x2 = points_[i].first;
        double y2 = points_[i].second;
        double dx = x2 - x1;
        double dy = y2 - y1;
        double lengthSquared = dx*dx+dy*dy;

        double distance;
        if(lengthSquared == 0){
            distance = std::sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
        } 
        else{
            double t=((x-x1)*dx+(y-y1)*dy)/lengthSquared;
            t = std::max(0.0, std::min(1.0, t));
            double closestX = x1 + t * dx;
            double closestY = y1 + t * dy;        
            distance = std::sqrt((x-closestX)*(x-closestX) + 
                               (y - closestY)*(y-closestY));
        }
        if (distance < threshold){
            return true;
        }
    }

    return false;
}
std::unique_ptr<GraphicsObject> FreeHand::clone() const{
    return std::make_unique<FreeHand>(*this);
}
QRect FreeHand::boundingRect() const {
    if (points_.empty()) return QRect();
    int minx=points_[0].first;
    int maxx=points_[0].first;
    int miny=points_[0].second;
    int maxy=points_[0].second;

    for(const auto& p : points_) {
        minx=std::min(minx, p.first);
        maxx=std::max(maxx, p.first);
        miny=std::min(miny, p.second);
        maxy=std::max(maxy, p.second);
    }
    return QRect(minx,miny,maxx-minx,maxy-miny);
}
void FreeHand::resize(int dx, int dy) {
    QRect rect= boundingRect();
    double newwidth= rect.width()+dx;
    double newheight= rect.height()+dy;
    if(newwidth<10 || newheight<10) return ;
    double scaleX= newwidth/rect.width();
    double scaleY= newheight/rect.height();
    int minX= rect.left();
    int minY=rect.top();
    for(auto& p:points_){
        p.first= minX+(p.first-minX)*scaleX;
        p.second= minY+(p.second-minY)*scaleY;
    }
}