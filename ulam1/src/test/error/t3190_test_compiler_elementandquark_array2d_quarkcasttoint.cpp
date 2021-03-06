#include "TestCase_EndToEndCompiler.h"

namespace MFM {

  BEGINTESTCASECOMPILER(t3190_test_compiler_elementandquark_array2d_quarkcasttoint)
  {
    std::string GetAnswerKey()
    {
      //./Foo.ulam:4:2: ERROR: Data member <m_array> of type: Unsigned(1)[71], total size: 71 MUST fit into 64 bits; Local variables do not have this restriction.

      //Ue_Foo { Int(1) m_array[71](0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);  Int(32) test() {  C2D c;  c ( 0 cast 0 cast )func = m_array c ( )toInt . [] true cast = m_array c ( )toInt . [] cast return } }\nExit status: 1

      return std::string("Exit status: -1\nUe_Foo { Int(32) test() {  Int(1) m_array[71];  C2D c;  c ( 0 0 )func = m_array c ( )toInt . cast [] true cast = m_array c ( )toInt . cast [] cast return } }\nUq_C2D { Int(8) m_width(0);  Int(8) m_height(0);  Int(8) m_x(0);  Int(8) m_y(0);  <NOMAIN> }\n");
    }

    std::string PresetTest(FileManagerString * fms)
    {
      // data members must fit within 32-bits (BitField limit)
      bool rtn1 = fms->add("Foo.ulam","ulam 1;\n use C2D;\n element Foo {\n Unsigned(1) m_array[71];\n C2D func(Int i, Int j) {\n C2D c;\n c.init();\n c.set(i,j);\n return c;\n }\n Int test() {\n C2D c;\n c = func(0,0);\n m_array[c] = 1; //true\n return m_array[c];\n }\n }\n");

      // alternative: use as a local data member instead
      //bool rtn1 = fms->add("Foo.ulam","ulam 1;\n use C2D;\n element Foo {\nC2D func(Int i, Int j) {\n C2D c;\n c.init();\n c.set(i,j);\n return c;\n }\n Int test() {\n Int(1) m_array[71];\n C2D c;\n c = func(0,0);\n m_array[c] = true;\n return m_array[c];\n }\n }\n");

      bool rtn2 = fms->add("C2D.ulam","quark C2D {\n typedef Int(8) IE;\n IE m_width, m_height, m_x, m_y;\n  Void init(Int x, Int y) {\n m_width = (IE) x;\n m_height = (IE) y;\n}\n Void init() {\n m_width = 9;\n m_height = 4;\n /* event window overload */ }\n Void set(Int a, Int b) {\n m_x = (IE) a;\n m_y = (IE) b;\n }\n Int toInt(){\n return ((m_height-m_y) * m_width + (m_height-m_x));\n }\n }\n");


      if(rtn1 && rtn2)
	return std::string("Foo.ulam");

      return std::string("");
    }
  }

  ENDTESTCASECOMPILER(t3190_test_compiler_elementandquark_array2d_quarkcasttoint)

} //end MFM
