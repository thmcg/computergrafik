/**
 * Computergrafik
 * Copyright © 2021-2025 Tobias Reimann
 * Copyright © 2024 Lukas Scheurer: Rewritten in modern C++
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "mesh.h"

#include "cgmath.h"
#include "filereader.h"

#include <glad/glad.h>

Mesh::Mesh(const std::vector<Vertex> &vertices)
    : vertices(vertices)
{
    init();
}

Mesh::Mesh(const std::string &filename)
{
    std::vector<Vector3> v;
    std::vector<Vector2> vt;
    std::vector<Vector3> vn;
    std::vector<std::string> f;

    FileReader reader(filename);
    while (reader.hasLine())
    {
        std::string type = reader.getString();
        if (type == "v")
        {
            v.push_back(reader.getVector3());
        }
        else if (type == "vt")
        {
            vt.push_back(reader.getVector2());
        }
        else if (type == "vn")
        {
            vn.push_back(reader.getVector3());
        }
        else if (type == "f")
        {
            for (int i = 0; i < 3; i++)
            {
                f.push_back(reader.getString());
            }
        }
    }

    vertices.reserve(v.size());
    for (int i = 0; i < f.size(); i++)
    {
        std::stringstream stream(f[i]);
        std::string item;
        std::vector<int> values;
        while (getline(stream, item, '/'))
        {
            values.push_back(stoi(item) - 1);
        }
        vertices.emplace_back(v[values[0]], vt[values[1]]);
    }
    init();
}

void Mesh::init()
{
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(1);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &vaoID);
    glDeleteBuffers(1, &vboID);
}

void Mesh::draw()
{
    glBindVertexArray(vaoID);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}