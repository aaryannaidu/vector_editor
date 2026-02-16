#include "gui/Canvas.h"
#include "model/Rectangle.h"
#include "model/Circle.h"
#include "model/Line.h"
#include "model/RoundedRectangle.h"
#include "model/FreeHand.h"
#include "model/Hexagon.h"
#include "model/Text.h"
#include <QPainter>

void Canvas::paintEvent(QPaintEvent* event){
    Q_UNUSED(event);
    // create painting for rendering
    QPainter painter(this);
    //  all diagram
    if(diagram_){
        for(const auto & obj :diagram_->getObjects()){
            obj->draw(painter);
        }
        if(selected_){ // draw selection box
            QPen dashPen(Qt::blue);
            dashPen.setStyle(Qt::DashLine);
            dashPen.setWidth(1);
            painter.setPen(dashPen);
            painter.setBrush(Qt::NoBrush);
            painter.drawRect(selected_->boundingRect());
        }
    }

    if(isDrawing_) { // draw previou with creating new shape 
        QPen pen(Qt::gray);
        pen.setStyle(Qt::DashLine);
        painter.setPen(pen);
        switch(currentShape){
            case ShapeType::Rectangle:
                painter.drawRect(QRect(startPoint_, currentPoint_));
                break;
            case ShapeType::Circle:{
                int radius = std::hypot(currentPoint_.x() - startPoint_.x(),
                                        currentPoint_.y() - startPoint_.y());
                painter.drawEllipse(startPoint_, radius, radius);
                break;
            }
            case ShapeType::Line:
                painter.drawLine(startPoint_, currentPoint_);
                break;
            case ShapeType::RoundedRectangle:
                painter.drawRoundedRect(QRect(startPoint_, currentPoint_), 15, 15);
                break;
            case ShapeType::Hexagon:{
                int dx = currentPoint_.x() - startPoint_.x();
                int dy = currentPoint_.y() - startPoint_.y();
                int radius = std::hypot(dx, dy);

                QPolygon polygon;
                for (int i = 0; i < 6; ++i){
                    double angle = i * M_PI / 3;
                    int x = startPoint_.x() + radius * cos(angle);
                    int y = startPoint_.y() + radius * sin(angle);
                    polygon << QPoint(x, y);
                }
                painter.drawPolygon(polygon);
                break;
            }
            case ShapeType::FreeHand:{
                for (size_t i = 1; i < currentFreehandPoints_.size(); ++i){
                    painter.drawLine(
                        currentFreehandPoints_[i - 1].first,
                        currentFreehandPoints_[i - 1].second,
                        currentFreehandPoints_[i].first,
                        currentFreehandPoints_[i].second
                    );
                }
                break;
            default:
                break;
            }
        }
    }
}