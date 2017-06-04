//
// Created by Wu on 2016/12/2.
//

#ifndef COMPLIER_SCANNER_H
#define COMPLIER_SCANNER_H

#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <string>
#include <cctype>
#include <fstream>
#include <vector>
#include <iomanip>

#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>


using namespace std;

#define MAX_SYMBOL_LEN 50

void Scanner_Demo();

enum Symbol_Type{
    ORIGIN, SCALE, ROT, IS, TO,
    STEP, DRAW, FOR, FROM,                  //保留字
    T,                                      //参数
    PLUS, MINUS, MUL, DIV, POWER,           //运算符
    SEMICO, L_BRACKET, R_BRACKET, COMMA,    //分隔符
    FUNC,                                   //函数（调用）
    CONST_ID,                               //常数
    NONTOKEN,                               //空记号（源程序结束）
    ERRTOKEN                                //出错记号（非法输入）
};
class Symbol  {                            //记号与符号表结构
public:
    Symbol(Symbol_Type a,string b,double c,double d);
    Symbol_Type type ;                     //记号的类别
    string lexeme;                         //构成记号的字符串
    double value;                         //若为常数，则是常数的值
    double func;                          //若为函数，则是函数的指针
    int Line_num;                         //所在行数
};
static Symbol SymbolTabel[] =	{			// 符号表内容
         	 {CONST_ID,	"PI",		3.1415926,	0.0},
             {CONST_ID,	"E",		2.71828,	0.0},
             {T,		"T",		0.0,		0.0},
             {FUNC,		"SIN",		0.0,		1.0},
             {FUNC,		"COS",		0.0,		2.0},
             {FUNC,		"TAN",		0.0,		3.0},
             {FUNC,		"LN",		0.0,		4.0},
             {FUNC,		"EXP",		0.0,		5.0},
             {FUNC,		"SQRT",		0.0,		6.0},
             {ORIGIN,	"ORIGIN",	0.0,		0.0},
             {SCALE,	"SCALE",	0.0,		0.0},
             {ROT,		"ROT",		0.0,		0.0},
             {IS,		"IS",		0.0,		0.0},
             {FOR,		"FOR",		0.0,		0.0},
             {FROM,		"FROM",		0.0,		0.0},
             {TO,		"TO",		0.0,		0.0},
             {STEP,		"STEP",		0.0,		0.0},
             {DRAW,		"DRAW",		0.0,		0.0}
        };

class Scanner{
public:
    int eof;
    vector <Symbol*> Symbol_List_Num;                //一个存储符号表指针地址的数组
    //Symbol *Symbol_List;                      //指向符号表的指针，每有一个新的符号表，指针地址向后+1
    int LineNum;
    ifstream Compiled_file;                            //文件输入流
    char Symbol_Buffer[MAX_SYMBOL_LEN];
    Scanner(string s);
    char GetChar();
    void EmptyBuffer();
    void AddBuffer(char a,int i);
    Symbol JudgeSymbol();
    void GetSymbol();
    void Initialize_Scanner();
    ~Scanner();
};
#endif //COMPLIER_SCANNER_H
