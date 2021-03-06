#include "TestCase_EndToEndCompiler.h"

namespace MFM {

  BEGINTESTCASECOMPILER(t3153_test_compiler_typebitsize)
  {
    std::string GetAnswerKey()
    {
      //casting to Bits a,b are false now.
      //note: m_i[1] = 3 now (correctly), not 7 as before.
      return std::string("Exit status: 0\nUe_C { Bool(1) a(false);  Int(3) m_i[4](2,3,0,0);  Int(6) m_u(15);  Bool(3) b(false);  Int(32) test() {  m_i 0 [] 2 = m_u 15 cast = m_i 1 [] m_u cast = b m_i 0 [] 3 == cast = b b cast m_i 0 [] 0 cast != cast & cast = a b cast = 0 cast return } }\n");
    }

    std::string PresetTest(FileManagerString * fms)
    {
      // Bits for bitwise; changed &= to & in order to cast explicitly to Bits(3) and then back to Bool(3).
      // note: 15 fits into 3 bits and turns into 7;
      bool rtn1 = fms->add("C.ulam","ulam 1;\n element C {\n Bool a;\n Int(3) m_i[4];\n Int(6) m_u;\n Bool(3) b;\n Int test() {\n m_i[0] = 2;\n m_u = 15;\n m_i[1] = (Int(3)) m_u;\n b = (m_i[0] == Int(3).maxof);\n b = (Bool(3)) (b & (m_i[0] !=0));\n a = b;\n return 0;\n}\n }\n");

      if(rtn1)
	return std::string("C.ulam");

      return std::string("");
    }
  }

  ENDTESTCASECOMPILER(t3153_test_compiler_typebitsize)

} //end MFM
