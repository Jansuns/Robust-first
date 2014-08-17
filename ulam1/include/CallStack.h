/**                                        -*- mode:C++ -*-
 * callStack.h - Basic Call Stack handling for ULAM
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
  \file CallStack.h - Basic Call Stack handling for ULAM
  \author Elenas S. Ackley.
  \author David H. Ackley.
  \date (C) 2014 All rights reserved.
  \gpl
*/

#ifndef CALLSTACK_H
#define CALLSTACK_H

#include <stdio.h>
#include <vector>
#include "itype.h"
#include "UlamValue.h"
#include "UlamType.h"

namespace MFM
{

  class CompilerState; //forward

  class CallStack
  {
  public:

    CallStack();
    ~CallStack();

    void init(UlamType * intType);

    //returns new "zero"
    u32 addFrameSlots(u32 depth);

    u32 returnFrame();

    u32 getCurrentFramePointer();

    u32 getRelativeTopOfStackNextSlot();

    UlamValue getFrameSlotAt(s32 idx);

    UlamValue * getPointerToFrameSlotAt(s32 idx); //dangerous, pointer can get reallocated by vector

    u32 getAbsoluteIndexToFrameSlotAt(s32 idx);

    UlamValue getAbsoluteSlotAt(u32 idx);

    void assignUlamValue(UlamValue luv, UlamValue ruv, CompilerState & state);
    void assignUlamValuePtr(UlamValue pluv, UlamValue puv, CompilerState & state);

    //returns number of ulamvalues pushed; one per array element, o.w. 1
    u32 pushArg(UlamValue arg, CompilerState & state);   //doesn't change framepointer

    void popArgs(u32 num);        //doesn't change framepointer

    UlamValue popArg();                //doesn't change framepointer

    UlamValue loadUlamValueFromSlot(s32 slot);
    void storeUlamValueInSlot(UlamValue uv, s32 slot);

  private: 
    std::vector<UlamValue> m_frames;  
    u32 m_currentFrame;
    UlamType * m_intType;

  };
}

#endif  /* CALLSTACK_H */