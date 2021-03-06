#include "TestCase_EndToEndCompiler.h"

namespace MFM {

  BEGINTESTCASECOMPILER(t3462_test_compiler_elementshift_error)
  {
    std::string GetAnswerKey()
    {
      //./A.ulam:4:8: ERROR: Non-primitive type: <A> is not supported for LHS bitwise shift operator<<.
      // ./A.ulam:5:8: ERROR: Non-primitive type: <A> is not supported for RHS bitwise shift operator<<.
      return std::string("Exit status: -1\n");
    }

    std::string PresetTest(FileManagerString * fms)
    {
      bool rtn1 = fms->add("A.ulam","element A {\nInt test() {\n A a, b;\n b = a << 1;\n b = 1 << a;\n return -1;\n }\n }\n");

      if(rtn1)
	return std::string("A.ulam");

      return std::string("");
    }
  }

  ENDTESTCASECOMPILER(t3462_test_compiler_elementshift_error)

} //end MFM
