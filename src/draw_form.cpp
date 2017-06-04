#include "draw_form.h"
#include "ui_draw_form.h"

Draw_Form::Draw_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Draw_Form)
{
    ui->setupUi(this);
    QVector<double> x(120),y(120);//分别存放x和y坐标的数据,101为数据长度
    for(double i = 0;i < 100; i++){
        x[i] = cos(i);
        y[i] = sin(i);
    }
    //向绘图区域QCustomPlot(从widget提升来的)添加一条曲线
     ui->widget->addGraph();
     /*ui->widget->addGraph();//添加第二条曲线
     for(int yy=-20;yy<20;yy++)
     {
         a[yy] = -yy;
         b[yy] = yy;
     }
     ui->widget->graph(1)->setData(a,b);
     //添加数据*/
     ui->widget->graph(0)->setData(x,y);

     //设置坐标轴标签名称
     ui->widget->xAxis->setLabel("x");
     ui->widget->yAxis->setLabel("y");

     //设置坐标轴显示范围,否则我们只能看到默认的范围
     ui->widget->xAxis->setRange(-8,8);
     ui->widget->yAxis->setRange(-4,4); 
}

Draw_Form::~Draw_Form()
{
    delete ui;
}
void Draw_Form::GetParser(Parser *s){
    parser = s;
    cout<<s->Start<<"    "<<s->End<<"     "<<s->Step<<endl;
    cout<<"scalex  "<<s->Scale_x<<"   scaley  "<<s->Scale_y<<endl;
    cout<<"originx  "<<s->Origin_x<<"   originy   "<<s->Origin_y<<endl;
    cout<<"  rot  "<<s->Rot_angle<<endl;
    cout<<"lfunc   "<<s->x_ptr->MathFuncPtr<<endl;
    cout<<"rfunc   "<<s->y_ptr->MathFuncPtr;

    //QVector<double> x(101),y(101);//分别存放x和y坐标的数据,101为数据长度
    //for(int i = 0;i < 10; i++){
        /*switch(int(s->x_ptr->MathFuncPtr)){
        case 0:{
            x[i] = 0;
            break;
        }
        case 1:{
            x[i] = (sin(i)+s->Origin_x)*s->Scale_x;
            break;
        }
        case 2:{
            x[i] = (cos(i)+s->Origin_x)*s->Scale_x;
            break;
        }
        }
        switch(int(s->y_ptr->MathFuncPtr)){
        case 0:{
            y[i] = 0;
            break;
        }
        case 1:{
            y[i] = (sin(i)+s->Origin_y)*s->Scale_y;
            break;
        }
        case 2:{
            y[i] = (cos(i)+s->Origin_y)*s->Scale_y;
            break;
        }
        }
    }*/
}

