/**                                        -*- mode:C++ -*-
 * SymbolVariable.h -  Basic handling of Variable Symbols for ULAM
 *
 * Copyright (C) 2014 The Regents of the University of New Mexico.
 * Copyright (C) 2014 Ackleyshack LLC.
 *
 * This file is part of the ULAM programming language compilation system.
 *
 * The ULAM programming language compilation system is free software:
 * you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * The ULAM programming language compilation system is distributed in
 * the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the ULAM programming language compilation system
 * software.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>
 */

/**
  \file SymbolVariable.h -  Basic handling of Variable Symbols for ULAM
  \author Elenas S. Ackley.
  \author David H. Ackley.
  \date (C) 2014 All rights reserved.
  \gpl
*/

#ifndef SYMBOLVARIABLE_H
#define SYMBOLVARIABLE_H

#include "UlamValue.h"
#include "Symbol.h"

namespace MFM{

  class CompilerState;  //forward

  //distinguish between SymbolFunction
  class SymbolVariable : public Symbol
  {
  public:
    SymbolVariable(u32 id, UlamType * utype);
    ~SymbolVariable();

    virtual s32 getStackFrameSlotIndex();
    virtual u32 getDataMemberSlotIndex();

    virtual UlamValue getUlamValue(CompilerState & m_state) = 0;
    virtual UlamValue getUlamValueToStoreInto() = 0;
    virtual UlamValue getUlamValueAt(s32 idx, CompilerState& m_state) = 0;
    virtual UlamValue getUlamValueAtToStoreInto(s32 idx, CompilerState& state) = 0;
    virtual s32 getBaseArrayIndex() = 0;

  protected:

  private:
    virtual UlamValue makeUlamValuePtr() = 0;
    virtual UlamValue makeUlamValuePtrAt(u32 idx, CompilerState& state) = 0;
  };

}

#endif //end SYMBOLVARIABLE_H