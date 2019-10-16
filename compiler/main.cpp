#include <iostream>

extern int yyparse();




int main(){
	int result = yyparse();
	if(result == 0)
		std::cout << "Entro con ganas"<< std::endl;
	else
		std::cout << "No entro"<< std::endl;
	return result;

}