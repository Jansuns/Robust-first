/**                                        -*- mode:C++ -*-
 * NodeIdent.h - Node handling Identifiers for ULAM
 *
 * Copyright (C) 2014-2015 The Regents of the University of New Mexico.
 * Copyright (C) 2014-2015 Ackleyshack LLC.
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
  \file NodeIdent.h - Node handling Identifiers for ULAM
  \author Elenas S. Ackley.
  \author David H. Ackley.
  \date (C) 2014-2015 All rights reserved.
  \gpl
*/


#ifndef NODEIDENT_H
#define NODEIDENT_H

#include "Node.h"
#include "Token.h"
#include "SymbolVariable.h"
#include "UlamType.h"

namespace MFM{

  class NodeIdent : public Node
  {
  public:

    NodeIdent(Token tok, SymbolVariable * symptr, CompilerState & state);
    ~NodeIdent();

    virtual void printPostfix(File * fp);

    virtual const char * getName();

    virtual const std::string prettyNodeName();

    virtual bool getSymbolPtr(Symbol *& symptrref);

    virtual UTI checkAndLabelType();

    virtual EvalStatus eval();

    virtual EvalStatus evalToStoreInto();

    virtual bool installSymbolTypedef(Token atok, s32 bitsize, s32 arraysize, UTI classInstanceIdx, Symbol *& asymptr);

    virtual bool installSymbolConstantValue(Token atok, s32 bitsize, s32 arraysize, Symbol *& asymptr);

    virtual bool installSymbolVariable(Token atok, s32 bitsize, s32 arraysize, UTI classInstanceIdx, Symbol *& asymptr);

    virtual void genCode(File * fp, UlamValue& uvpass);

    virtual void genCodeToStoreInto(File * fp, UlamValue& uvpass);

    virtual void genCodeReadIntoATmpVar(File * fp, UlamValue & uvpass);

  private:
    Token m_token;
    SymbolVariable * m_varSymbol;

    SymbolVariable *  makeSymbol(UTI aut);
    UlamValue makeUlamValuePtr();
    UlamValue makeUlamValuePtrForCodeGen();
  };

}

#endif //end NODEIDENT_H
