#include "gui/Canvas.h"

// Enable focus for Delete object
Canvas::Canvas(QWidget* parent)
    : QWidget(parent), diagram_(nullptr){
    setFocusPolicy(Qt::StrongFocus);
}
// Assign diagram model to canvas,set currect object
void Canvas::setDiagram(Diagram* diagram){
    diagram_ = diagram;
    update();
}
void Canvas::setShapeType(ShapeType type){
    currentShape = type;
}
// store clone ,remove selected,pate clone
void Canvas::copy() {
    if (!selected_) return;
    clipboard_ = selected_->clone();
}
void Canvas::cut() {
    if (!selected_) return;
    clipboard_ = selected_->clone();
    diagram_->remove(selected_);
    selected_ = nullptr;
    update();
}
void Canvas::paste() {
    if (!clipboard_) return;
    auto newObject = clipboard_->clone();
    newObject->move(10, 10);
    diagram_->add(std::move(newObject));
    update();
}
// return current selected object
GraphicsObject* Canvas::getSelected() const {
    return selected_;
}


