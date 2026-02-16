// Responsible for reading an SVG file and converting it into internal Diagram objects.

#ifndef SVG_PARSER_H
#define SVG_PARSER_H

#include <string>
#include "model/Diagram.h"

class SVGparser{
    public:
        static Diagram parseFile(const std::string& filename);
};

#endif