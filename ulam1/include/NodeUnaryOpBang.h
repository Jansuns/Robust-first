/**                                        -*- mode:C++ -*-
 * NodeUnaryOpBang.h -  Node handling Unary Bang Operator for ULAM
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
  \file NodeUnaryOpBang.h -  Node handling Unary Bang Operator for ULAM
  \author Elenas S. Ackley.
  \author David H. Ackley.
  \date (C) 2014 All rights reserved.
  \gpl
*/


#ifndef NODEUNARYOPBANG_H
#define NODEUNARYOPBANG_H

#include "NodeUnaryOp.h"

namespace MFM{

  class NodeUnaryOpBang : public NodeUnaryOp
  {
  public:
    
    NodeUnaryOpBang(Node * n, CompilerState & state);
    ~NodeUnaryOpBang();

    virtual UTI checkAndLabelType();

    virtual const char * getName();

    virtual const std::string prettyNodeName();

  protected:
    virtual UlamValue makeImmediateUnaryOp(UTI type, u32 data, u32 len);

  private:
   

  };

}

#endif //end NODEUNARYOP_H
