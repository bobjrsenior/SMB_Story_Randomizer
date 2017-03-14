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
    void setupStandardStageNames();
    void writeBigShort(FILE* file, int number);
    void createAlert(QString message);

    int storyList[100];
    int storyIdList[100];
    bool storyListVisible = true;
    bool generated = false;
    QRadioButton* allowDupesRadioButton;
    QTextEdit* seedTextEdit;
    QTextEdit* filepathTextEdit;
    QTableView* storyListTableView;
    QStandardItemModel* dataModel;
    QString* stageNames;
    QString standardStageNames[421] = {"", "CONVEYERS", "FLOATERS", "SLOPES", "SLIDERS", "SPINNING TOP", "CURVE BRIDGE", "BANKS", "EATEN FLOOR", "HOPPERS", "COASTER", "BUMPY CHECK", "SWELL", "GRAVITY SLIDER", "INCHWORMS", "TOTALITARIANISM", "ALTERNATIVE", "JUNCTION", "PRO SKATERS", "GIANT COMB", "BEEHIVE", "DYNAMIC MAZE", "TRIANGLE HOLES", "LAUNCHERS", "RANDOMIZER", "COIN SLOTS", "SEESAW BRIDGES", "ARTHROPOD", "WORMHOLE", "FREE FALL", "MELTING POT", "MAD SHUFFLE", "BEAD SCREEN", "JUMP MACHINE", "ZIGZAG SLOPE", "TOWER", "TOGGLE", "FLUCTUATION", "COMBINATION", "PUNCHED SEESAWS", "OPERA", "BRANDISHED", "TIERS", "CLIFFS", "NARROW PEAKS", "DETOUR", "SWITCH INFERNO", "FOLDERS", "QUICK TURN", "PISTONS", "SOFT CREAM", "MOMENTUM", "ENTANGLED PATH", "TOTTERS", "VORTEX", "WARP", "TRAMPOLINES", "SWING SHAFT", "LINEAR SEESAWS", "SERIAL JUMP", "CROSS FLOORS", "SPINNING SAW", "CHIPPED PIPES", "FLAT MAZE", "GUILLOTINE", "CORK SCREW", "ORBITERS", "TWIN BASIN", "AIR HOCKEY", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "SIMPLE", "HOLLOW", "BUMPY", "SWITCHES", "BOWL", "FLOATERS", "SLOPES", "SLIDERS", "SPINNING TOP", "CURVE BRIDGE", "CONVEYERS", "BUMPY CHECK", "ALTERNATIVE", "JUNCTION", "BEAD SCREEN", "FLUCTUATION", "FOLDERS", "QUICK TURN", "LINEAR SEESAWS", "BIRTH", "BANKS", "EATEN FLOOR", "HOPPERS", "COASTER", "BOARD PARK", "SWELL", "GRAVITY SLIDER", "INCHWORMS", "TOTALITARIANISM", "LEVELER", "ORGANIC FORM", "REVERSIBLE GEAR", "STEPPING STONES", "DRIBBLES", "U.R.L.", "MAD RINGS", "CURVY OPTIONS", "TWISTER", "DOWNHILL", "RAMPAGE", "PRO SKATERS", "GIANT COMB", "BEEHIVE", "DYNAMIC MAZE", "TRIANGLE HOLES", "LAUNCHERS", "RANDOMIZER", "COIN SLOTS", "SEESAW BRIDGES", "ARTHROPOD", "AUTO DOORS", "HEAVY SPHERE", "STAGGER", "U.F.O.", "RING BRIDGES", "DOMES", "AMIDA LOT", "LONG SLIDER", "GRID BRIDGE", "TEAPOT", "WORMHOLE", "FREE FALL", "MELTING POT", "MAD SHUFFLE", "PARTITION", "JUMP MACHINE", "ZIGZAG SLOPE", "TOWER", "TOGGLE", "PACHINKO", "COMBINATION", "PUNCHED SEESAWS", "OPERA", "BRANDISHED", "TIERS", "CLIFFS", "NARROW PEAKS", "DETOUR", "SWITCH INFERNO", "EARTHQUAKE", "SPIRAL BRIDGE", "WAVY OPTION", "OBSTACLE", "DOMINO", "SIEVE", "FLOCK", "DOUBLE SPIRAL", "HIERARCHY", "8 BRACELETS", "BANANA HUNTING", "PISTONS", "SOFT CREAM", "MOMENTUM", "ENTANGLED PATH", "TOTTERS", "VORTEX", "WARP", "TRAMPOLINES", "SWING SHAFT", "FIGHTERS", "SERIAL JUMP", "CROSS FLOORS", "SPINNING SAW", "CHIPPED PIPES", "FLAT MAZE", "GUILLOTINE", "CORK SCREW", "ORBITERS", "TWIN BASIN", "AIR HOCKEY", "CHARGE", "STRATA", "PUZZLE", "GIANT SWING", "5 DRUMS", "FREE THROW", "PENDULUMS", "CONICAL SLIDER", "CONSTRUCTION", "TRAIN WORM", "CENTRIFUGAL", "SWING BRIDGES", "CYLINDERS", "PASSAGE", "NOTCH", "INTERMITTENT", "LONG TORUS", "SPASMODIC", "DOUBLE TWIN", "CLOCK FACE", "VARIABLE WIDTH", "STRIKER", "OOPARTS", "PLANETS", "SLICED CHEESE", "8 SEESAWS", "SYNCHRONIZED", "HELIX", "DIZZY SYSTEM", "NINTENDO", "TRAINING", "GIMMICK", "MOUNTAIN", "DISORDER", "3D MAZE", "LABYRINTH", "POSTMODERN", "REVOLUTION", "INVISIBLE", "CREATED BY", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-"};
    QString customStageNames[421];

private slots:
    void generateButtonClicked();
    void toggleStoryListDisplay();
    void chooseRelFile();
    void writeToFile();
    void generateAndWriteToFile();


};

#endif // MAINWINDOW_H
