#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <time.h>
#include <stdint.h>
#include <iostream>
#include <QRadioButton>
#include <QTextEdit>
#include <QTableView>
#include <QStandardItemModel>
#include <string>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setup();

private:
    Ui::MainWindow *ui;
    void generateIdList();
    void generateStoryListWithDupes();
    void generateStoryListWithoutDupes();
    void setupTable();

    int storyList[100];
    int storyIdList[100];
    QRadioButton* allowDupesRadioButton;
    QTextEdit* seedTextEdit;
    QTableView* storyListTableView;
    QStandardItemModel* dataModel;

private slots:
    void generateButtonClicked();


};

#endif // MAINWINDOW_H
