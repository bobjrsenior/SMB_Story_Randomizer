#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::setup(){

    QPushButton* generateButton = findChild<QPushButton*>("generateButton");

    QPushButton* toggleStoryListDisplayButton = findChild<QPushButton*>("toggleStoryListDisplay");

    QPushButton* chooseRelButton = findChild<QPushButton*>("chooseRelButton");

    QPushButton* writeToFileButton = findChild<QPushButton*>("writeButton");

    QPushButton* genAndWriteButton = findChild<QPushButton*>("genAndWriteButton");

    seedTextEdit = findChild<QTextEdit*>("seedTextEdit");

    filepathTextEdit = findChild<QTextEdit*>("filepathTextEdit");

    allowDupesRadioButton = findChild<QRadioButton*>("alloeDupesRadioButton");

    storyListTableView = findChild<QTableView*>("storyListTableView");
    storyListTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    uint32_t seed = (uint32_t) time(NULL);

    QString seedString = QString::number(seed);

    seedTextEdit->setText(seedString);

    generateIdList();

    setupStandardStageNames();

    setupTable();

    connect(generateButton, SIGNAL(clicked()), this, SLOT(generateButtonClicked()));

    connect(toggleStoryListDisplayButton, SIGNAL(clicked()), this, SLOT(toggleStoryListDisplay()));

    connect(chooseRelButton, SIGNAL(clicked()), this, SLOT(chooseRelFile()));

    connect(writeToFileButton, SIGNAL(clicked()), this, SLOT(writeToFile()));

    connect(genAndWriteButton, SIGNAL(clicked()), this, SLOT(generateAndWriteToFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupTable(){
    dataModel = new QStandardItemModel(100, 3, this);
    storyListTableView->verticalHeader()->setVisible(false);

    dataModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Story Location")));
    dataModel->setHorizontalHeaderItem(1, new QStandardItem(QString("Stage Name")));
    dataModel->setHorizontalHeaderItem(2, new QStandardItem(QString("Stage ID")));


    for(int i = 0; i < 100; ++i){
        std::string concat = std::to_string(i / 10 + 1) + "-" + std::to_string(i % 10 + 1);
        dataModel->setItem(i, 0, new QStandardItem(QString(concat.c_str())));
    }

    storyListTableView->setModel(dataModel);
}

void MainWindow::generateIdList(){
    int i = 0;
    for( ; i < 68; ++i){
        storyIdList[i] = i + 1;
    }

    storyIdList[i++] = 201;
    storyIdList[i++] = 202;
    storyIdList[i++] = 203;
    storyIdList[i++] = 204;

    for(int j = 231; j <= 239; ++i, ++j){
        storyIdList[i] = j;
    }

    for(int j = 281; j <= 289; ++i, ++j){
        storyIdList[i] = j;
    }

    for(int j = 341; j <= 350; ++i, ++j){
        storyIdList[i] = j;
    }
}

void MainWindow::generateButtonClicked(){

    QString seedText = seedTextEdit->toPlainText();

    bool validInt = false;;

    uint32_t seed = (uint32_t) seedText.toInt(&validInt);

    if(!validInt){
        createAlert(QString("Invalid seeed (whole numbers only)"));
        return;
    }

    srand(seed);

    if(allowDupesRadioButton->isChecked()){
        generateStoryListWithDupes();
    }
    else{
        generateStoryListWithoutDupes();
    }

    for(int i = 0; i < 100; ++i){
        if(storyList[i] >= 0 && storyList[i] <= 420){
            dataModel->setItem(i, 2, new QStandardItem(QString::number(storyList[i])));

            dataModel->setItem(i, 1, new QStandardItem(stageNames[storyList[i]]));
        }
    }

    generated = true;

}

void MainWindow::generateStoryListWithDupes(){

    for(int i = 0; i < 100; ++i){
        storyList[i] = storyIdList[rand() % 100];
    }

}

void MainWindow::generateStoryListWithoutDupes(){
    int copyList[100];

    for(int i = 0; i < 100; ++i){
        copyList[i] = storyIdList[i];
    }

    for(int i = 0; i < 100; ++i){
        int index = rand() % (100 - i);
        storyList[i] = copyList[index];
        copyList[index] = copyList[100 - 1 - i];
        copyList[100 - 1 - i] = storyList[i];
    }

}

void MainWindow::setupStandardStageNames(){
    stageNames = standardStageNames;

}

void MainWindow::toggleStoryListDisplay(){
    if(storyListVisible){
        storyListTableView->hide();
    }
    else{
        storyListTableView->show();
    }
    storyListVisible = !storyListVisible;
}

void MainWindow::chooseRelFile(){
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Rel File"), NULL, tr("Rel Files (*.rel);;All Files (*.*)"));
    if(filename.isNull()){
        return;
    }

    filepathTextEdit->setText(filename);
}

void MainWindow::writeToFile(){
    if(!generated){
        createAlert(QString("No Story List has been generated yet"));
        return;
    }

    QString qFilename = filepathTextEdit->toPlainText();

    if(qFilename.isEmpty() || qFilename.isNull()){
        createAlert(QString("No Rel Path Given"));
        return;
    }

    FILE* relFile = fopen(qFilename.toStdString().c_str(), "r+");

    if(relFile == NULL){
        createAlert(QString("Unable to open Rel file"));
        return;
    }

    int filesize;

    fseek(relFile, 0, SEEK_END);
    filesize = ftell(relFile);
    fseek(relFile, 0, SEEK_SET);

    if(filesize < 0x0020B448 + (4 * 100)){
        fclose(relFile);
        createAlert(QString("File not big enough. Is this the right file (mkb2.main_loop.rel)?"));
        return;
    }


    fseek(relFile, 0x0020B448, SEEK_SET);
    for(int i = 0; i < 100; ++i){
        writeBigShort(relFile, storyList[i]);
        fseek(relFile, 2, SEEK_CUR);
    }

    fclose(relFile);
    createAlert(QString("Done writing to file"));
}

void MainWindow::generateAndWriteToFile(){
    generateButtonClicked();
    if(generated){
        writeToFile();
    }
}

void MainWindow::writeBigShort(FILE* file, int number){
    putc((number >> 8), file);
    putc((number), file);
}

void MainWindow::createAlert(QString message){
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.exec();
}
