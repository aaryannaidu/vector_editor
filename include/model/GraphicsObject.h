#ifndef GRAPHICS_OBJECT_H
#define GRAPHICS_OBJECT_H
#include <QPainter>
#include <QColor>
#include <QRect>
#include<string>
class GraphicsObject {
    public:
        virtual ~GraphicsObject()=default;
        //  core behaviour for all shape
        virtual void move (int dx,int dy)=0;
        virtual std::string toSVG() const = 0;
        virtual void draw(QPainter& painter) const =0;
        virtual bool contains(int x, int y) const = 0;
        virtual void resize(int dx, int dy) =0;
        virtual QRect boundingRect() const = 0;
        virtual std::unique_ptr<GraphicsObject> clone() const = 0;
        // selection handling
        void setSelected(bool selected) { selected_ = selected; }
        bool isSelected() const { return selected_; }
        // style properties
        void setStrokeColor(const QColor& color) { strokeColor_ = color; }
        void setFillColor(const QColor& color) { fillColor_ = color; }
        QColor strokeColor() const { return strokeColor_; }
        QColor fillColor() const { return fillColor_; }
        void setStrokeWidth(int w) { strokeWidth_ = w; }
        int strokeWidth() const { return strokeWidth_; }
        
    protected:
        int strokeWidth_ = 1;
        bool selected_ = false;
        QColor strokeColor_ = Qt::black;
        QColor fillColor_ = Qt::transparent;
};

#endif
