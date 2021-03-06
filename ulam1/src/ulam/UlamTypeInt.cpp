#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include "UlamTypeInt.h"
#include "UlamValue.h"
#include "CompilerState.h"

namespace MFM {

  UlamTypeInt::UlamTypeInt(const UlamKeyTypeSignature key, CompilerState & state) : UlamType(key, state)
  {
    s32 bitsize = getBitSize();
    if(bitsize <= 0)
      {
	m_max = m_min = 0;
      }
    else if(bitsize <= MAXBITSPERINT)
      {
	m_wordLengthTotal = calcWordSize(getTotalBitSize());
	m_wordLengthItem = calcWordSize(bitsize);
	m_max = calcBitsizeSignedMax(bitsize);
	m_min = calcBitsizeSignedMin(bitsize);
      }
    else if(bitsize <= MAXBITSPERLONG)
      {
	m_wordLengthTotal = calcWordSizeLong(getTotalBitSize());
	m_wordLengthItem = calcWordSizeLong(bitsize);
	m_max = calcBitsizeSignedMaxLong(bitsize);
	m_min = calcBitsizeSignedMinLong(bitsize);
      }
    else
      assert(0);
  }

   ULAMTYPE UlamTypeInt::getUlamTypeEnum()
   {
     return Int;
   }

  bool UlamTypeInt::isNumericType()
  {
    return true;
  }

  bool UlamTypeInt::isPrimitiveType()
  {
    return true;
  }

  const std::string UlamTypeInt::getUlamTypeVDAsStringForC()
  {
    return "VD::S32";
  }

  bool UlamTypeInt::cast(UlamValue & val, UTI typidx)
  {
    bool brtn = true;
    assert(m_state.getUlamTypeByIndex(typidx) == this);
    UTI valtypidx = val.getUlamValueTypeIdx();

    if(UlamType::safeCast(valtypidx) != CAST_CLEAR) //bad|hazy
      return false;

    u32 wordsize = getTotalWordSize();
    u32 valwordsize = m_state.getTotalWordSize(valtypidx);
    if(wordsize == MAXBITSPERINT)
      {
	if(valwordsize == MAXBITSPERINT)
	  brtn = castTo32(val, typidx);
	else if(valwordsize == MAXBITSPERLONG)
	  brtn = castTo64(val, typidx); //downcast
	else
	  assert(0);
      }
    else if(wordsize == MAXBITSPERLONG)
      brtn = castTo64(val, typidx);
    else
      {
	std::ostringstream msg;
	msg << "Casting to an unsupported word size: " << wordsize;
	msg << ", Value Type and bit size was: ";
	msg << valtypidx << "," << m_state.getBitSize(valtypidx);
	msg << " TO: ";
	msg << typidx << "," << getBitSize();
	MSG(m_state.getFullLocationAsString(m_state.m_locOfNextLineText).c_str(), msg.str().c_str(), DEBUG);
	brtn = false;
      }
    return brtn;
  } //cast

  bool UlamTypeInt::castTo32(UlamValue & val, UTI typidx)
  {
    bool brtn = true;
    UTI valtypidx = val.getUlamValueTypeIdx();
    s32 bitsize = getBitSize();
    s32 valbitsize = m_state.getBitSize(valtypidx);

    u32 data = val.getImmediateData(m_state);
    u32 sdata = 0;
    ULAMTYPE valtypEnum = m_state.getUlamTypeByIndex(valtypidx)->getUlamTypeEnum();
    switch(valtypEnum)
      {
      case Int:
	// casting Int to Int to change bits size
	sdata = _Int32ToInt32(data, valbitsize, bitsize);
	break;
      case Unsigned:
	// casting Unsigned to Int to change type
	sdata = _Unsigned32ToInt32(data, valbitsize, bitsize);
	break;
      case Bits:
	// casting Bits to Int to change type
	sdata = _Bits32ToInt32(data, valbitsize, bitsize);
	break;
      case Unary:
	sdata = _Unary32ToInt32(data, valbitsize, bitsize);
	break;
      case Bool:
	sdata = _Bool32ToInt32(data, valbitsize, bitsize);
	break;
      case Void:
      default:
	//std::cerr << "UlamTypeInt (cast) error! Value Type was: " << valtypidx << std::endl;
	brtn = false;
      };

    if(brtn)
      val = UlamValue::makeImmediate(typidx, sdata, m_state); //overwrite val
    return brtn;
  } //castTo32

  bool UlamTypeInt::castTo64(UlamValue & val, UTI typidx)
  {
    bool brtn = true;
    UTI valtypidx = val.getUlamValueTypeIdx();
    u32 valwordsize = m_state.getTotalWordSize(valtypidx);
    u64 data;

    if(valwordsize == MAXBITSPERINT)
      data = (u64) val.getImmediateData(m_state);
    else if(valwordsize == MAXBITSPERLONG)
      data = val.getImmediateDataLong(m_state);
    else
      assert(0);

    u64 sdata = 0;
    s32 bitsize = getBitSize();
    s32 valbitsize = m_state.getBitSize(valtypidx);
    ULAMTYPE valtypEnum = m_state.getUlamTypeByIndex(valtypidx)->getUlamTypeEnum();
    switch(valtypEnum)
      {
      case Int:
	// casting Int to Int to change bits size
	sdata = _Int64ToInt64(data, valbitsize, bitsize);
	break;
      case Unsigned:
	// casting Unsigned to Int to change type
	sdata = _Unsigned64ToInt64(data, valbitsize, bitsize);
	break;
      case Bits:
	// casting Bits to Int to change type
	sdata = _Bits64ToInt64(data, valbitsize, bitsize);
	break;
      case Unary:
	sdata = _Unary64ToInt64(data, valbitsize, bitsize);
	break;
      case Bool:
	sdata = _Bool64ToInt64(data, valbitsize, bitsize);
	break;
      case Void:
      default:
	//std::cerr << "UlamTypeInt (cast) error! Value Type was: " << valtypidx << std::endl;
	brtn = false;
      };

    if(brtn)
      {
	u32 wordsize = getTotalWordSize(); //tobe
	if(wordsize == MAXBITSPERINT) //downcast
	  val = UlamValue::makeImmediate(typidx, (u32) sdata, m_state); //overwrite val
	else if(wordsize == MAXBITSPERLONG)
	  val = UlamValue::makeImmediateLong(typidx, sdata, m_state); //overwrite val
	else
	  assert(0);
      }
    return brtn;
  } //castTo64

  FORECAST UlamTypeInt::safeCast(UTI typidx)
  {
    FORECAST scr = UlamType::safeCast(typidx);
    if(scr != CAST_CLEAR)
      return scr;

    bool brtn = true;
    UlamType * vut = m_state.getUlamTypeByIndex(typidx);
    s32 valbitsize = m_state.getBitSize(typidx);
    s32 bitsize = getBitSize();
    ULAMTYPE valtypEnum = vut->getUlamTypeEnum();
    switch(valtypEnum)
      {
      case Int:
	brtn = (bitsize >= valbitsize);
	break;
      case Unsigned:
	brtn = (bitsize > valbitsize);
	break;
      case Unary:
	brtn = (bitsize > (s32) _getLogBase2(valbitsize) + 1);
	break;
      case Bool:
      case Bits:
      case Void:
      case UAtom:
	brtn = false;
	break;
      case Class:
	{
	  //must be Quark! treat as Int if it has a toInt method
	  if(vut->isNumericType())
	    brtn = (bitsize >= MAXBITSPERINT);
	  else
	    {
	      std::ostringstream msg;
	      msg << "Class: ";
	      msg << m_state.getUlamTypeNameBriefByIndex(typidx).c_str();
	      msg << " is not a numeric type and cannot be safely cast to an Int";
	      MSG(m_state.getFullLocationAsString(m_state.m_locOfNextLineText).c_str(),msg.str().c_str(), ERR);
	      brtn = false;
	    }
	}
	break;
      default:
	assert(0);
	//std::cerr << "UlamTypeInt (cast) error! Value Type was: " << valtypidx << std::endl;
	brtn = false;
      };
    return brtn ? CAST_CLEAR : CAST_BAD;
  } //safeCast

  void UlamTypeInt::getDataAsString(const u32 data, char * valstr, char prefix)
  {
    if(prefix == 'z')
      sprintf(valstr,"%d", data);
    else
      sprintf(valstr,"%c%d", prefix, data);
  }

  void UlamTypeInt::getDataLongAsString(const u64 data, char * valstr, char prefix)
  {
    if(prefix == 'z')
      sprintf(valstr,"%s", ToSignedDecimal(data).c_str());
    else
      sprintf(valstr,"%c%s", prefix, ToSignedDecimal(data).c_str());
  }

  s32 UlamTypeInt::getDataAsCs32(const u32 data)
  {
    return _Int32ToCs32(data, getBitSize());
  }

  u32 UlamTypeInt::getDataAsCu32(const u32 data)
  {
    s32 bitsize = getBitSize();
    assert(bitsize > 0);
    u32 cdata = _Int32ToUnsigned32(data, (u32) bitsize, (u32) bitsize);
    return _Unsigned32ToCu32(cdata, (u32) bitsize);
  }

  s64 UlamTypeInt::getDataAsCs64(const u64 data)
  {
    return _Int64ToCs64(data, getBitSize());
  }

  u64 UlamTypeInt::getDataAsCu64(const u64 data)
  {
    s32 bitsize = getBitSize();
    assert(bitsize > 0);
    u64 cdata = _Int64ToUnsigned64(data, (u32) bitsize, (u32) bitsize);
    return _Unsigned64ToCu64(cdata, (u32) bitsize);
  }

  s32 UlamTypeInt::bitsizeToConvertTypeTo(ULAMTYPE tobUT)
  {
    s32 bitsize = getBitSize();
    s32 tobitsize = UNKNOWNSIZE;
    s32 wordsize = getTotalWordSize();
    switch(tobUT)
      {
      case Unsigned:
	tobitsize = bitsize; //unsafe
	break;
      case Unary:
	tobitsize = getMax();
	break;
      case Bool:
	tobitsize = 1;
	break;
      case Int:
      case Bits:
	tobitsize = bitsize; //self
	break;
      case Void:
	tobitsize = 0;
	break;
      case UAtom:
      case Class:
	break;
      default:
	assert(0);
	//std::cerr << "UlamTypeInt (convertTo) error! " << tobUT << std::endl;
      };
    return (tobitsize > wordsize ? wordsize : tobitsize);
  } //bitsizeToConvertTypeTo

} //end MFM
