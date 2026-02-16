//create Tool Bar,menus and action
// Connect UI with Canvas and Diagram
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gui/Canvas.h"
#include "model/Diagram.h"

class MainWindow:public QMainWindow{
    Q_OBJECT
    public:
        explicit MainWindow(QWidget* parent = nullptr);
    private:
        void createAction();
        void createMenu();
        void createToolBar();
        void connectAction();
        Canvas* canvas_;
        Diagram* diagram_;

        QAction* rect_;
        QAction* circle_;
        QAction* line_;
        QAction* roundedRect_;
        QAction* hexagon_;
        QAction* freehand_;
        QAction* text_;

        QAction* open_;
        QAction* save_;
        QAction* close_;

        QAction* undo_;
        QAction* redo_;
        QAction* copy_;
        QAction* cut_;
        QAction* paste_;
        QAction* strokeColor_;
        QAction* fillColor_;
        QAction* strokeWidth_;
       
};
#endif