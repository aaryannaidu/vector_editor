#include "gui/MainWindow.h"
#include "svg/SVGwriter.h"
#include "svg/SVGparser.h"

#include <QFileDialog>
#include <QColorDialog>
#include <QInputDialog>

void MainWindow::connectAction(){
    //shape Selection actions
    connect(rect_, &QAction::triggered,[this]() 
            { canvas_->setShapeType(ShapeType::Rectangle);});
    connect(circle_, &QAction::triggered,[this]()
            { canvas_->setShapeType(ShapeType::Circle);});
    connect(line_, &QAction::triggered,[this]() 
            { canvas_->setShapeType(ShapeType::Line);});
    connect(roundedRect_, &QAction::triggered,[this]() 
            { canvas_->setShapeType(ShapeType::RoundedRectangle);});
    connect(hexagon_, &QAction::triggered,[this]() 
            { canvas_->setShapeType(ShapeType::Hexagon);});
    connect(freehand_, &QAction::triggered,[this]() 
            { canvas_->setShapeType(ShapeType::FreeHand);});
    connect(text_, &QAction::triggered,[this]() 
            { canvas_->setShapeType(ShapeType::Text);});
    //File operation
    connect(close_, &QAction::triggered, [this]() { 
        diagram_->clear();
        diagram_->resetHistory();
        canvas_->update();
    });
    connect(open_, &QAction::triggered, [this]() {
        QString fileName = QFileDialog::getOpenFileName(
            this, "Open SVG File", "", "SVG Files (*.svg)");

        if (!fileName.isEmpty()) {
            Diagram newDiagram = SVGparser::parseFile(fileName.toStdString());
            diagram_->clear();
            diagram_->resetHistory();
            *diagram_ = std::move(newDiagram);
            canvas_->update();
        }
    });
    connect(save_, &QAction::triggered, [this]() {
        QString fileName = QFileDialog::getSaveFileName(
            this, "Save SVG", "", "SVG Files (*.svg)");
        if (!fileName.isEmpty()) {
            SVGwriter writer;
            writer.writeFile(fileName.toStdString(), *diagram_);
        }
    });

    connect(undo_,&QAction::triggered,[this]() 
            { diagram_->undo(); canvas_->update();});
    connect(redo_,&QAction::triggered,[this]() 
            { diagram_->redo(); canvas_->update();});
    connect(copy_,&QAction::triggered,
            [this]() { canvas_->copy();});
    connect(cut_,&QAction::triggered,[this]() 
            { canvas_->cut();});
    connect(paste_,&QAction::triggered,[this]() 
            { canvas_->paste();});
    connect(strokeColor_, &QAction::triggered, [this]() { //stroke color change 
        if (!canvas_->getSelected()) return;
        QColor color = QColorDialog::getColor(Qt::black, this);
        if (color.isValid()) {
            diagram_->saveState();
            canvas_->getSelected()->setStrokeColor(color);
            canvas_->update();
        }
    }); // fill color change
    connect(fillColor_,&QAction::triggered, [this]() {
        if (!canvas_->getSelected()) return;
        QColor color = QColorDialog::getColor(Qt::white, this);
        if (color.isValid()) {
            diagram_->saveState();
            canvas_->getSelected()->setFillColor(color);
            canvas_->update();
        }
    });
    // stroke width change
    connect(strokeWidth_, &QAction::triggered, [this]() {
        if (!canvas_->getSelected()) return;
        bool ok;
        int width = QInputDialog::getInt(
            this, "Stroke Width", "Enter width:",
            canvas_->getSelected()->strokeWidth(),
            1, 20, 1, &ok);
        if (ok) {
            diagram_->saveState();
            canvas_->getSelected()->setStrokeWidth(width);
            canvas_->update();
        }
    });
}