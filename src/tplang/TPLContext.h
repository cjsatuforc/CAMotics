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

#pragma once


#include "GCodeModule.h"
#include "MatrixModule.h"
#include "DXFModule.h"
#include "ClipperModule.h"
#include "STLModule.h"

#include <gcode/machine/MachineAdapter.h>

#include <cbang/js/Javascript.h>
#include <cbang/config/Options.h>
#include <cbang/json/Value.h>


namespace tplang {
  class TPLContext : public cb::js::Javascript {
    GCodeModule gcodeMod;
    MatrixModule matrixMod;
    ClipperModule clipperMod;
    DXFModule dxfMod;
    STLModule stlMod;

  public:
    GCode::MachineInterface &machine;
    cb::JSON::ValuePtr sim;

    TPLContext(const cb::SmartPointer<std::ostream> &stream,
               GCode::MachineInterface &machine,
               const std::string &jsImpl = std::string());

    template <typename T>
    T &find() {
      GCode::MachineAdapter *adapter =
        dynamic_cast<GCode::MachineAdapter *>(&machine);
      if (!adapter) THROW("Not found");
      return adapter->find<T>();
    }

    // From cb::js::Javascript
    void pushPath(const std::string &path);
    void popPath();
  };
}
