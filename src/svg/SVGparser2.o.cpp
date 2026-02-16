#include "svg/SVGparser2.o.h"
#include <QString>

int getIntAttr(const std::string& line, const std::string& key) {
    std::size_t pos=line.find(key+"=\"");
    if (pos== std::string::npos) return 0;
    pos += key.length() + 2;
    std::size_t end=line.find("\"", pos);
    return std::stoi(line.substr(pos, end - pos));
}
std::string getStringAttr(const std::string& line, const std::string& key) {
    std::size_t pos= line.find(key + "=\"");
    if (pos== std::string::npos) return "";
    pos += key.length() + 2;
    std::size_t end= line.find("\"", pos);
    return line.substr(pos,end - pos);
}

void Commanapply(GraphicsObject* obj, const std::string& line) {
    std::string stroke = getStringAttr(line, "stroke");
    std::string fill = getStringAttr(line, "fill");
    int strokeWidth = getIntAttr(line, "stroke-width");
    if (!stroke.empty())
        obj->setStrokeColor(QColor(QString::fromStdString(stroke)));
    if (!fill.empty()) {
        if (fill == "none") obj->setFillColor(Qt::transparent);
        else obj->setFillColor(QColor(QString::fromStdString(fill)));
    }
    if (strokeWidth > 0)
        obj->setStrokeWidth(strokeWidth);
}