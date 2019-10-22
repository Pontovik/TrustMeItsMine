#include "reg.h"
#include <mainwindow.h>
#include <QtWidgets>
#include"admindialog.h"
#include"cookdialog.h"
#include"customerdialog.h"
#include<cstdlib>
//! [0]
reg::reg(QWidget *parent)
    : QDialog(parent),
      Login(new QLineEdit),
      Password(new QLineEdit)
{
    User::readFromFile();

    auto logLabel = new QLabel(tr("Логин"));

     auto pasLabel = new QLabel(tr("Пароль"));
    auto enterButton = new QPushButton(tr("Вход"));
    auto cancelButton = new QPushButton("Отмена");
auto regButton = new QPushButton(tr("Регистрация"));

    auto gLayout = new QGridLayout;
    gLayout->setColumnStretch(1, 3);
    gLayout->addWidget(logLabel, 0, 0);
    gLayout->addWidget(Login, 0, 1);
    gLayout->addWidget(pasLabel, 1, 0, Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(Password, 1, 1, Qt::AlignLeft);


    auto buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(enterButton);
    buttonLayout->addWidget(regButton);
    buttonLayout->addWidget(cancelButton);


    gLayout->addLayout(buttonLayout, 2, 1, Qt::AlignRight);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    connect(enterButton, SIGNAL(clicked()),this,SLOT(enter()));
    connect(regButton, SIGNAL(clicked()),this,SLOT(registr()));
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

    setWindowTitle("Авторизация");
}

QString reg::log() const
{
    return Login->text();
}

QString reg::pas() const
{
    return Password->text();
}
void reg::registr(){
    User*current = new User();
    current->SetLogin(log());current->SetPassword(pas());
    if(checkLog(current)==1){
        QMessageBox::warning(this,"Vozvrat","Такой логин уже существует, попробуйте другой");

    }
    else {
        User::users->append(*current);
        QMessageBox::warning(this,"Vozvrat","Теперь можете попробовать войти");
        this->hide();
        reg*yes=new reg();
        yes->show();
        User::writeToFile();
    }

}


void reg::enter(){
    User*current = new User();
current->SetLogin(log());current->SetPassword(pas());
if(current->GetLogin()=="admin"&&current->GetPassword()=="admin"){
    QMessageBox::warning(this,"Vozvrat","Вы админ");
    admindialog*temp = new admindialog;
      temp->show();
      return;
}
if(current->GetLogin()=="cook"&&current->GetPassword()=="cook"){
    QMessageBox::warning(this,"Vozvrat","Вы повар");
    dialogcook*temp = new dialogcook;
    temp->show();
     return;
}
if(checkAll(current)==1){
    QMessageBox::warning(this,"Vozvrat","Вы успешно вошли в систему");
    customerdialog*temp = new customerdialog;
      temp->show();
       return;
}
else{
   QMessageBox::warning(this,"Vozvrat","Такого логина или пароля не существует");

}

}

int reg::checkLog(User*ya){
    if(User::users->isEmpty())
        return 0;
     int u=0;
        for(int i=0;i<User::users->count();i++){

            if(ya->GetLogin()==User::users->at(i).GetLogin()){
               u=1;
               return u;
            }


        }
        return u;
}
int reg::checkAll(User *ya){
    if(User::users->isEmpty())
        return 0;
     int u=0;


        for(int i=0;i<User::users->count();i++){

            if(ya->GetLogin()==User::users->at(i).GetLogin() && ya->GetPassword()==User::users->at(i).GetPassword()){
               u=1;
               return u;
            }

        }
        return u;

}

//! [0]
