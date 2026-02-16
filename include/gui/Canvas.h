// Qwidget responsible for rendering and interacting
// Handle -Drawing new shape ,selecting,Moving,Resizing,Copy,Cut,Paste,Keyboard delete
#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include "model/Diagram.h"

enum class ShapeType{
    Rectangle,
    Circle,
    Line,
    RoundedRectangle,
    Hexagon,
    FreeHand,
    Text
};

class Canvas : public QWidget{
    Q_OBJECT

    public:
    explicit Canvas(QWidget* parent = nullptr);
    void setDiagram(Diagram* diagram);
    void setShapeType(ShapeType type);
    void copy();
    void cut();
    void paste();
    GraphicsObject* getSelected() const;

    protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

    private:
    Diagram* diagram_;
    GraphicsObject* selected_ = nullptr;
    std::unique_ptr<GraphicsObject> clipboard_;
    bool isMoving_=false;
    bool isDrawing_=false;
    bool isResizing_ = false;
    QPoint startPoint_;
    QPoint currentPoint_;
    ShapeType currentShape= ShapeType::Rectangle;
    std::vector<std::pair<int,int>> currentFreehandPoints_;
};

#endif