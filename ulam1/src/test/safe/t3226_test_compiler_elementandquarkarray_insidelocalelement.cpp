#include "TestCase_EndToEndCompiler.h"

namespace MFM {

  BEGINTESTCASECOMPILER(t3226_test_compiler_elementandquarkarray_insidelocalelement)
  {
    std::string GetAnswerKey()
    {
      return std::string("Exit status: 0\nUe_Foo { Bool(3) b(false);  typedef Bar Pop[2];  System s();  Int(4) m_i(0);  Bar m_bar2[2]( Bool(1) val_b[3](false,false,false);  Bool(1) val_b[3](false,false,false); );  Bar sbar( Bool(1) val_b[3](false,false,false); );  Int(32) test() {  Foo f;  Atom(96) a;  a f sbar 0 cast [] . = f sbar 1 cast [] . a = 0 cast return } }\nUq_System { <NOMAIN> }\nUq_Bar { Bool(1) val_b[3](false,false,false);  <NOMAIN> }\n");
    }

    std::string PresetTest(FileManagerString * fms)
    {
      bool rtn1 = fms->add("Foo.ulam","ulam 1;\nuse System;\n use Bar;\n element Foo {\n typedef Bar Pop[2];\nSystem s;\nBool(3) b;\n Int(4) m_i;\n Pop m_bar2;\n Bar sbar;\n Bool check(Int v) {\n return true;\n }\n Int test() {\nFoo f;\nAtom a;\n a = f.sbar[0];\nf.sbar[1] = a;\nreturn 0;\n }\n }\n");

      bool rtn2 = fms->add("Bar.ulam"," ulam 1;\n quark Bar {\n Bool val_b[3];\n  Void reset(Bool b) {\n b = false;\n }\n Atom aref(Int index) native;\n Void aset(Int index, Atom v) native;\n }\n");

      // test system quark with native overloaded print funcs; assert
      bool rtn3 = fms->add("System.ulam", "ulam 1;\nquark System {\nVoid print(Unsigned arg) native;\nVoid print(Int arg) native;\nVoid print(Int(4) arg) native;\nVoid print(Int(3) arg) native;\nVoid print(Unary(3) arg) native;\nVoid print(Bool(3) arg) native;\nVoid assert(Bool b) native;\n}\n");


      if(rtn1 && rtn2 && rtn3)
	return std::string("Foo.ulam");

      return std::string("");
    }
  }

  ENDTESTCASECOMPILER(t3226_test_compiler_elementandquarkarray_insidelocalelement)

} //end MFM
