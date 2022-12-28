#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Vector.hpp"
#include "radio_components.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_exit__triggered();

    void on_add_single_to_bd_triggered();

    void on_search_in_bd_triggered();

    void on_pushButton_clicked();

    int on_new_bd_triggered();

    void on_author_triggered();

    void on_delete_some_triggered();

    void on_close_bd_triggered();

    void on_open_bd_triggered(bool);

    void on_save_bd_triggered();

    void on_save_as_bd_triggered();

    void on_edit_single_in_bd_triggered();

    void on_help_and_tips_triggered();

    void on_merge_bd_triggered();

private:
    Ui::MainWindow *ui;
    QString current_file = "";
    Vector<Radio> array;
};
#endif // MAINWINDOW_H
