#include<iostream>
#include <cstdlib>
#include"lexer.h"

using namespace std;

int main(int argc, char *argv[]) {

	int i = 1;
	Token *temp;
	Lexer lexer;
	lexer.Open_File(argv[1]);

	while(1) {
		temp = lexer.scan();
		if(lexer.Eof()) break;

		cout << i++ << " Token: " << temp->toString() << "\t" << "(";
		temp->Show_Tag(temp->token_tag);
		cout << ")" << endl;
	}
	cout << i << " End of file reached" << endl;

	lexer.Close_File();

	return 0;
}
