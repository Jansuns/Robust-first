/**                                        -*- mode:C++ -*-
 * Symbol.h -  Basic handling of Symbols for ULAM
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
  \file Symbol.h -  Basic handling of Symbols for ULAM
  \author Elenas S. Ackley.
  \author David H. Ackley.
  \date (C) 2014 All rights reserved.
  \gpl
*/


#ifndef SYMBOL_H
#define SYMBOL_H

#include "itype.h"
#include "Token.h"
#include "UlamType.h"

namespace MFM{

  class Symbol
  {
  public:
    Symbol(u32 id, UlamType * utype);
    virtual ~Symbol();    //abstract

    UlamType * getUlamType();
    u32 getId();
    
    virtual bool isFunction();
    virtual bool isTypedef();
    
    void setDataMember();
    bool isDataMember();

  protected:

  private:
    u32 m_id;            // id to its name (string) in lexer; also in ST
    UlamType * m_utype;  // may seem redundant, but not; from NodeVarDecl, before m_value known.
                         // base type, not array type, used here (e.g. NodeBinaryOp::calcNodeType)
    bool m_dataMember;
  };

}

#endif //end SYMBOL_H