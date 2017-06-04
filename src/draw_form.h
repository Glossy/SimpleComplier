#ifndef DRAW_FORM_H
#define DRAW_FORM_H

#include <QWidget>
#include "Parser.h"

namespace Ui {
class Draw_Form;
}

class Draw_Form : public QWidget
{
    Q_OBJECT

public:
    explicit Draw_Form(QWidget *parent = 0);
    ~Draw_Form();
    Parser* parser;
    void GetParser(Parser *s);
private:
    Ui::Draw_Form *ui;
};

#endif // DRAW_FORM_H
