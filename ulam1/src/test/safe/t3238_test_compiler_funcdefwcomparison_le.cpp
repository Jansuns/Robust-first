#include "TestCase_EndToEndCompiler.h"

namespace MFM {

  BEGINTESTCASECOMPILER(t3238_test_compiler_funcdefwcomparison_le)
  {
    std::string GetAnswerKey()
    {
      /* gen code output:
	 Int Arg: 5
	 Int Arg: 10
	 Int Arg: 15
	 Int Arg: 20
	 Int Arg: 25
	 Int Arg: 25
      */

      return std::string("Exit status: 25\nUe_A { Bool(7) b(false);  Int(32) d(25);  System s();  Int(32) test() {  d ( 4 cast 5 cast )times = s ( d )print . d return } }\nUq_System { <NOMAIN> }\n");
    }

    std::string PresetTest(FileManagerString * fms)
    {
      // using ++e instead of e+=1
      bool rtn1 = fms->add("A.ulam","use System;\nelement A {\n Int times(Int m, Int n) {\nInt d,e;\n while(e <= m)\n{ d += n;\n ++e;\ns.print(d);\n}\n return d;\n }\nSystem s;\nBool(7) b;\nInt d;\nInt test(){ d = times(4,5);\ns.print(d);\nreturn d;\n }\n }\n");

      // test system quark with native overloaded print funcs; assert
      bool rtn3 = fms->add("System.ulam", "ulam 1;\nquark System {\nVoid print(Unsigned arg) native;\nVoid print(Int arg) native;\nVoid print(Int(4) arg) native;\nVoid print(Int(3) arg) native;\nVoid print(Unary(3) arg) native;\nVoid print(Bool(3) arg) native;\nVoid assert(Bool b) native;\n}\n");

      if(rtn1 && rtn3)
	return std::string("A.ulam");

      return std::string("");
    }
  }

  ENDTESTCASECOMPILER(t3238_test_compiler_funcdefwcomparison_le)

} //end MFM
