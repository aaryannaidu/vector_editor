#include "svg/SVGwriter.h"
#include "fstream"

void SVGwriter::writeFile(const std::string& filename,const Diagram& diagram){
    std::ofstream file(filename);
    if (!file.is_open()) return;

    file << diagram.toSVG();
    file.close();
}