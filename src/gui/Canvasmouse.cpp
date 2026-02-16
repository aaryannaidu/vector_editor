#include "gui/Canvas.h"
#include "model/Rectangle.h"
#include "model/Circle.h"
#include "model/Line.h"
#include "model/RoundedRectangle.h"
#include "model/FreeHand.h"
#include "model/Hexagon.h"
#include "model/Text.h"
#include <QMouseEvent>
#include <QInputDialog>
#include <QLineEdit>

void Canvas::mousePressEvent(QMouseEvent* event){
    if (!diagram_) return;
    int x = event->position().x();
    int y = event->position().y();

    if(selected_){ //check resize area
        QRect rect= selected_->boundingRect();
        int margin = 6;
        QRect outer = rect.adjusted(-margin, -margin, margin, margin);
        QRect inner = rect.adjusted(margin, margin, -margin, -margin);
        if(outer.contains(event->pos()) && !inner.contains(event->pos())){
            diagram_->saveState();
            isResizing_=true;
            startPoint_=event->pos();
            return ;
        }
    }
    // clear previou selection
    for (auto& obj : diagram_->getObjects()){
        obj->setSelected(false);
    }
    selected_ = nullptr;

    for (auto& obj : diagram_->getObjects()){
        if (obj->contains(x, y)){
            diagram_->saveState();
            selected_ = obj.get();
            selected_->setSelected(true);
            isMoving_ = true;
            startPoint_ = event->position().toPoint();
            update();
            return;
        }
    }  
    if (currentShape == ShapeType::Text) { // Handle Text creation
        QPoint p = event->position().toPoint();
        bool ok;
        QString input = QInputDialog::getText(this,"Enter Text","Text:",
        QLineEdit::Normal,"",&ok);

        if (ok && !input.isEmpty()) {
            auto textobj = std::make_unique<Text>(p.x(),p.y(),input.toStdString());
            textobj->setFillColor(Qt::black);
            diagram_->add(std::move(textobj));
        }
        update();
        return;
    }
    // start drawing new shape 
    isDrawing_ = true;
    startPoint_ = event->position().toPoint();
    currentPoint_ = startPoint_;
    if (currentShape == ShapeType::FreeHand) { 
        currentFreehandPoints_.clear();
        currentFreehandPoints_.push_back({startPoint_.x(), startPoint_.y()});
    }
}

void Canvas::mouseMoveEvent(QMouseEvent* event){
    if(isResizing_&& selected_){
        QPoint current=event->pos();
        int dx= current.x()-startPoint_.x();
        int dy= current.y()-startPoint_.y();
        selected_->resize(dx, dy);
        startPoint_ = current;
        update();
        return ;
    }
    if (isMoving_&&selected_){
        QPoint current = event->position().toPoint();
        int dx = current.x() - startPoint_.x();
        int dy = current.y() - startPoint_.y();

        selected_->move(dx, dy);

        startPoint_ = current;
        update();
        return;
    }
    if (!isDrawing_) return;
    if (currentShape == ShapeType::FreeHand) {
        QPoint p = event->position().toPoint();
        currentFreehandPoints_.push_back({p.x(), p.y()});
    }
    currentPoint_ = event->position().toPoint();
    update(); 
}

void Canvas::mouseReleaseEvent(QMouseEvent* event){
    if(isResizing_){
        isResizing_=false;
        return ;
    }
    if (isMoving_){   
        isMoving_ = false;
        return;
    }   
    if (!diagram_ || !isDrawing_) return;
    isDrawing_ = false;

    int x1 = startPoint_.x();
    int y1 = startPoint_.y();
    int x2 = event->position().x();
    int y2 = event->position().y();
    int width = std::abs(x2 - x1);
    int height = std::abs(y2 - y1);
    if (width < 5 && height < 5){
        update();
        return;  
    }
    int x = std::min(x1, x2);
    int y = std::min(y1, y2);

    switch (currentShape){
        case ShapeType::Rectangle:
            diagram_->add(std::make_unique<Rectangle>(x, y, width, height));
            break;
        case ShapeType::Circle:{
            int radius = std::hypot(x2 - x1, y2 - y1); ;
            diagram_->add(std::make_unique<Circle>(x1, y1, radius));
            break;
        }
        case ShapeType::Line:
            diagram_->add(std::make_unique<Line>(x1, y1, x2, y2));
            break;
        case ShapeType::RoundedRectangle:
            diagram_->add(std::make_unique<RoundedRectangle>(x,y,width,height,15));
            break;
        case ShapeType::Hexagon:{
            int dx = x2 - x1;
            int dy = y2 - y1;
            int radius = std::hypot(dx, dy);
            diagram_->add(std::make_unique<Hexagon>(x1, y1, radius));
            break;
        }
        case ShapeType::FreeHand:{
            if (currentFreehandPoints_.size() > 1){
                diagram_->add(std::make_unique<FreeHand>(currentFreehandPoints_));
            }
            currentFreehandPoints_.clear();
            break;
        }
        default:
            break;
    }
    update();
}

void Canvas::keyPressEvent(QKeyEvent* event){
    int key = event->key();
    if ((key == Qt::Key_Delete || key == Qt::Key_Backspace) && selected_ && diagram_){
        diagram_->remove(selected_);
        selected_ = nullptr;
        update();
    }
}