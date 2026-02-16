#include "model/Diagram.h"
#include<algorithm>


std::vector<std::unique_ptr<GraphicsObject>>
cloneObjects(const std::vector<std::unique_ptr<GraphicsObject>>& objects) {
  std::vector<std::unique_ptr<GraphicsObject>> copy;

  for (const auto& obj : objects) {
    copy.push_back(obj->clone());
  }

  return copy;
}
void Diagram::saveState() {
    undoStack_.push(cloneObjects(objects_));
    while (!redoStack_.empty()) redoStack_.pop();
}
void Diagram::add(std::unique_ptr<GraphicsObject> obj) {
  saveState();
  objects_.push_back(std::move(obj));
}
const std::vector<std::unique_ptr<GraphicsObject>>&
Diagram::getObjects() const {
    return objects_;
}
void Diagram::remove(GraphicsObject* obj){
  saveState();
  objects_.erase(
      std::remove_if(objects_.begin(), objects_.end(),
        [obj](const std::unique_ptr<GraphicsObject>& ptr) {
        return ptr.get() == obj;
      }),
  objects_.end()
  );
}
void Diagram::clear() {
  saveState();
  objects_.clear();
}
std::string Diagram::toSVG() const {
  std::string svg = "<svg xmlns=\"http://www.w3.org/2000/svg\">\n";

  for (const auto& obj : objects_) {
    svg += obj->toSVG();
    svg += "\n";
  }

  svg += "</svg>";
  return svg;
}


void Diagram::undo() {
  if (undoStack_.empty()) return;

  redoStack_.push(cloneObjects(objects_));
  objects_ = std::move(undoStack_.top());
  undoStack_.pop();
}

void Diagram::redo() {
  if (redoStack_.empty()) return;

  undoStack_.push(cloneObjects(objects_));
  objects_ = std::move(redoStack_.top());
  redoStack_.pop();
}
void Diagram::resetHistory()
{
    while (!undoStack_.empty()) undoStack_.pop();
    while (!redoStack_.empty()) redoStack_.pop();
}

