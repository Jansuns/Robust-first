#include "TestCase_EndToEndCompiler.h"

namespace MFM {

  BEGINTESTCASECOMPILER(t3267_test_compiler_elementandquark_typedeffromanotherclass)
  {
    std::string GetAnswerKey()
    {
      return std::string("Exit status: 2\nUe_TypedefIssue { Unsigned(3) x[2](0,2);  Bool(1) b(true);  Vector t( typedef Unsigned(3) Symmetry;  Unsigned(3) m(2);  Unsigned(3) n(1); );  Int(32) test() {  t ( 2 cast 1 cast )set . cond b true = if x 1 [] t m . = x 1 [] cast return } }\nUq_Vector { typedef Unsigned(3) Symmetry;  Unsigned(3) m(0);  Unsigned(3) n(2);  <NOMAIN> }\n");
    }

    std::string PresetTest(FileManagerString * fms)
    {
      // informed by t3258: typedef 'Symmetry' from quark used as data member array, and casted arg in element.
      // must already be parsed! (e.g. couldn't use element yet! because its Class Block doesn't exist).
      bool rtn1 = fms->add("TypedefIssue.ulam","ulam 1;\nuse Vector;\n element TypedefIssue {\nVector.Symmetry x[2];\n Bool b;\nVector t;\n Int test() {\nif(t.set((Vector.Symmetry) 2, (Vector.Symmetry) 1))\n b=true;\n x[1]=t.m;\n return x[1];\n}\n}\n");
      //simplify for debugging
      //bool rtn1 = fms->add("TypedefIssue.ulam","ulam 1;\nuse Vector;\n element TypedefIssue {\nVector.Symmetry x[2];\n Int test() {\n return x[1];\n}\n}\n");

      bool rtn2 = fms->add("Vector.ulam","ulam 1;\nquark Vector {\ntypedef Unsigned(3) Symmetry;\n Symmetry m;\nSymmetry n;\n Bool set(Symmetry vector, Symmetry index) {\nm=vector;\nn=index;\n return (m!=0 && n!=0);\n }\n}\n");

      if(rtn1 && rtn2)
	return std::string("TypedefIssue.ulam");

      return std::string("");
    }
  }

  ENDTESTCASECOMPILER(t3267_test_compiler_elementandquark_typedeffromanotherclass)

} //end MFM
