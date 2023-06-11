#include <iostream>
#include <fstream>

const std::string testRect = "R 10 20 30 40", testCirc = "C 30 40 20";

// TODO
    // write shape and points to XML template file
        // move file pointer to location where the svg elements must be added
            // overwrite "<!-- shapes from the input to be added here -->"

const int domainWidth = 600, domainHeight = 500;


const std::string makeShape()
{
    std::string svgStr;
    char shapeType;
    std::cin >> shapeType;

    switch (shapeType)
    {
        case 'R':
        {
            std::string rectX, rectY, rectWidth, rectHeight;
            std::cin >> rectX >> rectY >> rectWidth >> rectHeight;

            svgStr = R"(<rect x=")" + rectX + R"(" y=")" + rectY + R"(" width=")" + rectWidth
                    + R"(" height=")" + rectHeight + R"("/>)";
            break;
        }
        case 'C':
        {
            std::string circX, circY, circRadius;
            std::cin >> circX >> circY >> circRadius;

            svgStr = R"(<circle cx=")" + circX + R"(" cy=")" +circY + R"(" r=")" + circRadius + R"("/>)";
            break;
        }

    }
    return svgStr;
}

template <typename...S>
void makeSVGWithShapes(S&... shapeStr)
{
    std::string line;
    std::ifstream fin; fin.open("/Users/lowerschoolmusic/svgTest/template.svg");
    std::ofstream fout("SVGShapes.svg");

    if (fin.is_open() && fout.is_open())
    {
        while (getline(fin, line))
        {
            if (line.substr(0, 4) == "<!--")
            {
                line.clear();

                for (const auto& sh : {shapeStr...})
                    line += sh + '\n';

                line.erase(--line.end());
            }
            fout << line + '\n';
        }
    }
    fin.close(); fout.close();
}

int main()
{

    makeSVGWithShapes(makeShape(), makeShape());



    return 0;
}