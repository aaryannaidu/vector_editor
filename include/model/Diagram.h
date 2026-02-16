//  store and manage all Shapes
//  Handle remove,clear,add,undo ,redo history,SVG export of entire Drawing
#ifndef DIAGRAM_H
#define DIAGRAM_H
#include<memory>
#include<vector>
#include <stack>
#include "GraphicsObject.h"

class Diagram{
    public:
        Diagram()=default;
        void add (std::unique_ptr<GraphicsObject> obj);
        const std::vector<std::unique_ptr<GraphicsObject>> &getObjects() const;
        void remove(GraphicsObject* obj);
        void clear();                    
        std::string toSVG() const; 
        void undo();
        void redo();
        void resetHistory();
        void saveState();
    private:
        std::vector<std::unique_ptr<GraphicsObject>> objects_;
        std::stack<std::vector<std::unique_ptr<GraphicsObject>>> undoStack_;
        std::stack<std::vector<std::unique_ptr<GraphicsObject>>> redoStack_;
};
#endif

