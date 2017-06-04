#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "draw_form.h"
#include "about_form.h"
#include "qcustomplot.h"

#define STACK_SIZE 10
#define BASIC_ORIGIN_X 30
#define BASIC_ORIGIN_Y 780
#define BASIC_WIDTH  750
#define BASIC_HIGHTH 780            //默认值
#define SCALE      50


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    bool loadFile(const QString &fileName); // 加载文件
    QString filepath; //保存文件路径
    ~MainWindow();
private slots:
    void on_Draw_Button_clicked();

    void on_About_action_triggered();

    void on_Exit_action_triggered();

    void on_ViewText_Button_clicked();

    void on_Scanner_Button_clicked();

    void on_Open_action_triggered();

    void on_Parser_Button_clicked();

    void on_Scanner_action_triggered();

    void on_Parser_action_triggered();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
