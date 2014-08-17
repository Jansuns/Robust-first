#include "TestCase_EndToEndParser.h"

namespace MFM {

  BEGINTESTCASEPARSER(t221_test_parser_controlwhile_emptybody)
  {
    std::string GetAnswerKey()
    {
      return std::string(" { Int a(0);  Int test() {  a 5 = a a 1 -b = cast cond {} while a return } }\n");
    }
    
    std::string PresetTest(FileManagerString * fms)
    {
      bool rtn1 = fms->add("a.ulam","ulam { Int a; Int test() {a = 5; while( a = a - 1 ) { } return a; } }");
      
      if(rtn1)
	return std::string("a.ulam");
      
      return std::string("");
    }      
  }
  
  ENDTESTCASEPARSER(t221_test_parser_controlwhile_emptybody)
  
} //end MFM

