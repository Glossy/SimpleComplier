//
// Created by Wu on 2016/12/2.
//

#include "Scanner.h"

using namespace std;

Symbol::Symbol(Symbol_Type a,string b,double c,double d):type(a),lexeme(b),value(c),func(d),Line_num(0){};

Scanner::Scanner(string s) {
    cout<<"Initialize Scanner"<<endl;
    //cout<<"Input the file you want to compile"<<endl;
    string filename = s;
    //cin>>filename;
    EmptyBuffer();
    //string url = "E:\\Code\\Complier\\";
    //url += filename;
    Compiled_file.open(filename,ios::in|ios::binary );
    Compiled_file.seekg(3,ios::beg);
    LineNum = 1;
    Symbol_Buffer[0] = '\0';
    //*Symbol_List = NULL;
    if (! Compiled_file.is_open()) {
        QMessageBox::warning(NULL, "Scanner","Error opening file");
        return;
    }
}
Scanner::~Scanner() {
    cout<<"Close Scanner"<<endl;
    Compiled_file.close();
}
void Scanner::EmptyBuffer() {
    int i = 0;
    for(i ; i < MAX_SYMBOL_LEN; i++){
        Symbol_Buffer[i] = 0;
    }
    Symbol_Buffer[0] = '\0';
}
Symbol Scanner::JudgeSymbol() {
    int loop;
    for(loop = 0;loop < (sizeof(Symbol_Buffer)/ sizeof(Symbol_Buffer[0]));loop++){
        if(!strcmp(SymbolTabel[loop].lexeme.c_str(),Symbol_Buffer) ){
            return SymbolTabel[loop];
        }
    }
    Symbol symbol1(ERRTOKEN,"",0.0,0.0);
    return symbol1;
}
void Scanner::AddBuffer(char a,int i) {
    if(i+1> sizeof(Symbol_Buffer)||i < 0){
        cout<<"The Symbol's length is out of number"<<endl;
        return ;
    }
    Symbol_Buffer[i] = a;
    Symbol_Buffer[i+1] = '\0';
}
char Scanner::GetChar() {
    char a;
    Compiled_file.get(a);
    if(Compiled_file.peek() == EOF){
        eof = 2;
    }
    if(islower(a)) {
        a = (char) toupper(a);
    }
    return a;
}
void Scanner::GetSymbol() {
    char aChar;
    EmptyBuffer();
    while(1){
        aChar = this->GetChar();
        if(Compiled_file.eof()){
            Symbol* asymbol = new Symbol(NONTOKEN,"NONTOKEN",0.0,0.0);
            asymbol->Line_num = LineNum;
            Symbol_List_Num.push_back(asymbol);
            return;
        }
        else if(aChar == '\n'){
            LineNum++;
        }
        else if(aChar == ' ' || aChar == '\t' || aChar == '\r');
        else break;
    }
    this->AddBuffer(aChar,0);
    int count = 1;
    if(isalpha(aChar)){
        while(1){
            aChar = this->GetChar();
            if(isalpha(aChar)){
                this->AddBuffer(aChar,count);
                count++;
            }
            else{
                break;
            }
        }
        Compiled_file.seekg(-1,ios::cur);
        Symbol *asymbol = new Symbol(JudgeSymbol().type,JudgeSymbol().lexeme,JudgeSymbol().value,JudgeSymbol().func);
        asymbol->Line_num = LineNum;
        Symbol_List_Num.push_back(asymbol);
    }
    else if(isdigit(aChar)){
        while(1){
            aChar = this->GetChar();
            if(isdigit(int(aChar))){
                this->AddBuffer(aChar,count);
                count++;
            }
            else{
                break;
            }
        }
        if(aChar == '.'){
                this->AddBuffer(aChar,count);
                count++;
                while(1){
                    aChar = this->GetChar();
                    if(isdigit(int(aChar))){
                        this->AddBuffer(aChar,count);
                        count++;
                    }
                    else{
                        break;
                    }
                }
            }
        else{
            Compiled_file.seekg(-1,ios::cur);
            char t[256];
            string s;
            sprintf(t, "%lf",atof(Symbol_Buffer));
            s = t;
            Symbol *asymbol = new Symbol(CONST_ID,s,atof (Symbol_Buffer),0);
            asymbol->Line_num = LineNum;
            Symbol_List_Num.push_back(asymbol);
            }
    }
    else{
        switch (aChar) {
            case ';' : {Symbol *asymbol = new Symbol(SEMICO,";",0.0,0.0) ;asymbol->Line_num = LineNum;Symbol_List_Num.push_back(asymbol); break;}
            case '(' : {Symbol *asymbol = new Symbol(L_BRACKET,"(",0.0,0.0) ;asymbol->Line_num = LineNum;Symbol_List_Num.push_back(asymbol); break;}
            case ')' : {Symbol *asymbol = new Symbol(R_BRACKET,")",0.0,0.0) ;asymbol->Line_num = LineNum; Symbol_List_Num.push_back(asymbol); break;}
            case ',' : {Symbol *asymbol = new Symbol(COMMA,",",0.0,0.0) ;asymbol->Line_num = LineNum;Symbol_List_Num.push_back(asymbol); break;}
            case '+' : {Symbol *asymbol = new Symbol(PLUS,"+",0.0,0.0) ;asymbol->Line_num = LineNum;Symbol_List_Num.push_back(asymbol); break;}
            case '-' : {
                aChar = GetChar();
                if (aChar == '-') {
                    while (aChar != '\n' && aChar != EOF) aChar = GetChar();
                    Compiled_file.seekg(-1, ios::cur);
                    return GetSymbol();
                } else {
                    Compiled_file.seekg(-1, ios::cur);
                    Symbol *asymbol = new Symbol(MINUS, "-", 0.0, 0.0);
                    asymbol->Line_num = LineNum;
                    Symbol_List_Num.push_back(asymbol);
                    break;
                }
            }
            case '/' : {
                aChar = GetChar();
                if (aChar == '/') {
                    while (aChar != '\n' && aChar != EOF) aChar = GetChar();
                    Compiled_file.seekg(-1, ios::cur);
                    return GetSymbol();
                } else {
                    Compiled_file.seekg(-1, ios::cur);
                    Symbol *asymbol = new Symbol(DIV, "/", 0.0, 0.0);
                    asymbol->Line_num = LineNum;
                    Symbol_List_Num.push_back(asymbol);
                    break;
                }
            }
            case '*' : {
                aChar = GetChar();
                if (aChar == '*') {
                    Symbol *asymbol = new Symbol(POWER, "POWER", 0.0, 0.0);
                    asymbol->Line_num = LineNum;
                    Symbol_List_Num.push_back(asymbol);
                    break;
                } else {
                    Compiled_file.seekg(-1, ios::cur);
                    Symbol *asymbol = new Symbol(MUL, "*", 0.0, 0.0);
                    asymbol->Line_num = LineNum;
                    Symbol_List_Num.push_back(asymbol);
                    break;
                }
            }
            default :Symbol* asymbol = new Symbol(ERRTOKEN,"ERRTOKEN",0.0,0.0);asymbol->Line_num = LineNum;Symbol_List_Num.push_back(asymbol);break;
        }
    }
}
void Scanner::Initialize_Scanner() {
    this->Compiled_file.clear();
    Compiled_file.seekg(0,ios::beg);
    LineNum = 0;
}
/*void Scanner_Demo(){
    Scanner  *scanner = new Scanner();
    cout<<"SymbolType  String  Constvalue  FunctionPointer"<<endl;
    cout<<"____________________________________________"<<endl;
    while(1){
        scanner->GetSymbol();
        if(scanner->Compiled_file.eof()){
            break;
        }
    };
    int i = 0;
    while(i < scanner->Symbol_List_Num.size()){
        cout<<scanner->Symbol_List_Num[i]->type<<" "<<scanner->Symbol_List_Num[i]->lexeme<<" "<<scanner->Symbol_List_Num[i]->value<<" "<<scanner->Symbol_List_Num[i]->func<<endl;
        i++;
    }
    cout<<"____________________________________________"<<endl;
    delete scanner;
}
*/
