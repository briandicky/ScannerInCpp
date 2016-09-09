#include<fstream>

using namespace std;

/* Tag */
class Tag {
	public:
	static const int
	AND = 256,
	BASIC = 257,
	BREAK = 258,
	DO = 259,
	ELSE = 260,
	EQ = 261,
	FALSE = 262,
	GE = 263,
	ID = 264,
	IF = 265,
	INDEX = 266,
	LE = 267,
	MINUS = 268,
	NE = 269,
	NUM = 270,
	OR = 271,
	REAL = 272,
	TEMP = 273,
	TRUE = 274,
	WHILE = 275;
};
/* -------------------------- */

/* Token */
class Token {
	public:
	int token_tag;
	Token(): token_tag(0) {};
	Token(int t): token_tag(t) {};
	~Token() {};
	virtual std::string toString();
	void Show_Tag(int token_tag);
};
/* -------------------------- */

/* Word */
class Word : public Token {
	public:
	std::string lexeme;
	Word() {lexeme = "";};
	~Word() {};
	Word(std::string s, int tag);
	std::string toString();
};
/* -------------------------- */

/* Num */
class Num : public Token {
	const int value;
	public:
	Num(): value(0) {};
	Num(int v);
	~Num() {};
	std::string toString();
};
/* ------------------------- */

/* Real */
class Real : public Token {
	const float value;
	public:
	Real(): value(0) {};
	Real(float v);
	~Real() {};
	std::string toString();
};
/* ------------------------- */

/* Type */
class Type : public Word {
	public:
	int width;
	Type() {width = 0;};
	~Type() {};
	Type(std::string s, int tag, int w);

	static bool numeric(Type p);
	static Type max(Type p1, Type p2);
    	friend bool operator==(const Type& x, const Type& y);
};
/* ------------------------- */

/* Hashtable */
class Hashtable {
	public:
	std::string string;
	Word word;
	Hashtable() {string = "";};
	~Hashtable() {};
	void put(std::string s, Word* w);
	Word* get();
	bool Compare(std::string s);
};
/* ------------------------ */

/* Lexer */
class Lexer {
	int hash_index;
	ifstream file;
	char peek;
	Hashtable hashtable[100];
	public:
	static int line;
	Lexer();
	~Lexer() {Close_File();};
	void reserve(Word w);
	void readch();
	bool readch(char c);
	void Open_File(char *filename);
	void Close_File();
	bool Eof();
	bool Check_Digit(char c);
	bool Check_Letter(char c);
	Token* scan();
};
/* ------------------------ */

static const Tag t;

static Word
	And("&&", t.AND),
	Or("||", t.OR),
	Eq("==", t.EQ),
	Ne("!=", t.NE),
	Le("<=", t.LE),
	Ge(">=", t.GE),
	Minus("minus", t.MINUS),
	True("true", t.TRUE),
	False("false", t.FALSE),
	Temp("t", t.TEMP);

static Type
	Int("int", t.BASIC, 4),
	Float("float", t.BASIC, 8),
	Char("char", t.BASIC, 1),
	Bool("bool", t.BASIC, 1);

