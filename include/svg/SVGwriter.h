// export current Diagram into SVG file
#ifndef SVG_WRITER_H
#define SVG_WRITER_H

#include <string>
#include "model/Diagram.h"

class SVGwriter{
    public:
        static void writeFile(const std::string &filename,const Diagram& diagram);
};
#endif
