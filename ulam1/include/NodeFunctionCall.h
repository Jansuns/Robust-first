/**                                        -*- mode:C++ -*-
 * NodeFunctionCall.h - Basic Node for handling Function Calls for ULAM
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
  \file NodeFunctionCall.h - Basic Node for handling Function Calls for ULAM
  \author Elenas S. Ackley.
  \author David H. Ackley.
  \date (C) 2014 All rights reserved.
  \gpl
*/


#ifndef NODEFUNCTIONCALL_H
#define NODEFUNCTIONCALL_H

#include <vector>
#include "Node.h"
#include "Token.h"
#include "SymbolFunction.h"

namespace MFM{

  class NodeFunctionCall : public Node
  {
  public:
    
    NodeFunctionCall(Token fname, SymbolFunction * fsym, CompilerState & state);
    ~NodeFunctionCall();

    virtual void printPostfix(File * fp);

    virtual UlamType * checkAndLabelType();

    virtual EvalStatus eval();

    void addArgument(Node * n);

    u32 getNumberOfArguments();

    virtual const char * getName();

    virtual const std::string prettyNodeName();

    virtual void genCode(File * fp);

  private:

    Token m_functionNameTok;
    SymbolFunction * m_funcSymbol;
    std::vector<Node *> m_argumentNodes;

  };

}

#endif //end NODEFUNCTIONCALL_H