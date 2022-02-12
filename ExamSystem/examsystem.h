#ifndef EXAMSYSTEM_H
#define EXAMSYSTEM_H

#include <QDialog>
#include <QTimer>
#include <QGridLayout>
#include <QTextEdit>
#include <QRadioButton>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QButtonGroup>
#include <QStringList>

class ExamSystem : public QDialog
{
    Q_OBJECT

public:
    ExamSystem(QWidget *parent=nullptr);
    void initTimer();
    void initLayout();
    bool initText();
    void initButtons();
    bool hasNoSelect();

private:
    QTimer *m_timer;                //计时器
    int m_timeGo;                   //已用时
    QGridLayout *m_layout;          //布局对象
    QTextEdit *text;                //题目内容
    QLabel *titleLabel[10];         //选项标题
    QRadioButton *radioButton[32];  //32个单选选项
    QCheckBox *checkBox[4];         //4个多选选项
    QRadioButton *radioA;           //判断题A选项
    QRadioButton *radioB;           //判断题B选项
    QPushButton *submitBtn;         //提交按钮
    QButtonGroup *btnGroup[9];      //按钮分组
    QStringList answerList;         //存放答案

private slots:
    void freshTime();
    void getScore();
};

#endif // EXAMSYSTEM_H
