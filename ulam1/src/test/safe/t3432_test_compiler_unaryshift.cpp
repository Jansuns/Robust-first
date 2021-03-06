#include "TestCase_EndToEndCompiler.h"

namespace MFM {

  BEGINTESTCASECOMPILER(t3432_test_compiler_unaryshift)
  {
    std::string GetAnswerKey()
    {
      /* gen code output:
	 Unary(3) Arg: 0x2
	 Unary(3) Arg: 0x2
      */
      return std::string("Exit status: 0\nUe_A { System s();  Unary(3) u(2);  Unary(3) v(2);  Int(32) test() {  v 3u cast = u v cast cast 1 cast << cast = v v cast 1 cast >> cast = s ( u )print . s ( v )print . 0 cast return } }\nUq_System { <NOMAIN> }\n");
    }

    std::string PresetTest(FileManagerString * fms)
    {
      // cast to Bits and cast back to Unary(3): 3 >> 1 = 2   3 << 1 = 2
      //conversion to unsigned then shift then back to unary. so, 3 << 1 saturates at 3; 3 >> 1 = 1;
      bool rtn1 = fms->add("A.ulam","use System;\nelement A {\nSystem s;\nUnary(3) u, v;\n Int test() {\n v = 3u;\n u = (Unary(3)) (v << 1);\n v = (Unary(3)) (v >> 1);\n s.print(u);\n s.print(v);\n return 0;\n }\n }\n");

      // test system quark with native overloaded print funcs; assert
      bool rtn3 = fms->add("System.ulam", "ulam 1;\nquark System {\nVoid print(Unsigned arg) native;\nVoid print(Int arg) native;\nVoid print(Int(4) arg) native;\nVoid print(Int(3) arg) native;\nVoid print(Unary(3) arg) native;\nVoid print(Bool(3) arg) native;\nVoid assert(Bool b) native;\n}\n");

      if(rtn1 && rtn3)
	return std::string("A.ulam");

      return std::string("");
    }
  }

  ENDTESTCASECOMPILER(t3432_test_compiler_unaryshift)

} //end MFM
