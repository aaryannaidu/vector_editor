#include "gui/MainWindow.h"
#include "svg/SVGwriter.h"
#include "svg/SVGparser.h"

#include <QToolBar>
#include <QMenuBar>
#include <QFileDialog>
#include <QColorDialog>
#include <QInputDialog>
#include <QKeySequence>


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent){
    setWindowTitle("Micro Vector Editor");
    resize(800, 600);
    canvas_ = new Canvas(); // create core component
    diagram_ = new Diagram();
    canvas_->setDiagram(diagram_); //connect canvas with diagram
    setCentralWidget(canvas_);

    createAction(); //Initializtion of UI Structure
    createToolBar();
    createMenu();
    connectAction();
}

void MainWindow::createAction(){
    rect_ = new QAction("Rectangle", this); //shape action
    circle_ = new QAction("Circle", this);
    line_ = new QAction("Line", this);
    roundedRect_ = new QAction("RoundedRect", this);
    hexagon_= new QAction("Hexagon", this);
    freehand_= new QAction("FreeHand", this);
    text_= new QAction("Text", this);
    // file action
    open_= new QAction("Open SVG", this);
    save_= new QAction("Save as SVG", this);
    close_= new QAction("Close", this);
    // edit action
    undo_= new QAction("Undo", this);
    redo_= new QAction("Redo", this);
    copy_= new QAction("Copy", this);
    cut_= new QAction("Cut", this);
    paste_= new QAction("Paste", this);
    strokeColor_= new QAction("Stroke Color", this); // style action
    fillColor_= new QAction("Fill Color", this);
    strokeWidth_= new QAction("Stroke Width", this);

    undo_->setShortcut(QKeySequence::Undo); // shortcut 
    redo_->setShortcut(QKeySequence::Redo);
    copy_->setShortcut(QKeySequence::Copy);
    cut_->setShortcut(QKeySequence::Cut);
    paste_->setShortcut(QKeySequence::Paste);
}

void MainWindow::createMenu(){
    QMenu* fileMenu = menuBar()->addMenu("File"); //file menu
    fileMenu->addAction(open_);
    fileMenu->addAction(save_);
    fileMenu->addAction(close_);

    QMenu* editMenu = menuBar()->addMenu("Edit"); //Edit menu
    editMenu->addAction(undo_);
    editMenu->addAction(redo_);
    editMenu->addSeparator();
    editMenu->addAction(copy_);
    editMenu->addAction(cut_);
    editMenu->addAction(paste_);
    editMenu->addSeparator();
    editMenu->addAction(strokeColor_);
    editMenu->addAction(fillColor_);
    editMenu->addAction(strokeWidth_);
}

void MainWindow::createToolBar(){
    QToolBar* toolbar = addToolBar("Shapes"); // Tool Bar

    toolbar->addAction(rect_);
    toolbar->addAction(circle_);
    toolbar->addAction(line_);
    toolbar->addAction(roundedRect_);
    toolbar->addAction(hexagon_);
    toolbar->addAction(freehand_);
    toolbar->addAction(text_);
}

