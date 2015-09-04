#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_menuTreeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_actionZako_cz_triggered();

private:
    Ui::MainWindow *ui;

<<<<<<< HEAD
    QTreeWidgetItem* addForm(QString name, QWidget* widget, int id);
=======
    QTreeWidgetItem* addForm(QString name, QWidget* widget, int id1, int id2, QTreeWidgetItem *parent);
>>>>>>> cde5f3bd530c0347019060c8255fafc7521bedd2
};

#endif // MAINWINDOW_H
