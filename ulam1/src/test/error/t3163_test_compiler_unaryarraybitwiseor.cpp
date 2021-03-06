#include "TestCase_EndToEndCompiler.h"

namespace MFM {

  BEGINTESTCASECOMPILER(t3163_test_compiler_unaryarraybitwiseor)
  {
    std::string GetAnswerKey()
    {
      //./A.ulam:11:8: ERROR: Incompatible (nonscalar) types, LHS: Unary(3)[2], RHS: Unary(3)[2] for binary operator| ; Suggest writing a loop.
      return std::string("Ue_A { typedef Unary(3) Mu[2];  Unary(3) a[2](2,1);  Unary(3) b[2](0,2);  Unary(3) c[2](2,2);  Int(32) test() {  a 0 [] 2 cast = a 1 [] 1 cast = b 0 [] 0 cast = b 1 [] 2 cast = c a b | = c 0 [] cast return } }\nExit status: 2");
    }

    std::string PresetTest(FileManagerString * fms)
    {
      //bool rtn1 = fms->add("A.ulam","element A { typedef Unary(3) Mu[2]; Mu a, b, c;  use test;  a[0] = 2; a[1] = 1; b[0] = 0; b[1] = 2; c = a | b; return c[0]; } }");

      bool rtn1 = fms->add("A.ulam","element A {\n typedef Unary(3) Mu[2];\nBool sp1;\nBool(15) sp;\nMu a, b, c;\n  use test;\n  a[0] = 2;\n a[1] = 1;\n b[0] = 0;\n b[1] = 2;\n c = a | b;\n return c[0];\n }\n }\n");

      bool rtn2 = fms->add("test.ulam", "Int test() {\n");

      if(rtn1 && rtn2)
	return std::string("A.ulam");

      return std::string("");
    }
  }

  ENDTESTCASECOMPILER(t3163_test_compiler_unaryarraybitwiseor)

} //end MFM
