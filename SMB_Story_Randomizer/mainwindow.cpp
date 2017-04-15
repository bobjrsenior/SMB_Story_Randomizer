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

    QPushButton* importStageNamesButton = findChild<QPushButton*>("importCustomStageNames");

    seedTextEdit = findChild<QTextEdit*>("seedTextEdit");

    filepathLineEdit = findChild<QLineEdit*>("filepathLineEdit");

    allowDupesCheckbox = findChild<QCheckBox*>("allowDupesCheckbox");

    onlyStoryRadioButton = findChild<QRadioButton*>("onlyStoryRadioButton");

    onlyChallengeRadioButton = findChild<QRadioButton*>("OnlyChallengeRadioButton");

    storyAndChallengeRadioButton = findChild<QRadioButton*>("StoryAndChallengeRadioButton");

    allLevelsRadioButton = findChild<QRadioButton*>("allLevelsRadioButton");

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

    connect(importStageNamesButton, SIGNAL(clicked()), this, SLOT(importCustomStageNames()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupTable(){
    dataModel = new QStandardItemModel(STORY_COUNT, 3, this);
    storyListTableView->verticalHeader()->setVisible(false);

    dataModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Story Location")));
    dataModel->setHorizontalHeaderItem(1, new QStandardItem(QString("Stage Name")));
    dataModel->setHorizontalHeaderItem(2, new QStandardItem(QString("Stage ID")));


    for(int i = 0; i < STORY_COUNT; ++i){
        std::string concat = std::to_string(i / 10 + 1) + "-" + std::to_string(i % 10 + 1);
        dataModel->setItem(i, 0, new QStandardItem(QString(concat.c_str())));
    }

    storyListTableView->setModel(dataModel);
}

void MainWindow::generateIdList(){

    // Story IDs
    int storyOnlyCounter = 0;
    for( ; storyOnlyCounter < 68; ++storyOnlyCounter){
        storyIdList[storyOnlyCounter] = storyOnlyCounter + 1;
        storyAndChallengeIdList[storyOnlyCounter] = storyOnlyCounter + 1;
    }

    int StoryChallengeCounter = storyOnlyCounter;

    storyIdList[storyOnlyCounter++] = 201;
    storyIdList[storyOnlyCounter++] = 202;
    storyIdList[storyOnlyCounter++] = 203;
    storyIdList[storyOnlyCounter++] = 204;


    for(int j = 231; j <= 239; ++storyOnlyCounter, ++j){
        storyIdList[storyOnlyCounter] = j;
    }

    for(int j = 281; j <= 289; ++storyOnlyCounter, ++j){
        storyIdList[storyOnlyCounter] = j;
    }

    for(int j = 341; j <= 350; ++storyOnlyCounter, ++j, ++StoryChallengeCounter){
        storyIdList[storyOnlyCounter] = j;
        storyAndChallengeIdList[StoryChallengeCounter] = j;
    }

    // Challenge IDs

    for(int j = 201; j <= 340; ++j, ++storyOnlyCounter, ++StoryChallengeCounter){
        challengeIdList[j - 201] = j;
        storyAndChallengeIdList[StoryChallengeCounter] = j;
    }


    // All Level IDs

    for(int j = 1; j <= 420; ++j){
        allLevelsIdList[j - 1] = j;
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

    int *idList;
    int length;

    if((levels == -1 && onlyStoryRadioButton->isChecked()) || levels == 0){
        idList = storyIdList;
        length = STORY_COUNT;
    }
    else if((levels == -1 && onlyChallengeRadioButton->isChecked()) || levels == 1){
        idList = challengeIdList;
        length = CHALLENGE_COUNT;
    }
    else if((levels == -1 && storyAndChallengeRadioButton->isChecked()) || levels == 2){
        idList = storyAndChallengeIdList;
        length = STORY_AND_CHALLENGE_COUNT;
    }
    else{
        idList = allLevelsIdList;
        length = ALL_LEVEL_COUNT;
    }


    srand(seed);

    if(allowDupesCheckbox->isChecked()){
        generateStoryListWithDupes(idList, length);
    }
    else{
        generateStoryListWithoutDupes(idList, length);
    }

    for(int i = 0; i < 100; ++i){
        dataModel->setItem(i, 2, new QStandardItem(QString::number(storyList[i])));

        if(storyList[i] >= 0 && storyList[i] < stageNames.length()){
            dataModel->setItem(i, 1, new QStandardItem(stageNames[storyList[i]]));
        }
        else{
            dataModel->setItem(i, 1, new QStandardItem(QString("N/A")));
        }
    }

    generated = true;

}

void MainWindow::generateStoryListWithDupes(int *idList, int count){

    for(int i = 0; i < STORY_COUNT; ++i){
        storyList[i] = idList[rand() % count];
    }

}

void MainWindow::generateStoryListWithoutDupes(int *idList, int count){
    int *copyList = new int[count];

    for(int i = 0; i < count; ++i){
        copyList[i] = idList[i];
    }

    for(int i = 0; i < STORY_COUNT; ++i){
        int index = rand() % (count - i);
        storyList[i] = copyList[index];
        copyList[index] = copyList[count - 1 - i];
        copyList[count - 1 - i] = storyList[i];
    }

    delete [] copyList;
}

void MainWindow::setupStandardStageNames(){
    stageNames.clear();
    for(int i = 0; i < ALL_LEVEL_COUNT; ++i){
        stageNames << standardStageNames[i];
    }
}

void MainWindow::importCustomStageNames(){
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Custom Stage Names Files"), NULL, tr("Stage Names (*.str);;All Files (*.*)"));
    if(filename.isNull()){
        return;
    }
    std::string stdFilename = filename.toStdString();
    std::ifstream file(stdFilename);
    std::cout << "G: " << stdFilename << std::endl;
    if(!file.good()){
        createAlert(QString("Failed To Import Stage Names"));
        return;
    }
    stageNames.clear();
    int index = 0;
    while(file.good()){
        std::string line;
        std::getline(file, line);
        if(line.length() == 0){
            line = " ";
        }

        stageNames << QString(line.c_str());
        ++index;
    }
    file.close();
    createAlert(QString("Imported Stage Names"));

    if(generated){
        generateButtonClicked();
    }
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

    filepathLineEdit->setText(filename);
}

void MainWindow::writeToFile(){
    if(!generated){
        createAlert(QString("No Story List has been generated yet"));
        return;
    }

    QString qFilename = filepathLineEdit->text();

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

    if(filesize < 0x0020B448 + (4 * STORY_COUNT)){
        fclose(relFile);
        createAlert(QString("File not big enough. Is this the right file (mkb2.main_loop.rel)?"));
        return;
    }


    fseek(relFile, 0x0020B448, SEEK_SET);
    for(int i = 0; i < STORY_COUNT; ++i){
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
    if(!cmd){
        QMessageBox msgBox;
        msgBox.setText(message);
        msgBox.exec();
    }
    else{
        std::cout << message.toStdString() << std::endl;
    }
}

void MainWindow::setSeed(uint32_t seed){
    QString seedString = QString::number(seed);

    seedTextEdit->setText(seedString);
}

void MainWindow::setRelPath(char* relPath){
    QString qRelPath = QString::fromUtf8(relPath, (int) strlen(relPath));
    filepathLineEdit->setText(qRelPath);
}

void MainWindow::setCMD(bool option){
    cmd = option;
}

void MainWindow::setLevels(int levels){
    this->levels = levels;
}
