#include <iostream>
#include <stdio.h>
#include <string.h>
#include "UlamTypeVoid.h"
#include "UlamValue.h"
#include "CompilerState.h"

namespace MFM {

  UlamTypeVoid::UlamTypeVoid(const UlamKeyTypeSignature key, CompilerState & state) : UlamType(key, state)
  {}

   ULAMTYPE UlamTypeVoid::getUlamTypeEnum()
   {
     return Void;
   }

  bool UlamTypeVoid::isPrimitiveType()
  {
    return true;
  }

  const std::string UlamTypeVoid::getUlamTypeAsStringForC()
  {
    return "void";
  }

  const std::string UlamTypeVoid::getUlamTypeMangledName()
  {
    return "void";
  }

  const std::string UlamTypeVoid::getUlamTypeImmediateMangledName()
  {
    return getImmediateStorageTypeAsString(); //"void";
  }

  bool UlamTypeVoid::needsImmediateType()
  {
    return false;
  }

  const std::string UlamTypeVoid::getImmediateStorageTypeAsString()
  {
    return "void";
  }

  void UlamTypeVoid::genUlamTypeMangledImmediateModelParameterDefinitionForC(File * fp)
  {
    assert(0); //only primitive types
  }

  const std::string UlamTypeVoid::getTmpStorageTypeAsString()
  {
    return "void";
  }

  bool UlamTypeVoid::isMinMaxAllowed()
  {
    return false;
  }

  //anything can be cast to a void (not the reverse)
  bool UlamTypeVoid::cast(UlamValue & val, UTI typidx)
  {
    bool brtn = true;
    UTI valtypidx = val.getUlamValueTypeIdx();

    if(UlamType::safeCast(valtypidx) != CAST_CLEAR) //bad|hazy
      return false;

    ULAMTYPE valtypEnum = m_state.getUlamTypeByIndex(valtypidx)->getUlamTypeEnum();
    switch(valtypEnum)
      {
      case Void:
      case Int:
      case Unsigned:
      case Unary:
      case Bool:
      case Bits:
      case UAtom:
      case Class:
	val = UlamValue::makeImmediate(typidx, 0, m_state); //overwrite val, no data
	break;
      default:
	//std::cerr << "UlamTypeVoid (cast) error! Value Type was: " << valtypidx << std::endl;
	brtn = false;
      };

    return brtn;
  } //end cast

  FORECAST UlamTypeVoid::safeCast(UTI typidx)
  {
    FORECAST scr = UlamType::safeCast(typidx);
    if(scr != CAST_CLEAR)
      return scr;

    bool brtn = true;
    UlamType * vut = m_state.getUlamTypeByIndex(typidx);
    ULAMTYPE valtypEnum = vut->getUlamTypeEnum();
    switch(valtypEnum)
      {
      case Void:
      case Unsigned:
      case Unary:
      case Int:
      case Bool:
      case Bits:
      case UAtom:
      case Class:
	brtn = true; //anything casts to void ok
	break;
      default:
	assert(0);
	//std::cerr << "UlamTypeVoid (cast) error! Value Type was: " << valtypidx << std::endl;
	brtn = false;
      };
    return brtn ? CAST_CLEAR : CAST_BAD;
  } //safeCast

  s32 UlamTypeVoid::bitsizeToConvertTypeTo(ULAMTYPE tobUT)
  {
    u32 tobitsize = UNKNOWNSIZE;
    switch(tobUT)
      {
      case Bool:
      case Unsigned:
      case Unary:
      case Int:
      case Bits:
	break;
      case Void:
	tobitsize = 0;
	break;
      case UAtom:
      case Class:
	break;
      default:
	assert(0);
	//std::cerr << "UlamTypeVoid (convertTo) error! " << tobUT << std::endl;
      };
    return tobitsize;
  } //bitsizeToConvertTypeTo

} //end MFM
