#include "User.h"
#include <QtWidgets>
#include <QMessageBox>
QList<User>* User::users=new QList<User>;
using namespace std;
User::User()
{
    Login = "";
   Password = "";
}
