#include "h/OBJParser.h"

void OBJParser::Parse(const std::string& fileName) {
    file.open(fileName);

    if (file.is_open()) {
        std::vector<Vec3> vertices;
        std::vector<Triangle> triangles;

        std::string line;
        while (std::getline(file, line)) {
            std::vector<std::string> lineParsed;

            // split line by space
            std::string delimiter = " ";
            size_t pos = 0;
            while ((pos = line.find(delimiter)) != std::string::npos) {
                lineParsed.push_back(line.substr(0, pos));
                line.erase(0, pos + delimiter.length());
            }
            lineParsed.push_back(line);

            // create the vertices and triangles vectors
            if (lineParsed.size() == 4) {
                if (lineParsed[0] == "v") {
                    vertices.push_back(
                        Vec3{
                            std::stod(lineParsed[1]),
                            std::stod(lineParsed[2]),
                            std::stod(lineParsed[3])
                        }
                    );
                }
                else if (lineParsed[0] == "f") {
                    triangles.push_back(
                        Triangle(
                            std::stoi(lineParsed[1]) - 1,
                            std::stod(lineParsed[2]) - 1,
                            std::stod(lineParsed[3]) - 1,
                            RGBA(200, 200, 200, 200)
                        )
                    );
                }
            }
        }

        Vertices = vertices;
        Triangles = triangles;
    }

    file.close();
}

std::ifstream OBJParser::file;
std::vector<Vec3> OBJParser::Vertices;
std::vector<Triangle> OBJParser::Triangles;


std::vector<Vec3> OBJParser::GetVertices() {
    return Vertices;
}
std::vector<Triangle> OBJParser::GetTriangles() {
    return Triangles;
}