#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    filepath = "0";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Draw_Button_clicked()
{
    ui->textBrowser->setText("");
    string url;
    if(filepath == "0"){
        QString str = ui->textEdit->toPlainText();
        if(str=="在这里输入代码\n"){
            QMessageBox::warning(this, tr("Path"),tr("请输入文件"));
            return;
        }
        url = "E:\\Code\\Qt\\Compiler\\tempfile.txt";
        filepath =  QString::fromStdString(url);;
        ofstream file;
        QByteArray ba = str.toLatin1();
        const char *cstr = ba.data();
        file.open(url,ios::in|ios::out|ios::binary|ios::trunc);
        std::string t = cstr;
        file<<t;
        file.close();
    }
    else{
        url = filepath.toStdString();
    }
    Parser *s = new Parser(filepath.toStdString());
    s->FetchToken();
    s->Program();
    s->parser_file.close();
    if(s->error_num != 0){
        QMessageBox::warning(this, tr("画图"),tr("语法分析出错"));
        return;
    }
    Draw_Form *b = new Draw_Form();
    b->setWindowTitle("画图");
    //b->GetParser(s);
    b->show();
    /*painter.setValue(s.draw[s.for_num][0],s.draw[for_num][1],
                                  s.draw[s.for_num][7], s.draw[s.for_num][5],s.draw[s.for_num][6],
                                  s.draw[s.for_num][4],s.draw[s.for_num][2],s.draw[s.for_num][3],
                                  s.x_ptr[s.for_num], s.y_ptr[s.for_num],s.for_num);*/
}

void MainWindow::on_About_action_triggered()
{
    About_Form *s = new About_Form();
    s->setWindowTitle("关于");
    s->show();
}

void MainWindow::on_Exit_action_triggered()
{
    this->close();
}

void MainWindow::on_ViewText_Button_clicked()
{
   QString path = QFileDialog::getOpenFileName(this,tr("打开文件"),".",tr("Text Files(*)")); //打开文件浏览并返回所选择文件路径
   filepath = path;
   if(!path.isEmpty()) {
       QFile file(path);
       if(!file.open(QIODevice::ReadOnly|QIODevice::Text)) {
           QMessageBox::warning(this, tr("Read File"),tr("不能打开文件:\n%1").arg(path));
           return;
       }
       QTextStream in(&file);
       in.setCodec("GB2312");
       ui->textEdit->setText(in.readAll());
       file.close();
   } else {
       QMessageBox::warning(this, tr("Path"),tr("请选择文件"));
       }

}

void MainWindow::on_Scanner_Button_clicked()
{
    ui->textBrowser->setText("");
    string url;
    if(filepath == "0"){
        QString str = ui->textEdit->toPlainText();
        if(str=="在这里输入代码\n"){
            QMessageBox::warning(this, tr("Path"),tr("请输入文件"));
            return;
        }
        url = "E:\\Code\\Qt\\Compiler\\tempfile.txt";
        filepath =  QString::fromStdString(url);;
        ofstream file;
        QByteArray ba = str.toLatin1();
        const char *cstr = ba.data();
        file.open(url,ios::in|ios::out|ios::binary|ios::trunc);
        std::string t = cstr;
        file<<t;
        file.close();
    }
    else{
        url = filepath.toStdString();
    }
    Scanner a(url);
    ofstream files;
    files.open("E:\\Code\\Qt\\Compiler\\scanner.txt",ios::in|ios::out|ios::binary|ios::trunc);
    files<<"SymbolType   String       Constvalue   FunctionPointer"<<endl;
    files<<"______________________________________________________________"<<endl;
    while(1){
        a.GetSymbol();
        if(a.Compiled_file.eof()){
            break;
        }
    };
    int i = 0;
    string temp[] = {"ORIGIN", "SCALE","ROT","IS", "TO",
                     "STEP", "DRAW", "FOR", "FROM",
                     "T",
                     "PLUS", "MINUS", "MUL", "DIV", "POWER",
                     "SEMICO", "L_BRACKET", "R_BRACKET", "COMMA",
                     "FUNC",
                     "CONST_ID",
                     "NONTOKEN",
                     "ERRTOKEN" };
    while(i < a.Symbol_List_Num.size()){
        files<<setw(10)<<temp[a.Symbol_List_Num[i]->type];
        files<<"   "<<setw(10)<<a.Symbol_List_Num[i]->lexeme;
        files<<"   "<<setw(10)<<a.Symbol_List_Num[i]->value;
        switch(int(a.Symbol_List_Num[i]->func)){
        case 0:{
            files<<"   "<<setw(10)<<a.Symbol_List_Num[i]->func<<endl;
            break;
        }
        case 1:{
            files<<"   "<<setw(10)<<"SIN"<<endl;
            break;
        }
        case 2:{
            files<<"   "<<setw(10)<<"COS"<<endl;
            break;
        }
        case 3:{
            files<<"   "<<setw(10)<<"TAN"<<endl;
            break;
        }
        case 4:{
            files<<"   "<<setw(10)<<"LN"<<endl;
            break;
        }
        case 5:{
            files<<"   "<<setw(10)<<"EXP"<<endl;
            break;
        }
        case 6:{
            files<<"   "<<setw(10)<<"SQRT"<<endl;
            break;
        }
        }
        i++;
    }
    files<<"______________________________________________________________"<<endl;
    files.close();
    QString l = QString::fromStdString(a.Symbol_List_Num[1]->lexeme);
    QFile tfile("E:\\Code\\Qt\\Compiler\\scanner.txt");
    if(!tfile.open(QFile::ReadOnly | QFile::Text))
        qDebug() << "Can not open";
    QTextStream in(&tfile);
    ui->textBrowser->append(tfile.readAll());
    //ui->textBrowser->append(l);
}



void MainWindow::on_Open_action_triggered()
{
    MainWindow::on_ViewText_Button_clicked();
}

void MainWindow::on_Parser_Button_clicked()
{
    ui->textBrowser->setText("");
    string url;
    if(filepath == "0"){
        QString str = ui->textEdit->toPlainText();
        if(str=="在这里输入代码\n"){
            QMessageBox::warning(this, tr("Path"),tr("请输入文件"));
            return;
        }
        url = "E:\\Code\\Qt\\Compiler\\tempfile.txt";
        filepath =  QString::fromStdString(url);;
        ofstream file;
        QByteArray ba = str.toLatin1();
        const char *cstr = ba.data();
        file.open(url,ios::in|ios::out|ios::binary|ios::trunc);
        std::string t = cstr;
        file<<t;
        file.close();
    }
    else{
        url = filepath.toStdString();
    }
    Parser s(filepath.toStdString());
    s.FetchToken();
    s.Program();
    s.parser_file<<" =================build finished: ("<<s.error_num<<") errors================="<<endl;
    s.parser_file.close();
    QFile pfile("E:\\Code\\Qt\\Compiler\\parser.txt");
    if(!pfile.open(QFile::ReadOnly | QFile::Text))
        qDebug() << "Can not open parser file";
    QTextStream in(&pfile);
    ui->textBrowser->append(in.readAll());
}

void MainWindow::on_Scanner_action_triggered()
{
   MainWindow::on_Scanner_Button_clicked();
}

void MainWindow::on_Parser_action_triggered()
{
    MainWindow::on_Parser_Button_clicked();
}


