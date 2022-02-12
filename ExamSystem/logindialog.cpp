#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);  //加载UI
    ui->background->setScaledContents(true);    //图片填充label
    resize(ui->background->width(),ui->background->height());   //将窗体大小设置为与图片大小一致
    setFixedSize(width(),height()); //设置固定大小
    setWindowTitle("驾校科目一考试");  //设置窗体标题
    setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);     //设置窗体风格

//    show();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_login_btn_clicked()
{
    //正则表达式检核邮箱
    //^表示表达式开始，$表示表达式结束，+表示匹配次数≥1，*表示可以匹配任意次数，{n,m}表示匹配次数至少n次，至多m次
    QRegExp ex("^[A-Za-z0-9]+([_\.][a-zA-Z0-9]+)*@([A-Za-z0-9]+\.)+[A-Za-z]{2,6}$");
    bool re = ex.exactMatch(ui->username->text());

    if(re){
        QString fileName;   //文件名
        QString username;   //账号
        QString password;   //密码
        QString strline;    //读取整行
        QStringList list;   //存放读取的数据

        fileName = "user.txt";
        username = ui->username->text();    //读取账号
        password = ui->password->text();    //读取密码
        QFile file(fileName);   // 加载文件
        QTextStream stream(&file);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
            while(!stream.atEnd()){
                strline = stream.readLine();
                list = strline.split(",");   //以逗号分隔数据存入到list中
                if(username == list.at(0)){
                    if(password == list.at(1)){
                        QMessageBox::information(this,"提示","欢迎进入科目一考试!");
                        file.close();
                        done(Accepted); //以用户接受的状态返回，并关闭窗口
                        return;
                    }else{
                        QMessageBox::information(this,"提示","密码输入错误，请重新输入!");
                        ui->password->clear();
                        ui->password->setFocus();
                        file.close();
                        return;
                    }
                }
            }
            QMessageBox::information(this,"提示","账号输入错误，请重新输入!");
            ui->username->clear();
            ui->password->clear();
            ui->username->setFocus();
            file.close();
        }else{
            QMessageBox::information(this,"提示","文件读取失败!");
            return;
        }

    }else{
        QMessageBox::information(this,"提示","账号邮箱输入错误，请重新输入！");
        ui->username->clear();     //清除栏位内容
        ui->username->setFocus();  //重新聚焦
        return;
    }
}

void LoginDialog::on_cancel_btn_clicked()
{
    done(Rejected); //以用户拒绝的状态返回，关闭窗口
}
