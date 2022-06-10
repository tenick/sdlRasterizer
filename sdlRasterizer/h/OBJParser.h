#ifndef OBJPARSER_H
#define OBJPARSER_H
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <h/Vec3.h>
#include <h/Triangle.h>

class OBJParser {
    static std::ifstream file;
    static std::vector<Vec3> Vertices;
    static std::vector<Triangle> Triangles;
public:
    static void Parse(const std::string& fileName);

    static std::vector<Vec3> GetVertices();
    static std::vector<Triangle> GetTriangles();
};

#endif

