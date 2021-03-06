/**                                        -*- mode:C++ -*-
 * NodeBinaryOpShift.h - Basic Node for handling Bitwise Shift Operations for ULAM
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
  \file NodeBinaryOpShift.h - Basic Node for handling Bitwise Shift Operations for ULAM
  \author Elenas S. Ackley.
  \author David H. Ackley.
  \date (C) 2014-2015 All rights reserved.
  \gpl
*/

#ifndef NODEBINARYOPSHIFT_H
#define NODEBINARYOPSHIFT_H

#include <assert.h>
#include "NodeBinaryOp.h"
#include "NodeCast.h"

namespace MFM{

  class NodeBinaryOpShift : public NodeBinaryOp
  {
  public:

    NodeBinaryOpShift(Node * left, Node * right, CompilerState & state);

    NodeBinaryOpShift(const NodeBinaryOpShift& ref);

    virtual ~NodeBinaryOpShift();

    virtual UTI checkAndLabelType();

    virtual const std::string methodNameForCodeGen();

  protected:
    virtual bool doBinaryOperation(s32 lslot, s32 rslot, u32 slots);

    virtual UTI calcNodeType(UTI lt, UTI rt);

    virtual s32 resultBitsize(UTI lt, UTI rt) = 0;
  };

}

#endif //NODEBINARYOPSHIFT_H
