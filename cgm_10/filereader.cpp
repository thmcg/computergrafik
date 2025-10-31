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

#include "filereader.h"

FileReader::FileReader(const std::string &filename)
{
    fileStream.open(filename);
}

FileReader::~FileReader()
{
    fileStream.close();
}

bool FileReader::hasLine()
{
    std::string lineBuffer;
    if (getline(fileStream, lineBuffer))
    {
        lineStream.clear();
        lineStream.str(lineBuffer);
        return true;
    }
    lineStream.clear();
    fileStream.close();
    return false;
}

std::string FileReader::getString()
{
    std::string str;
    lineStream >> str;
    return str;
}

double FileReader::getDouble()
{
    std::string p1;
    lineStream >> p1;
    return stod(p1);
}

Vector2 FileReader::getVector2()
{
    std::string p1, p2;
    lineStream >> p1 >> p2;
    return (Vector2){stod(p1), stod(p2)};
}

Vector3 FileReader::getVector3()
{
    std::string p1, p2, p3;
    lineStream >> p1 >> p2 >> p3;
    return (Vector3){stod(p1), stod(p2), stod(p3)};
}
