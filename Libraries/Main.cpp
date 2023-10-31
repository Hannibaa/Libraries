/*
                         Authur     : KADDA Aoues
                         My library :


                         1. container utility : namespace container_utility = cu::
                         2. associative container utility : namespace        acu::
                         3. file utility :                                  File::
                                   3.1 make splite filer 31 / 10 / 2023
                         4. bitwise utility :                                Bit::
                         5. bitmap image utility :                          bmpf::
                         6. escape character utility :                       Esc::
                         7. string utility                                   Str::
                                   7.1 we need to change get_text_word from using 
                                   vector to using map to avoid repetition.
                         8. Time utility                                    Time::
                         9. Calender utility                            Calender::
                         10. meta programming lib                            mpl::
                         11. function utility mathematic and logic      Function::
                         12. random variable utility                         RND::
                         13. variable transition                              vt::
                         14. geometry function and relation                geo2d:: 
                                                                           geo3d:: 
                                                                        geometry:: 
                                                                      affine_geo::
                         15. making Text Library                            Text::
                             CGlyph, CWord, CLine, CPage, CText,   
*/


#include <iostream>
#include "MyLib/Console_Library/escape_code.h"


using namespace std;


int main()
{
	print_ << "hello"" world"     " this here_";
	newline_;



	cin.get();
	return 0;
}