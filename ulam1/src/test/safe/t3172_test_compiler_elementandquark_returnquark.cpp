#include "TestCase_EndToEndCompiler.h"

namespace MFM {

  BEGINTESTCASECOMPILER(t3172_test_compiler_elementandquark_returnquark)
  {
    std::string GetAnswerKey()
    {
      /*
	gen code output:
	Unsigned Arg: 15
      */

      return std::string("Exit status: 15\nUe_Foo { System s();  typedef Bar Pop[2];  Unsigned(4) m_i(0);  Bar m_bar[2]( Bool(1) val_b[3](false,false,false);  Bool(1) val_b[3](false,true,false); );  Int(32) test() {  Foo f;  f m_i . 15 cast = m_bar 1 [] f ( 1 cast )check . = s ( f m_i . cast )print . f m_i . cast return } }\nUq_System { <NOMAIN> }\nUq_Bar { Bool(1) val_b[3](false,false,false);  <NOMAIN> }\n");
    }

    std::string PresetTest(FileManagerString * fms)
    {
      // array of quarks, as typedef
      //modified gencode to allow quarks as return values, and parameters.
      bool rtn1 = fms->add("Foo.ulam","ulam 1;\nuse System;\n use Bar;\n element Foo {\nSystem s;\n typedef Bar Pop[2];\n Unsigned(4) m_i;\n Pop m_bar;\n Bar check(Int v) {\n Bar b;\n b.val_b[1] = true;\n return b;\n }\n Int test() {\n Foo f;\n f.m_i = 15;\n m_bar[1] = f.check(1);\ns.print((Unsigned) f.m_i);\n return f.m_i;\n }\n }\n"); //tests offsets, but too complicated data members in Foo for memberselect

      // simplify to DEBUG:
      //bool rtn1 = fms->add("Foo.ulam","ulam 1;\nuse Bar;\n element Foo {\n typedef Bar Pop[2];\n Pop m_bar;\n Int test() {\n Bar b;\n m_bar[1] = b;\n return 0;\n }\n }\n");

      // singleton quark
      //bool rtn1 = fms->add("Foo.ulam","ulam 1; use Bar; element Foo { Int(4) m_i; Bar m_bar; Bar check(Int v) { Bar b; b.val_b[1] = true; return b; } Int test() { Foo f; f.m_i = 15; m_bar = f.check(1); return f.m_i; } }\n"); //tests offsets, but too complicated data members in Foo for memberselect

      bool rtn2 = fms->add("Bar.ulam"," ulam 1;\n quark Bar {\n Bool val_b[3];\n  Void reset(Bool b) {\n b = false;\n }\n }\n\n");

      bool rtn3 = fms->add("System.ulam", "ulam 1;\nquark System {\nVoid print(Unsigned arg) native;\nVoid print(Int arg) native;\nVoid print(Int(4) arg) native;\nVoid print(Int(3) arg) native;\nVoid print(Unary(3) arg) native;\nVoid print(Bool(3) arg) native;\nVoid assert(Bool b) native;\n}\n");

      if(rtn1 && rtn2 && rtn3)
	return std::string("Foo.ulam");

      return std::string("");
    }
  }

  ENDTESTCASECOMPILER(t3172_test_compiler_elementandquark_returnquark)

} //end MFM
