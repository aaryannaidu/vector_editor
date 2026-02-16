// Helper funtion used by SVGparser
// EXtract int and string attribute from lines
// Apply Comman style (stroke,fill,stroke-width) to GraphicObject instance
#ifndef SVG_PARSER_UTILS_H
#define SVG_PARSER_UTILS_H
#include <string>
#include <QColor>
#include "model/GraphicsObject.h"

int getIntAttr(const std::string& line, const std::string& key);
std::string getStringAttr(const std::string& line, const std::string& key);
void Commanapply(GraphicsObject* obj, const std::string& line);

#endif