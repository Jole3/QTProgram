/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QLabel *background;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *username;
    QLineEdit *password;
    QPushButton *login_btn;
    QPushButton *cancel_btn;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QString::fromUtf8("LoginDialog"));
        LoginDialog->resize(800, 600);
        background = new QLabel(LoginDialog);
        background->setObjectName(QString::fromUtf8("background"));
        background->setGeometry(QRect(0, 0, 651, 411));
        background->setPixmap(QPixmap(QString::fromUtf8(":/login.png")));
        label = new QLabel(LoginDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(220, 180, 31, 21));
        label_2 = new QLabel(LoginDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(220, 220, 31, 16));
        username = new QLineEdit(LoginDialog);
        username->setObjectName(QString::fromUtf8("username"));
        username->setGeometry(QRect(260, 180, 141, 21));
        password = new QLineEdit(LoginDialog);
        password->setObjectName(QString::fromUtf8("password"));
        password->setGeometry(QRect(260, 220, 141, 21));
        password->setEchoMode(QLineEdit::Password);
        login_btn = new QPushButton(LoginDialog);
        login_btn->setObjectName(QString::fromUtf8("login_btn"));
        login_btn->setGeometry(QRect(160, 280, 93, 28));
        cancel_btn = new QPushButton(LoginDialog);
        cancel_btn->setObjectName(QString::fromUtf8("cancel_btn"));
        cancel_btn->setGeometry(QRect(410, 280, 93, 28));

        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "LoginDialog", nullptr));
        background->setText(QString());
        label->setText(QCoreApplication::translate("LoginDialog", "\350\264\246\345\217\267", nullptr));
        label_2->setText(QCoreApplication::translate("LoginDialog", "\345\257\206\347\240\201", nullptr));
        login_btn->setText(QCoreApplication::translate("LoginDialog", "\347\231\273\345\275\225", nullptr));
        cancel_btn->setText(QCoreApplication::translate("LoginDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
