#include<iostream>
#include<string>
#include<locale>
#include<sstream>
#include"lexer.h"

/* Lexer */
int Lexer::line = 1;

Lexer::Lexer() 
{
	peek = ' ';
	hash_index = 0;
	Tag t;
	reserve(Word("if", t.IF));
	reserve(Word("else", t.ELSE));
	reserve(Word("while", t.WHILE));
	reserve(Word("do", t.DO));
	reserve(Word("break", t.BREAK));
	reserve(True);
	reserve(False);
	reserve(Int);
	reserve(Char);
	reserve(Bool);
	reserve(Float);
}

void Lexer::reserve(Word w) 
{
	if(hash_index > 99) 
		cout << "hashtable overflow" << endl;
	else
		hashtable[hash_index++].put(w.lexeme, &w);
}

void Lexer::Open_File(char *filename) 
{
	file.open(filename);
}

void Lexer::Close_File() 
{
	file.close();
}

bool Lexer::Eof() 
{
	if(file.eof()) return true;
	else return false;
}

bool Lexer::Check_Digit(char c) 
{
	std::locale loc;
	if(isdigit(c, loc)) return true;
	else return false;
}

bool Lexer::Check_Letter(char c) 
{
	std::locale loc;
	if(isalpha(c, loc)) return true;
	else return false;
}

void Lexer::readch() 
{
	peek = file.get();	
}

bool Lexer::readch(char c) 
{
	readch();

	if(peek != c) return false;
	peek = ' ';

	return true;
}

Token* Lexer::scan() 
{
	for (;;readch()) {
		if(peek == ' ' || peek == '\t')
			continue;
		else if(peek == '\n')
			line++;
		else
			break;
	}

	switch(peek) {
		case '&':
			if(readch('&'))
				return &And;
			else {
				Token *t = new Token('&');
				return t;
			}
			break;
		case '|':
			if(readch('|'))
				return &Or;
			else {
				Token *t = new Token('|');
				return t;
			}
			break;
		case '=':
			if(readch('='))
				return &Eq;
			else {
				Token *t = new Token('=');
				return t;
			}
			break;
		case '!':
			if(readch('='))
				return &Ne;
			else {
				Token *t = new Token('!');
				return t;
			}
			break;
		case '<':
			if(readch('='))
				return &Le;
			else {
				Token *t = new Token('<');
				return t;
			}
			break;
		case '>':
			if(readch('='))
				return &Ge;
			else {
				Token *t = new Token('>');
				return t;
			}
			break;
		
	}

	if(Check_Digit(peek)) {
		int v = 0;
		do {
			v = 10 * v + peek - 48;
			readch();
		} while(Check_Digit(peek));

		if(peek != '.') {
			Num *t = new Num(v);
			return t;
		}

		float x = v;
		float d = 10;

		for(;;) {
			readch();
			if(!Check_Digit(peek)) break;
			x += (peek - 48) / d;
			d *= 10;
		}
		Real *t = new Real(x);
		return t;
	}

	if(Check_Letter(peek)) {
		std::string b;
		do {
			b.append(1, peek);
			readch();
		} while(Check_Letter(peek) || Check_Digit(peek));

		bool Flag_hashtable = false;
		Word *w = new Word(b, t.ID);

		for(int i = 0; i < 100; i++)
			if(hashtable[i].Compare(b)) {
				w->~Word();
				w = hashtable[i].get();
				Flag_hashtable = true;
				break;
			}

		if(!Flag_hashtable)
			hashtable[hash_index++].put(b, w);

		return w;
	}

	Token *t = new Token(peek);
	peek = ' ';
	return t;
}
/* -------------------------- */

/* Hashtable */
void Hashtable::put(std::string s, Word* w) 
{
	string = s;
	word = Word(w->lexeme, w->token_tag);
}

Word* Hashtable::get() 
{
	return &word;
}

bool Hashtable::Compare(std::string s) 
{
	if(s.compare(string) == 0) return true;
	else return false;
}
/* -------------------------- */

/* Token */
std::string Token::toString() 
{
	std::ostringstream s;
	s << (char)token_tag;
	return s.str();
}

void Token::Show_Tag(int token_tag) 
{
	switch(token_tag) {
		case 256:
			cout << "AND";
			break;
		case 257:
			cout << "BASIC";
			break;
		case 258:
			cout << "BREAK";
			break;
		case 259:
			cout << "DO";
			break;
		case 260:
			cout << "ELSE";
			break;
		case 261:
			cout << "EQ";
			break;
		case 262:
			cout << "FALSE";
			break;
		case 263:
			cout << "GE";
			break;
		case 264:
			cout << "ID";
			break;
		case 265:
			cout << "IF";
			break;
		case 266:
			cout << "INDEX";
			break;
		case 267:
			cout << "LE";
			break;
		case 268:
			cout << "MINUS";
			break;
		case 269:
			cout << "NE";
			break;
		case 270:
			cout << "NUM";
			break;
		case 271:
			cout << "OR";
			break;
		case 272:
			cout << "REAL";
			break;
		case 273:
			cout << "TEMP";
			break;
		case 274:
			cout << "TRUE";
			break;
		case 275:
			cout << "WHILE";
			break;
		default:
			cout << (char)token_tag;
			break;
	}
}
/* -------------------------- */

/* Word */

Word::Word(std::string s, int tag): Token(tag) 
{
	lexeme = s;
}

std::string Word::toString() 
{
	return lexeme;
}
/* -------------------------- */

/* Num */
Num::Num(int v):  Token(t.NUM), value(v) 
{
}

std::string Num::toString() 
{
	std::ostringstream s;
	s << value;
	return s.str();
}
/* -------------------------- */

/* Real */
Real::Real(float v): Token(t.REAL), value(v) 
{
}

std::string Real::toString() 
{
	std::ostringstream s;
	s << value;
	return s.str();
}
/* -------------------------- */

/* Type */
Type::Type(std::string s, int tag, int w): Word(s, tag) 
{
	width = w;
}

bool Type::numeric(Type p) 
{
	if(p == Char || p == Int || p == Float)
		return true;
	else return false;
}

Type Type::max(Type p1, Type p2) 
{
	if(!numeric(p1) || !numeric(p2)) return Type();
	else if(p1 == Float || p2 == Float)
		return Float;
	else if(p1 == Int || p2 == Int)
		return Int;
	else
		return Char;
}

bool operator==(const Type& x, const Type& y) 
{
	if(x.lexeme == y.lexeme && x.token_tag == y.token_tag && x.width == y.width)
		return true;
	return false;
}
/* -------------------------- */
