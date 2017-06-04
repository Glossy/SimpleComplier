//
// Created by Wu on 2016/12/6.
//

#include "Parser.h"

Parser::Parser(string url) {
    cout<<"Initialize Parser"<<endl;
    for_num = 0;
    Symbol_num = 0;
    error_num = 0;
    scanner = new Scanner(url);
    while(1) {
            scanner->GetSymbol();
            if (scanner->Compiled_file.eof()) {
                break;
            }
        }
    parser_file.open("E:\\Code\\Qt\\Compiler\\parser.txt",ios::in|ios::binary|ios::trunc);
    if (! parser_file.is_open()) {
        QMessageBox::warning(NULL, "Parser","Error opening file");
        return;
    }
}

void Parser::FetchToken() {
    //(*scanner).GetSymbol();
    temp = (*scanner).Symbol_List_Num[Symbol_num];
    string t[] = {"ORIGIN", "SCALE","ROT","IS", "TO",
                     "STEP", "DRAW", "FOR", "FROM",
                     "T",
                     "PLUS", "MINUS", "MUL", "DIV", "POWER",
                     "SEMICO", "L_BRACKET", "R_BRACKET", "COMMA",
                     "FUNC",
                     "CONST_ID",
                     "NONTOKEN",
                     "ERRTOKEN" };
    //parser_file<<setw(10)<<t[temp->type]<<" "<<setw(10)<<temp->lexeme<<" "<<setw(8)<<temp->value<<" ";
    switch(int(temp->func)){
    case 0:{
        parser_file<<"   "<<setw(8)<<temp->func<<endl;
        break;
    }
    case 1:{
        parser_file<<"   "<<setw(8)<<"SIN"<<endl;
        break;
    }
    case 2:{
        parser_file<<"   "<<setw(8)<<"COS"<<endl;
        break;
    }
    case 3:{
        parser_file<<"   "<<setw(8)<<"TAN"<<endl;
        break;
    }
    case 4:{
        parser_file<<"   "<<setw(8)<<"LN"<<endl;
        break;
    }
    case 5:{
        parser_file<<"   "<<setw(8)<<"EXP"<<endl;
        break;
    }
    case 6:{
        parser_file<<"   "<<setw(8)<<"SQRT"<<endl;
        break;
    }
    }
    Symbol_num++;
    if(temp->type == ERRTOKEN){
        SyntaxError(0);                     //非法符号
    }
}
void Parser::MatchToken(enum Symbol_Type AToken) {
    if(temp->type == NONTOKEN){return; }
    if ((*temp).type != AToken) SyntaxError(1);
    FetchToken();
}
void Parser::SyntaxError(int case_of) {
    error_num++;
    switch(case_of) {
    case 0:	{
        parser_file<<" Illegal symbol  Line Number:"<<temp->Line_num<<endl ;
        break;
        }
    case 1:{
        parser_file<<"Not expected symbol  Line Number:"<<temp->Line_num<<endl;
        break;
        }
    }
}
void Parser::PrintSyntaxTree(Tree* root, int depth){
    int		temp;
    for (temp=1; temp<= depth; temp++) printf("\t");	// 缩进
    switch(root->Opcode)								// 打印根节点
    {	case PLUS:      parser_file<<"+"<<endl;	break;
        case MINUS:     parser_file<<"-"<<endl;	break;
        case MUL:       parser_file<<"*"<<endl;	break;
        case DIV:       parser_file<<"/"<<endl;	break;
        case POWER:     parser_file<<"**"<<endl; break;
        case FUNC:      parser_file<<root->MathFuncPtr<<endl;
            break;
        case CONST_ID:  parser_file<<root->CaseConst<<endl;
            break;
        case T:         parser_file<<"T"<<endl;
            break;
        default:        parser_file<<"Error Tree Node !"<<endl;
            return;
    }
    if(root->Opcode == CONST_ID || root->Opcode == T)	// 叶子节点返回
        return ;
    if(root->Opcode == FUNC)		// 递归打印一个孩子的节点
        PrintSyntaxTree(root->child,depth+1);
    else							// 递归打印两个孩子的节点
    {	PrintSyntaxTree(root->Left,  depth+1);
        PrintSyntaxTree(root->Right, depth+1);
    }
}

void Parser::Program() {                                              //语法分析器主体
    while (temp->type != NONTOKEN&&this->Symbol_num <= scanner->Symbol_List_Num.size()) {
        Statement () ;
        MatchToken (SEMICO) ;
    }
}

void Parser::Statement() {
    switch (temp->type) {
        case ORIGIN	:	OriginStatement();	break ;
        case SCALE  :	ScaleStatement();	break ;
        case ROT    :	RotStatement();		break ;
        case FOR    :	ForStatement();		break ;
        default     :	SyntaxError(1);
    }
}

void Parser::OriginStatement() {
    Tree *tmp;
    MatchToken (ORIGIN);
    MatchToken (IS);
    MatchToken (L_BRACKET);
    tmp = Expression();
    Origin_x = GetExprValue(tmp);		// 获取横坐标的平移距离
    DelExprTree(tmp);
    MatchToken (COMMA);
    tmp = Expression();
    Origin_y = GetExprValue(tmp);		// 获取纵坐标的平移距离
    DelExprTree(tmp);
    MatchToken (R_BRACKET);
}

void Parser::RotStatement() {
    Tree *tmp;
    MatchToken (ROT);
    MatchToken (IS);
    tmp = Expression();
    Rot_angle = GetExprValue(tmp);		// 获取旋转角度
    DelExprTree(tmp);
}

void Parser::ScaleStatement() {
    Tree *tmp;
    MatchToken (SCALE);
    MatchToken (IS);
    MatchToken (L_BRACKET);
    tmp = Expression();
    Scale_x = GetExprValue(tmp);		// 获取横坐标的比例因子
    DelExprTree(tmp);
    MatchToken (COMMA);
    tmp = Expression();
    Scale_y = GetExprValue(tmp);		// 获取纵坐标的比例因子
    DelExprTree(tmp);
    MatchToken (R_BRACKET);
}

void Parser::ForStatement() {
    MatchToken (FOR);
    MatchToken(T);
    MatchToken (FROM);
    start_ptr = this->Expression();			// 构造参数起始表达式语法树
    Start = GetExprValue(start_ptr);	// 计算参数起始表达式的值
    //DelExprTree(start_ptr);
    MatchToken (TO);
    end_ptr = this->Expression();				// 构造参数终结表达式语法树
    End = GetExprValue(end_ptr);		// 计算参数结束表达式的值
    //DelExprTree(end_ptr);
    MatchToken (STEP);
    step_ptr = this->Expression();			// 构造参数步长表达式语法树
    Step = GetExprValue(step_ptr);		// 计算参数步长表达式的值
    //DelExprTree(step_ptr);
    MatchToken (DRAW);
    MatchToken (L_BRACKET);
    x_ptr = this->Expression();	  			// 构造横坐标表达式语法树
    MatchToken (COMMA);
    y_ptr = this->Expression(); 				// 构造纵坐标表达式语法树
    MatchToken (R_BRACKET);
    //DrawLoop (Start, End, Step, x_ptr, y_ptr); // 绘制图形
    //DelExprTree(x_ptr);					// 释放横坐标语法树所占空间
    //DelExprTree(y_ptr);
    for_num++;
}

Tree *Parser::Expression() {        // + -
    Tree *left, *right;		// 左右子树节点的指针
    Symbol_Type token_tmp;				// 当前记号
    left = Term();						// 分析左操作数且得到其语法树
    while (temp->type==PLUS || temp->type==MINUS)
    {	token_tmp = temp->type;
        MatchToken(token_tmp);
        right = Term();					// 分析右操作数且得到其语法树
        left = MakeExprNode(token_tmp, left, right);            // 构造运算的语法树，结果为左子树
    }
    PrintSyntaxTree(left,1);					// 打印表达式的语法树
    return left;
}

Tree *Parser::Term() {      // * /
    	Tree *left, *right;
        Symbol_Type token_tmp;
        left = Factor();
        while (temp->type==MUL
               || temp->type==DIV) {
            token_tmp = temp->type;
            MatchToken(token_tmp);
            right = Factor();
            left = MakeExprNode(token_tmp, left, right);
        }
        return left;
    }

Tree* Parser::Factor() {            //+ -
    Tree *left, *right;
    if(temp->type == PLUS){ 		// 匹配一元加运算
    	MatchToken(PLUS);
        right = Factor();			//  表达式退化为仅有右操作数的表达式
    }
    else if(temp->type == MINUS)	// 匹配一元减运算
    {   MatchToken(MINUS); 			// 表达式转化为二元减运算的表达式
        right = Factor();
        left = new Tree(CONST_ID);
        left->CaseConst = 0.0;
        right = MakeExprNode(MINUS, left, right);
    }
    else right = Component();		// 匹配非终结符Component
    return right;
}

Tree *Parser::Component() {
    Tree *left, *right;
    left = Atom();
    if(temp->type == POWER)
    {	MatchToken(POWER);
        right = Component();	// 递归调用Component以实现POWER的右结合
        left = MakeExprNode(POWER, left, right);
    }
    return left;
}

Tree *Parser::Atom() {
    Symbol s = *temp;
    Tree *address,*tmp;
    switch (temp->type)
    {	case CONST_ID :
            MatchToken (CONST_ID) ;
            address = MakeExprNode(CONST_ID,s.value);
            break;
        case T:
            MatchToken(T);
            address = MakeExprNode(T);
            break;
        case FUNC :
            MatchToken (FUNC);
            MatchToken (L_BRACKET);
            tmp = Expression ();
            address = MakeExprNode(FUNC,s.func,tmp);
            MatchToken (R_BRACKET);
            break ;
        case L_BRACKET :
            MatchToken (L_BRACKET);
            address = Expression();
            MatchToken (R_BRACKET);
            break ;
        default :
            SyntaxError (1);
    }
    return address;
}
Tree *Parser::MakeExprNode(Symbol_Type opcode,...) {
    Tree* ExprPtr = new Tree(opcode);
    va_list ArgPtr ;                //声明参数指针
    va_start (ArgPtr, opcode);      //将参数指针设置为第一个参数
    switch(opcode){					// 根据记号的类别构造不同的节点
    	case CONST_ID: {                 // 常数节点
            ExprPtr->CaseConst = (double) va_arg(ArgPtr, double);
            cout<<endl;
        }
        case T: {                            // 参数节点
            ExprPtr->CaseParmPtr = &(Start); //传入的为T启示值地址
        }
        case FUNC: {                    // 函数调用节点
            ExprPtr->MathFuncPtr = (double)va_arg(ArgPtr,double);
            ExprPtr->child = (Tree *) va_arg (ArgPtr, Tree *);
            break;
        }
        default:					// 二元运算节点
            ExprPtr->Left = (Tree *)va_arg (ArgPtr,Tree *);
            ExprPtr->Right = (Tree *)va_arg (ArgPtr,Tree *);
           break;
    }
    va_end(ArgPtr);
    return ExprPtr;
}

Tree::Tree(Symbol_Type a) {
    Opcode = a;
    Left = NULL;
    Right = NULL;
    child = NULL;
}
int Parser::get_deepth(Tree *root)
{
    int left, right;
    if (root != NULL) {
        left = 0;
        if (root->Left != NULL) {
            left += get_deepth(root->Left);
        }
        right = 0;
        if (root->Right != NULL) {
            right += get_deepth(root->Right);
        }
        return (left < right ? right : left)+1 ;
    }else {
        return -1;
    }
}

void Parser::DelExprTree(Tree *a) {
    if (a == NULL) return;
    switch (a ->Opcode)
    {   case PLUS  :
        case MINUS :
        case MUL   :
        case DIV   :
        case POWER :
            DelExprTree (a->Left ) ;
            DelExprTree (a->Right) ;
            break ;
        case FUNC  : 			// 一个孩子的内部节点
            DelExprTree (a->child) ;
            break ;
        default    : 			// 叶子节点
            break ;
    }
    delete(a) ;				// 删除叶子节点
}

double Parser::GetExprValue(Tree *a) {
    if (a == NULL) return 0.0;
    switch (a -> Opcode)
    {	case PLUS  :
            return GetExprValue(a->Left ) + GetExprValue(a->Right) ;
        case MINUS :
            return GetExprValue(a->Left ) - GetExprValue(a->Right) ;
        case MUL   :
            return GetExprValue(a->Left ) * GetExprValue(a->Right) ;
        case DIV   :
            return GetExprValue(a->Left ) / GetExprValue(a->Right) ;
        case POWER :
            return pow(GetExprValue(a->Left ), GetExprValue(a->Right) );
        case FUNC  :
            return (GetExprValue(a->child) );
        case CONST_ID :
            return a->CaseConst ;
        case T  :
            return *(a->CaseParmPtr);
        default    :
            return 0.0 ;
    }
}
void Parser::DrawLoop(double Start, double End, double Step, Tree * HorPtr, Tree * VerPtr)
{
    double x, y;
    //for(Parameter = Start; Parameter <= End; Parameter += Step)
    //{	CalcCoord(HorPtr, VerPtr, x, y);
        //DrawPixel((unsigned long)x, (unsigned long)y);
    //}
}
