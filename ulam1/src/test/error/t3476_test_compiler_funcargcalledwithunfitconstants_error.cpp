#include "TestCase_EndToEndCompiler.h"

namespace MFM {

  BEGINTESTCASECOMPILER(t3476_test_compiler_funcargcalledwithunfitconstants_error)
  {
    std::string GetAnswerKey()
    {
      //no longer takes the first one even though constant doesn't fit!
      //./Tu.ulam:12:9: ERROR: (1) <func> has no defined function with 1 matching argument type: Int(32), and cannot be called.
      return std::string("Exit status: 7\nUe_Tu { typedef Int(3) I;  typedef Int(4) J;  Int(32) test() {  ( 7 cast )func cast return } }\n");
    }

    std::string PresetTest(FileManagerString * fms)
    {
      //t3477 uses 7; here, 9 fits neither.
      bool rtn1 = fms->add("Tu.ulam", "ulam 1;\nelement Tu {\ntypedef Int(3) I;\n I func(I arg) {\nreturn arg;\n}\n typedef Int(4) J;\n J func(J arg) {\nreturn arg;\n}\n Int test(){\n return func(9);\n}\n}\n");


      if(rtn1)
	return std::string("Tu.ulam");

      return std::string("");
    }
  }

  ENDTESTCASECOMPILER(t3476_test_compiler_funcargcalledwithunfitconstants_error)

} //end MFM
