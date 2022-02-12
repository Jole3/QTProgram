#include "examsystem.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

ExamSystem::ExamSystem(QWidget *parent):QDialog(parent)
{
    setWindowTitle("已用时0分0秒");
    initTimer();

    //设置字体大小
    QFont font;
    font.setPointSize(12);
    setFont(font);

    setPalette(QPalette(QColor(209,215,255)));
    setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);     //设置窗体风格
    resize(800,900);    //设置窗体大小
    setFixedSize(width(),height());

    initLayout();
    if(!initText()){
        QMessageBox::information(this,"提示","初始化文件失败，请检查文件！");
    }
    initButtons();
    show();
}

//初始化计时器
void ExamSystem::initTimer()
{
    m_timeGo=0;
    m_timer = new QTimer(this);     //为当前窗体作计时器
    m_timer->setInterval(1000);     //以1秒作为计时器间隔
    m_timer->start();   //启动计时器
    connect(m_timer,SIGNAL(timeout()),this,SLOT(freshTime()));  //将计时器与当前窗体进行信号与槽连接
}

//将时间刷新到标题
void ExamSystem::freshTime()
{
    m_timeGo++;
    QString min = QString::number(m_timeGo/60);
    QString second = QString::number(m_timeGo % 60);

    setWindowTitle("已用时"+ min +"分"+ second +"秒");
}

//初始化考试布局
void ExamSystem::initLayout(){
    m_layout = new QGridLayout(this);   //布局添加到此窗口上
    m_layout->setSpacing(10);
    m_layout->setMargin(10);
}

//初始化文字，从文件中读取题库
bool ExamSystem::initText(){
    int line = 0;     //记录文件中有多少行
    QString fileName("exam.txt");
    QFile file(fileName);
    QTextStream stream(&file);
    stream.setCodec("UTF-8");

    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        text = new QTextEdit(this); //在当前窗口显示文字
        text->setReadOnly(true);    //唯独不可编辑

        QString str;    //保存数据
        QString strLine; //保存答案
        QStringList strList;
        while(!stream.atEnd()){
            //过滤第一行
            if(line == 0){
                stream.readLine();
                line++;
                continue;
            }

            //过滤答案
            if(line>=6 && line<=58 && (line % 6 == 0 || line == 6*10-2)){
                strLine = stream.readLine();
                strList = strLine.split(" ");
                answerList.append(strList.at(1));
                line++;
                str += "\n";
                continue;
            }

            str += stream.readLine();
            str += "\n";
            line++;
        }
        text->setText(str);
        m_layout->addWidget(text,0,0,1,10);     //以一行10列在(0,0)处显示
        file.close();
        return true;
    }else{
        QMessageBox::information(this,"提示","文件打开失败，请检查文件！");
        return false;
    }
}

void ExamSystem::initButtons()
{
    QStringList selectList = {"A","B","C","D"};
    for(int i=0; i<10; i++){
        titleLabel[i] = new QLabel(this);
        titleLabel[i]->setText("第"+QString::number(i+1)+"题");
        m_layout->addWidget(titleLabel[i],1,i);

        if(i == 9){
            radioA = new QRadioButton(this);
            radioB = new QRadioButton(this);
            radioA->setText("正确");
            radioB->setText("错误");
            m_layout->addWidget(radioA,2,9);
            m_layout->addWidget(radioB,3,9);

            //按钮添加分组
            btnGroup[8] = new QButtonGroup(this);
            btnGroup[8]->addButton(radioA);
            btnGroup[8]->addButton(radioB);
        }else{
            if(i!=8){
                btnGroup[i] = new QButtonGroup(this);
            }

            for(int j=0; j<4; j++){
                if(i == 8){
                    //               for(int j=0; j<4; j++){
                    checkBox[j] = new QCheckBox(this);
                    checkBox[j]->setText(selectList.at(j));
                    m_layout->addWidget(checkBox[j],j+2,i);
                }
                else{
                    radioButton[4*i+j] = new QRadioButton(this);
                    radioButton[4*i+j]->setText(selectList.at(j));
                    m_layout->addWidget(radioButton[4*i+j],j+2,i);

                    btnGroup[i]->addButton(radioButton[4*i+j]);
                }
            }
        }/*else{
            for(int k=0; k<4; k++){
                radioButton[(k+1)*(i+1)-1] = new QRadioButton(this);
                radioButton[(k+1)*(i+1)-1]->setText(selectList.at(k));
                m_layout->addWidget(radioButton[(k+1)*(i+1)-1],k+2,i);
            }
        }*/
    }
    submitBtn = new QPushButton(this);
    submitBtn->setText("提交");
    connect(submitBtn,SIGNAL(clicked(bool)),this,SLOT(getScore()));
    m_layout->addWidget(submitBtn,6,9);
}

//判断是否有未选择的题目
bool ExamSystem::hasNoSelect()
{
    int checkNumber = 0;    //用来统计多选题勾选了几个答案
    int radioNumber = 0;    //用来统计单选题勾选了几个答案

    for(int i=0; i<8; i++){
        if(btnGroup[i]->checkedButton()) radioNumber++;
    }

    //多选题
    for(int j=0; j<4; j++){
        if(checkBox[j]->checkState()) checkNumber++;
    }

    if(radioNumber != 8 && checkNumber<=1){
        return true;
    }

    //判断题
    if(!radioA->isChecked() && !radioB->isChecked()) return true;

    return false;
}

//获取分数
void ExamSystem::getScore()
{
    if(hasNoSelect()){
        QMessageBox::information(this,"提示","您有未完成的题目，请完成后再点击提交。","是");
        return;
    }

    int score = 0;

    //判断题
    if(btnGroup[8]->checkedButton()->text() == answerList.at(9))
        score += 10;

    //用来判断多选题是否勾选选项
    bool selectA = checkBox[0]->checkState();
    bool selectB = checkBox[1]->checkState();
    bool selectC = checkBox[2]->checkState();
    bool selectD = checkBox[3]->checkState();

    //用来判断答案中选项
    bool answerA = answerList[8].contains("A");
    bool answerB = answerList[8].contains("B");
    bool answerC = answerList[8].contains("C");
    bool answerD = answerList[8].contains("D");

    if(selectA == answerA && selectB == answerB && selectC == answerC && selectD == answerD) score += 10;

    for(int i=0; i<8; i++){
        if(btnGroup[i]->checkedButton()->text() == answerList.at(i)) score += 10;
    }

    int res = QMessageBox::information(this,"提示","您的分数为:"+QString::number(score),QMessageBox::Yes);

    if(res == QMessageBox::Yes){
        close();
    }
}
