#ifndef CUSERSCFGFORM_H
#define CUSERSCFGFORM_H

#include <QWidget>

namespace Ui {
class CUsersCfgForm;
}

class CUsersCfgForm : public QWidget
{
    Q_OBJECT

public:
    explicit CUsersCfgForm(QWidget *parent = 0);
    ~CUsersCfgForm();

private:
    Ui::CUsersCfgForm *ui;
};

#endif // CUSERSCFGFORM_H
