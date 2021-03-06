/******************************************************************************\

    CAMotics is an Open-Source simulation and CAM software.
    Copyright (C) 2011-2017 Joseph Coffland <joseph@cauldrondevelopment.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

\******************************************************************************/

#include "Axes.h"

#include <limits>
#include <cmath>

using namespace std;
using namespace cb;
using namespace GCode;


const char *Axes::AXES = "XYZABCUVW";


void Axes::applyXYZMatrix(const Matrix4x4D &m) {
  Vector4D v(m * Vector4D(getX(), getY(), getZ(), 1));
  setXYZ(v[0], v[1], v[2]);
}


void Axes::applyABCMatrix(const Matrix4x4D &m) {
  Vector4D v(m * Vector4D(getA(), getB(), getC(), 1));
  setABC(v[0], v[1], v[2]);
}


void Axes::applyUVWMatrix(const Matrix4x4D &m) {
  Vector4D v(m * Vector4D(getU(), getV(), getW(), 1));
  setUVW(v[0], v[1], v[2]);
}


void Axes::read(const JSON::Value &value) {
  for (unsigned i = 0; i < 9; i++)
    if (value.has(toAxisName(i)))
      data[i] = value.getNumber(toAxisName(i));

    else if (value.has(toAxisName(i, true)))
      data[i] = value.getNumber(toAxisName(i, true));
}


void Axes::write(JSON::Sink &sink) const {
  sink.beginDict(true);

  for (unsigned i = 0; i < 9; i++)
    if (!isnan(data[i]))
      sink.insert(string(1, AXES[i]), data[i]);

  sink.endDict();
}
