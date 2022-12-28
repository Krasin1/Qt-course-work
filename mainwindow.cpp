    #include "mainwindow.h"
#include "pop_up.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QFileInfo>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setColumnWidth(0, 150);
    ui->tableWidget->setColumnWidth(1, 150);
    ui->tableWidget->setColumnWidth(2, 200);
    setWindowTitle("База данных радиодеталей");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_exit__triggered()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Выход", "Вы действительно хотите выйти?",
                                                              QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    } else  {
        ui->statusbar->showMessage("отказался выходить");
    }
}


void MainWindow::on_add_single_to_bd_triggered()
{
    Radio single{};
    pop_up window(nullptr, &single);
    window.setModal(true);
    window.exec();
    if (single.specifications != "" && single.cost != 0 && single.type != "") {
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(single.type));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(QString::number(single.cost)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, new QTableWidgetItem(single.specifications));
        array.push_back(single);
        ui->statusbar->showMessage("Элемент добавлен");
    } else {
        ui->statusbar->showMessage("Элемент не добавлен");
    }


}


void MainWindow::on_search_in_bd_triggered()
{
    MainWindow::on_pushButton_clicked();
}


void MainWindow::on_pushButton_clicked()
{
    QString arg1 = ui->lineEdit->text();
    ui->tableWidget->setCurrentCell(-1, -1);
    if (arg1 == "") {
        return;
    }
    ui->tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::MultiSelection);
    auto find_items = ui->tableWidget->findItems(arg1, Qt::MatchContains);
    int len = find_items.size();
    for (int i = 0; i < len; ++i) {
        auto item = find_items.at(i);
        ui->tableWidget->setItemSelected(item, true);
    }
    ui->tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->statusbar->showMessage("Найдено " + QString::number(len) + " ячеек");
}


int MainWindow::on_new_bd_triggered()
{
    if (ui->tableWidget->rowCount() > 0) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Вы уверены, что хотите создать новый файл?\nУ вас еще остались не сохраненные данные.");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        if (msgBox.exec() == QMessageBox::No) {
            return 0;
        }
    }
    ui->tableWidget->setRowCount(0);
    array.clear();
    current_file = "";
    return 1;
}


void MainWindow::on_author_triggered()
{
    QMessageBox::about(this,
                       "О программе",
                       "Курсовая работа по дисциплине ООП\n"
                       "Тема: класс характеризующий радиодетали \n"
                       "Вариант 5\n"
                       "Выполнил студент группы ИКПИ-14\n"
                       "Дунаев Владислав\n"
                       "Санкт-Петербург\n"
                       "2022 год");

}


void MainWindow::on_delete_some_triggered()
{
    auto list = ui->tableWidget->selectionModel()->selectedRows();
    if (list.size() > 0) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Вы уверены, что хотите удалить эти строки?");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        if (msgBox.exec() == QMessageBox::Yes) {
            for (auto k = list.rbegin(); k != list.rend(); ++k) {
                auto idx = (*k).row();
                array.erase(idx);
                ui->tableWidget->removeRow(idx);
            }
            ui->statusbar->showMessage("Запись удалена");
        }
    } else ui->statusbar->showMessage("Выделите всю строку");

}


void MainWindow::on_close_bd_triggered()
{
    if (ui->tableWidget->rowCount() > 0) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Вы уверены, что хотите закрыть таблицу?");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        if (msgBox.exec() == QMessageBox::Yes) {
            ui->tableWidget->setRowCount(0);
            array.clear();
            ui->statusbar->showMessage("Таблица закрыта");
            current_file = "";
        }
    } else ui->statusbar->showMessage("Таблица и так пустая");
}


void MainWindow::on_open_bd_triggered(bool isflag = false)
{
    QString file_name = QFileDialog::getOpenFileName(this, "Открыть файл...", ".", "text files (*.txt);;All files (*.*);;");
    QFileInfo check_file(file_name);
    if (check_file.exists() && check_file.isFile()) {
        if (!isflag) {
            if(!MainWindow::on_new_bd_triggered()) {
                return;
            }

        }
        QFile file(file_name);
        if (file.open(QIODevice::ReadOnly)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                Radio t;
                QString line = in.readLine();
                QStringList fields = line.split(";");
                if (fields.size() == 3) {
                    t.type = fields[0].simplified();
                    t.cost = fields[1].simplified().toInt();
                    t.specifications = fields[2].simplified();

                    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(t.type));
                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(QString::number(t.cost)));
                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, new QTableWidgetItem(t.specifications));
                    array.push_back(t);
                }
            }
            file.close();
            ui->statusbar->showMessage("Записи из файла добавлены");
            current_file = file_name;
        } else ui->statusbar->showMessage("Файл '" + file_name + "' не удалось открыть на чтение (" + file.errorString() + ")");
    } else ui->statusbar->showMessage("Файл '" + file_name + "' не существует");

}


void MainWindow::on_save_bd_triggered()
{
    if (current_file == "") {
        MainWindow::on_save_as_bd_triggered();
        return;
    }
    QFile file(current_file);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        int len = ui->tableWidget->rowCount();
        for (int i = 0; i < len; ++i) {
            QString type = ui->tableWidget->item(i, 0)->text();
            QString cost = ui->tableWidget->item(i, 1)->text();
            QString specs = ui->tableWidget->item(i, 2)->text();
            out  << type << ";" << cost << ";" << specs << "\n";
        }
        file.close();
        ui->statusbar->showMessage("Файл записан");
    }
}


void MainWindow::on_save_as_bd_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Сохранить файл...", ".", "text files (*.txt);;All files (*.*);;");
    if(!file_name.endsWith(QString(".txt")))
         file_name.append(QString(".txt"));
    if (file_name != "") {
        current_file = file_name;
        MainWindow::on_save_bd_triggered();
    }

}


void MainWindow::on_edit_single_in_bd_triggered()
{
    auto list = ui->tableWidget->selectedItems();
    if (list.size() == 3) {
        Radio single{};
        single.type = list.at(0)->text();
        single.cost = list.at(1)->text().toInt();
        single.specifications = list.at(2)->text();
        pop_up window(nullptr, &single);
        window.setModal(true);
        window.exec();

        if (single.type != "" || single.cost != 0 || single.specifications != "")
        {
            list.at(0)->setText(single.type);
            list.at(1)->setText(QString::number(single.cost));
            list.at(2)->setText(single.specifications);

            array[list.at(0)->row()] = single;

            ui->statusbar->showMessage("Запись отредактирована");
        }
    }
    ui->statusbar->showMessage("Выделите всю строку");

}


void MainWindow::on_help_and_tips_triggered()
{
    QMessageBox::information(this, "Help", "Подсказки не нужны\nИ так все просто и понятно");
}


void MainWindow::on_merge_bd_triggered()
{
    QString old_file = current_file;
    MainWindow::on_open_bd_triggered(true);
    current_file = old_file;
    ui->statusbar->showMessage("Данные объединены");
    setWindowTitle("*" + current_file + " – Функции языка программирования");

}

