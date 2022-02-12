#include "logindialog.h"
#include "examsystem.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginDialog loginDialog;
    int res = loginDialog.exec();     //登录窗口以模态方式运行
    if(res == QDialog::Accepted){
        ExamSystem *examSystem;
        examSystem = new ExamSystem;
    }else {
        return 0;
    }

    return a.exec();
}
