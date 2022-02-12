#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginDialog; }     //继承自UI_LoginDialog类，用于描述登录信息
QT_END_NAMESPACE

class LoginDialog : public QDialog
{
    Q_OBJECT    //实现信号与槽，可以与其他窗口进行通信

public:
    LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:     //私有的槽方法
    void on_login_btn_clicked();

    void on_cancel_btn_clicked();

private:
    Ui::LoginDialog *ui;
};
#endif // LOGINDIALOG_H
