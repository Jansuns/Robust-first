/**                                        -*- mode:C++ -*-
 * NodeBinaryOp.h - Basic Node for handling Binary Operations for ULAM
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
  \file NodeBinaryOp.h - Basic Node for handling Binary Operations for ULAM
  \author Elenas S. Ackley.
  \author David H. Ackley.
  \date (C) 2014 All rights reserved.
  \gpl
*/

#ifndef NODEBINARYOP_H
#define NODEBINARYOP_H

#include "Node.h"
#include "NodeCast.h"

namespace MFM{

  class NodeBinaryOp : public Node
  {
  public:
    
    NodeBinaryOp(Node * left, Node * right, CompilerState & state);
    ~NodeBinaryOp();

    virtual void print(File * fp);

    virtual void printPostfix(File * fp);

    virtual void printOp(File * fp);

    virtual EvalStatus eval();

    virtual void genCode(File * fp);

  protected:

    Node * m_nodeLeft;
    Node * m_nodeRight;

    UlamType * calcNodeType(UlamType * lt, UlamType * rt);
    UlamType * calcNodeTypeBitwise(UlamType * lt, UlamType * rt);

    virtual void doBinaryOperation(s32 lslot, s32 rslot, u32 slots) = 0;

  };

}

#endif //end NODEBINARYOP_H