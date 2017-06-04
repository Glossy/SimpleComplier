//
// Created by Wu on 2016/12/6.
//

#ifndef COMPLIER_PARSER_H
#define COMPLIER_PARSER_H

#include "Scanner.h"
#include <stdarg.h>

class Tree;
class Parser{
public:
    int for_num;
    //double draw [4][3];
    double	 Origin_x=0,  Origin_y=0,			// 横、纵平移距离
             Scale_x=1, 	 Scale_y=1,     	    // 横、纵比例因子
             Rot_angle=0,
             Start = 0, End = 0,  Step = 0;
    Tree *start_ptr;
    Tree *end_ptr;
    Tree *step_ptr;
    Tree *x_ptr;
    Tree *y_ptr;		// 各表达式语法树根节点指针
    Parser(string url);
    Symbol *temp;
    Scanner* scanner;
    ofstream parser_file;
    int error_num;
    int Symbol_num; //记录读取的Symbol数
    void FetchToken();
    void MatchToken(enum Symbol_Type AToken);
    void SyntaxError(int case_of);
    void PrintSyntaxTree(Tree* root, int indent);
    void Program();
    void Statement();
    void OriginStatement();
    void RotStatement();
    void ScaleStatement();
    void ForStatement();
    Tree* Expression();
    Tree* Term();
    Tree* Factor();
    Tree* Component();
    Tree* Atom();
    Tree* MakeExprNode(Symbol_Type opcode,...);
    int get_deepth(Tree *root);
    void DelExprTree(Tree *a);
    void DrawLoop(double Start, double End, double Step, Tree * HorPtr, Tree * VerPtr);
    double GetExprValue(Tree* a);
};

class Tree{                                                             //构建语法树所有节点的抽象父类Tree
public:
    Tree(Symbol_Type a);
    enum Symbol_Type Opcode;
    Tree* Left;
    Tree* Right;
    Tree* child;
    double MathFuncPtr;
    double CaseConst;
    double* CaseParmPtr;
    //virtual void accept(Vistor C);
};
/*class CaseOpertator:public Tree{                                                //语法树二元运算节点
public:
    CaseOpertator(Symbol_Type a);
    Tree* Left;
    Tree* Right;
    //void accept(Vistor C);
};
class CaseFunc:public Tree{                                                     //语法树函数调用节点
public:
    CaseFunc(Symbol_Type a);
    Tree* child;
    double MathFuncPtr;
    //void accept(Vistor C);
};
class CaseConst:public Tree{                                                    //语法树常数节点，绑定右值
public:
    CaseConst(Symbol_Type a);
    double caseconst;
    //void accept(Vistor C);
};
class CaseParmPtr:public Tree{                                                  //语法树参数T节点，绑定左值
public:
    CaseParmPtr(Symbol_Type a);
    double* caseparmptr;
    //void accept(Vistor C);
};
*/
#endif //COMPLIER_PARSER_H
