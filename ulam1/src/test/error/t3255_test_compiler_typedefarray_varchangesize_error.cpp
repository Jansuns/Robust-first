#include "TestCase_EndToEndCompiler.h"

namespace MFM {

  BEGINTESTCASECOMPILER(t3255_test_compiler_typedefarray_varchangesize_error)
  {
    std::string GetAnswerKey()
    {
      //./B.ulam:9:9: ERROR: Arraysize [] is included in typedef: <IArray>, and cannot be redefined by variable: <arr>.
      //./B.ulam:9:2: ERROR: Invalid variable declaration of base type: <Unsigned> and Name: <arr> (missing symbol).

      return std::string("Ue_B { Bool(7) b(false);  System s();  typedef Unsigned(8) Index;  typedef Unsigned(8) NIdx;  typedef Unsigned(8) IndArr[4];  typedef Unsigned(8) IArray[4];  IArray(8) arr[4](1,0,0,0);  Int(32) test() {  arr 0 [] 1 cast = arr 0 [] cast 0 cast == cast return } }\nExit status: 0");
    }

    std::string PresetTest(FileManagerString * fms)
    {
      // with renames of typedefs, and arrays based on typedef
      // can't change/state array size when declaring variable with array typedef
      bool rtn1 = fms->add("B.ulam","use System;\nelement B {\nSystem s;\nBool(7) b;\ntypedef Unsigned(8) Index;\ntypedef Index NIdx;\ntypedef NIdx IndArr[4];\ntypedef IndArr IArray;\n IArray arr[2];\n Int test(){ arr[0] = 1;\n return arr[0] == 0;\n }\n }\n");

      // test system quark with native overloaded print funcs; assert
      bool rtn3 = fms->add("System.ulam", "ulam 1;\nquark System {\nVoid print(Unsigned arg) native;\nVoid print(Int arg) native;\nVoid print(Int(4) arg) native;\nVoid print(Int(3) arg) native;\nVoid print(Unary(3) arg) native;\nVoid print(Bool(3) arg) native;\nVoid assert(Bool b) native;\n}\n");

      if(rtn1 && rtn3)
	return std::string("B.ulam");

      return std::string("");
    }
  }

  ENDTESTCASECOMPILER(t3255_test_compiler_typedefarray_varchangesize_error)

} //end MFM
