#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool updateGeneralCfg(void);
    bool updateIOModuleCfg(void);
    bool updateJsn2Cfg(void);
    bool updateMeterCfg(void);

    void setCfgStructs(char* buf);
    bool setGeneralCfg(void);
    bool setIOModuleCfg(void);
    bool setJsn2Cfg(void);
    bool setMeterCfg(void);

private slots:
    void on_actionOtw_rz_triggered();
    void on_actionZako_cz_triggered();
    void on_actionZapisz_triggered();
    void on_addIoModuleBtn_clicked();
    void on_delIoModuleBtn_clicked();
    void on_addJsn2Btn_clicked();
    void on_delJsn2Btn_clicked();
    void on_addMeterBtn_clicked();
    void on_delMeterBtn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
