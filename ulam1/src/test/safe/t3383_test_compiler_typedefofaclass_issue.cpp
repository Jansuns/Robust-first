#include "TestCase_EndToEndCompiler.h"

namespace MFM {

  BEGINTESTCASECOMPILER(t3383_test_compiler_typedefofaclass_issue)
  {
    std::string GetAnswerKey()
    {
      //test bug fix: typedef of a class' typedef
      //Ish2.ulam:6:16: ERROR: Invalid Class Type: <Tail>; KEYWORD should be: 'element', 'quark', or 'union'.
      //							    ERROR: No parse tree for This Class: Ish2.
      return std::string("Exit status: 3\nUe_R { Ish2 ish( Colony(3u) colony( constant Unsigned(32) widthc = 3;  typedef Telomeree(3u) Telo;  typedef Unsigned(3) TeloTail;  Telomeree(3u) t( constant Unsigned(32) width = 3;  typedef Unsigned(3) Tail;  Unsigned(3) age(0); ); ); );  Int(32) test() {  3u cast return } }\nUq_Telomeree { constant Unsigned(32) width = NONREADYCONST;  typedef Unsigned(UNKNOWN) Tail;  Unsigned(UNKNOWN) age(0);  <NOMAIN> }\nUq_Colony { constant Unsigned(32) widthc = NONREADYCONST;  typedef Telomeree(width) Telo;  typedef Unsigned(UNKNOWN) TeloTail;  Telomeree(width) t( constant Unsigned(32) width = NONREADYCONST; );  <NOMAIN> }\nUq_Ish2 { Colony(3u) colony( constant Unsigned(32) widthc = 3;  typedef Telomeree(3u) Telo;  typedef Unsigned(3) TeloTail;  Telomeree(3u) t( constant Unsigned(32) width = 3;  typedef Unsigned(3) Tail;  Unsigned(3) age(0); ); );  <NOMAIN> }\n");
    }

    std::string PresetTest(FileManagerString * fms)
    {
      // likes Telomeree first!
      bool rtn3 = fms->add("R.ulam", "use Telomeree;\n use Colony;\n use Ish2;\n  element R{\nIsh2 ish;\n Int test() { return ish.sizeof;\n}\n}");

      // this order fails:  ERROR: Number of Arguments (2) in class instance: Telomeree, does not match the required number of parameters (1) to fix.
      //bool rtn3 = fms->add("R.ulam", " use Colony;\n  use Telomeree;\n use Ish2;\n element R{\nIsh2 ish;\n Int test() { return ish.sizeof;\n}\n}");

      bool rtn1 = fms->add("Colony.ulam","quark Colony(Unsigned widthc){\n typedef Telomeree(widthc) Telo;\n typedef Telo.Tail TeloTail;\n  Telo t;\n }");
      bool rtn2 = fms->add("Ish2.ulam","quark Ish2{\nColony(3) colony;\n }");
      bool rtn4 = fms->add("Telomeree.ulam","quark Telomeree(Unsigned width){\n typedef Unsigned(width) Tail;\n Tail age;\n }");

      if(rtn1 && rtn2 && rtn3 && rtn4)
	return std::string("R.ulam");

      return std::string("");
    }
  }

  ENDTESTCASECOMPILER(t3383_test_compiler_typedefofaclass_issue)

} //end MFM
