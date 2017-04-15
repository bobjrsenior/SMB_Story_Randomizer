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
#include <QFileDialog>
#include <stdio.h>
#include <QMessageBox>
#include <fstream>
#include <QList>

#define STORY_COUNT 100
#define CHALLENGE_COUNT 140
#define STORY_AND_CHALLENGE_COUNT 218
#define ALL_LEVEL_COUNT 420

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
    void setSeed(uint32_t seed);
    void setRelPath(char* relPath);
    void setCMD(bool option);

private:
    Ui::MainWindow *ui;
    void generateIdList();
    void generateStoryListWithDupes(int *idList, int count);
    void generateStoryListWithoutDupes(int *idList, int count);
    void setupTable();
    void setupStandardStageNames();
    void writeBigShort(FILE* file, int number);
    void createAlert(QString message);

    int storyList[STORY_COUNT];
    int storyIdList[STORY_COUNT];
    int challengeIdList[CHALLENGE_COUNT];
    int storyAndChallengeIdList[STORY_AND_CHALLENGE_COUNT];
    int allLevelsIdList[ALL_LEVEL_COUNT];
    bool storyListVisible = true;
    bool generated = false;
    bool cmd = false;
    QCheckBox* allowDupesCheckbox;
    QRadioButton* onlyStoryRadioButton;
    QRadioButton* onlyChallengeRadioButton;
    QRadioButton* storyAndChallengeRadioButton;
    QRadioButton* allLevelsRadioButton;
    QTextEdit* seedTextEdit;
    QTextEdit* filepathTextEdit;
    QTableView* storyListTableView;
    QStandardItemModel* dataModel;
    QList<QString> stageNames;
    QString standardStageNames[421] = {"", "CONVEYERS", "FLOATERS", "SLOPES", "SLIDERS", "SPINNING TOP", "CURVE BRIDGE", "BANKS", "EATEN FLOOR", "HOPPERS", "COASTER", "BUMPY CHECK", "SWELL", "GRAVITY SLIDER", "INCHWORMS", "TOTALITARIANISM", "ALTERNATIVE", "JUNCTION", "PRO SKATERS", "GIANT COMB", "BEEHIVE", "DYNAMIC MAZE", "TRIANGLE HOLES", "LAUNCHERS", "RANDOMIZER", "COIN SLOTS", "SEESAW BRIDGES", "ARTHROPOD", "WORMHOLE", "FREE FALL", "MELTING POT", "MAD SHUFFLE", "BEAD SCREEN", "JUMP MACHINE", "ZIGZAG SLOPE", "TOWER", "TOGGLE", "FLUCTUATION", "COMBINATION", "PUNCHED SEESAWS", "OPERA", "BRANDISHED", "TIERS", "CLIFFS", "NARROW PEAKS", "DETOUR", "SWITCH INFERNO", "FOLDERS", "QUICK TURN", "PISTONS", "SOFT CREAM", "MOMENTUM", "ENTANGLED PATH", "TOTTERS", "VORTEX", "WARP", "TRAMPOLINES", "SWING SHAFT", "LINEAR SEESAWS", "SERIAL JUMP", "CROSS FLOORS", "SPINNING SAW", "CHIPPED PIPES", "FLAT MAZE", "GUILLOTINE", "CORK SCREW", "ORBITERS", "TWIN BASIN", "AIR HOCKEY", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "SIMPLE", "HOLLOW", "BUMPY", "SWITCHES", "BOWL", "FLOATERS", "SLOPES", "SLIDERS", "SPINNING TOP", "CURVE BRIDGE", "CONVEYERS", "BUMPY CHECK", "ALTERNATIVE", "JUNCTION", "BEAD SCREEN", "FLUCTUATION", "FOLDERS", "QUICK TURN", "LINEAR SEESAWS", "BIRTH", "BANKS", "EATEN FLOOR", "HOPPERS", "COASTER", "BOARD PARK", "SWELL", "GRAVITY SLIDER", "INCHWORMS", "TOTALITARIANISM", "LEVELER", "ORGANIC FORM", "REVERSIBLE GEAR", "STEPPING STONES", "DRIBBLES", "U.R.L.", "MAD RINGS", "CURVY OPTIONS", "TWISTER", "DOWNHILL", "RAMPAGE", "PRO SKATERS", "GIANT COMB", "BEEHIVE", "DYNAMIC MAZE", "TRIANGLE HOLES", "LAUNCHERS", "RANDOMIZER", "COIN SLOTS", "SEESAW BRIDGES", "ARTHROPOD", "AUTO DOORS", "HEAVY SPHERE", "STAGGER", "U.F.O.", "RING BRIDGES", "DOMES", "AMIDA LOT", "LONG SLIDER", "GRID BRIDGE", "TEAPOT", "WORMHOLE", "FREE FALL", "MELTING POT", "MAD SHUFFLE", "PARTITION", "JUMP MACHINE", "ZIGZAG SLOPE", "TOWER", "TOGGLE", "PACHINKO", "COMBINATION", "PUNCHED SEESAWS", "OPERA", "BRANDISHED", "TIERS", "CLIFFS", "NARROW PEAKS", "DETOUR", "SWITCH INFERNO", "EARTHQUAKE", "SPIRAL BRIDGE", "WAVY OPTION", "OBSTACLE", "DOMINO", "SIEVE", "FLOCK", "DOUBLE SPIRAL", "HIERARCHY", "8 BRACELETS", "BANANA HUNTING", "PISTONS", "SOFT CREAM", "MOMENTUM", "ENTANGLED PATH", "TOTTERS", "VORTEX", "WARP", "TRAMPOLINES", "SWING SHAFT", "FIGHTERS", "SERIAL JUMP", "CROSS FLOORS", "SPINNING SAW", "CHIPPED PIPES", "FLAT MAZE", "GUILLOTINE", "CORK SCREW", "ORBITERS", "TWIN BASIN", "AIR HOCKEY", "CHARGE", "STRATA", "PUZZLE", "GIANT SWING", "5 DRUMS", "FREE THROW", "PENDULUMS", "CONICAL SLIDER", "CONSTRUCTION", "TRAIN WORM", "CENTRIFUGAL", "SWING BRIDGES", "CYLINDERS", "PASSAGE", "NOTCH", "INTERMITTENT", "LONG TORUS", "SPASMODIC", "DOUBLE TWIN", "CLOCK FACE", "VARIABLE WIDTH", "STRIKER", "OOPARTS", "PLANETS", "SLICED CHEESE", "8 SEESAWS", "SYNCHRONIZED", "HELIX", "DIZZY SYSTEM", "NINTENDO", "TRAINING", "GIMMICK", "MOUNTAIN", "DISORDER", "3D MAZE", "LABYRINTH", "POSTMODERN", "REVOLUTION", "INVISIBLE", "CREATED BY", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-"};

private slots:
    void generateButtonClicked();
    void toggleStoryListDisplay();
    void chooseRelFile();
    void writeToFile();
    void importCustomStageNames();

public slots:
    void generateAndWriteToFile();


};

#endif // MAINWINDOW_H
