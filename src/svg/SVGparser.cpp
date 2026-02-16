#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <QColor>
#include <QString>

#include "svg/SVGparser.h"
#include "svg/SVGparser2.o.h"
#include "model/Circle.h"
#include "model/Rectangle.h"
#include "model/RoundedRectangle.h"
#include "model/Line.h"
#include "model/Text.h"
#include "model/Hexagon.h"
#include "model/FreeHand.h"


Diagram SVGparser::parseFile(const std::string& filename) {

    Diagram diagram;
    std::ifstream file(filename); //open SVG
    if (!file) return diagram;
    std::string line;

    while (std::getline(file, line)) { // read file line by line 
        //  if _ else for all shape 
        if (line.find("<circle")!= std::string::npos) {
            int cx= getIntAttr(line,"cx");
            int cy= getIntAttr(line,"cy");
            int r= getIntAttr(line,"r");
            auto circle = std::make_unique<Circle>(cx, cy, r);
            Commanapply(circle.get(),line);
            diagram.add(std::move(circle));
        }
        else if (line.find("<rect")!=std::string::npos) {
            int x= getIntAttr(line,"x");
            int y= getIntAttr(line,"y");
            int w= getIntAttr(line,"width");
            int h= getIntAttr(line,"height");
            if (line.find("rx=\"")!= std::string::npos) {
                int r = getIntAttr(line,"rx");
                auto rounded = std::make_unique<RoundedRectangle>(x, y, w, h, r);
                Commanapply(rounded.get(),line);
                diagram.add(std::move(rounded));
            } else {
                auto rect = std::make_unique<Rectangle>(x, y, w, h);
                Commanapply(rect.get(),line);
                diagram.add(std::move(rect));
            }
        }
        else if (line.find("<line") != std::string::npos) {
            int x1= getIntAttr(line,"x1");
            int y1= getIntAttr(line,"y1");
            int x2= getIntAttr(line,"x2");
            int y2= getIntAttr(line,"y2");
            auto lineObj = std::make_unique<Line>(x1, y1, x2, y2);
            Commanapply(lineObj.get(),line);
            diagram.add(std::move(lineObj));
        }
        else if (line.find("<text")!= std::string::npos) {
            int x= getIntAttr(line,"x");
            int y= getIntAttr(line,"y");
            std::size_t start= line.find(">");
            std::size_t end= line.find("</text>");
            if (start!= std::string::npos && end!= std::string::npos) {
                std::string content= line.substr(start + 1, end - start - 1);
                auto textobj = std::make_unique<Text>(x, y, content);
                std::size_t fillPos = line.find("fill=\"");
                if (fillPos != std::string::npos) {
                    fillPos += 6;
                    std::size_t fillEnd = line.find("\"", fillPos);
                    std::string colorStr = line.substr(fillPos, fillEnd - fillPos);
                    textobj->setFillColor(QColor(QString::fromStdString(colorStr)));
                }
                diagram.add(std::move(textobj));
            }
        }
        else if (line.find("<polygon")!= std::string::npos) {
            std::size_t pos= line.find("points=\"");
            if (pos== std::string::npos) continue;
            pos+= 8;
            std::size_t end= line.find("\"", pos);
            std::string pts= line.substr(pos, end - pos);
            std::stringstream ss(pts);
            std::string token;
            std::vector<std::pair<int,int>> points;

            while (ss >> token) {
                std::size_t comma= token.find(",");
                if (comma== std::string::npos) continue;
                int px= std::stoi(token.substr(0, comma));
                int py= std::stoi(token.substr(comma + 1));
                points.emplace_back(px, py);
            }
            if (!points.empty()) {
                int sumx=0, sumy=0;
                for (const auto& p : points) {
                    sumx += p.first;
                    sumy += p.second;
                }
                int cx= sumx / points.size();
                int cy= sumy / points.size();
                int dx= points[0].first - cx;
                int dy= points[0].second - cy;
                int r= static_cast<int>(std::sqrt(dx*dx + dy*dy));
                auto hex = std::make_unique<Hexagon>(cx, cy, r);
                Commanapply(hex.get(),line);
                diagram.add(std::move(hex));
            }
        }
        else if (line.find("<polyline")!= std::string::npos) {
            std::size_t pos= line.find("points=\"");
            if (pos== std::string::npos) continue;
            pos += 8;
            std::size_t end= line.find("\"", pos);
            std::string pts= line.substr(pos, end - pos);
            std::stringstream ss(pts);
            std::string token;
            std::vector<std::pair<int,int>> points;
            while (ss >> token) {
                std::size_t comma= token.find(",");
                if (comma== std::string::npos) continue;
                int px= std::stoi(token.substr(0, comma));
                int py= std::stoi(token.substr(comma + 1));
                points.emplace_back(px, py);
            }
            if (!points.empty()) {
                auto free = std::make_unique<FreeHand>(points);
                std::string stroke= getStringAttr(line, "stroke");
                int strokeWidth= getIntAttr(line, "stroke-width");
                if (!stroke.empty())
                    free->setStrokeColor(QColor(QString::fromStdString(stroke)));
                if (strokeWidth > 0)
                    free->setStrokeWidth(strokeWidth);
                diagram.add(std::move(free));
            }
        }
    }

    return diagram;
}