#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QTextStream>
#ifdef _WIN32
#include <windows.h>
#endif

void displayHelp();

int main(int argc, char *argv[])
{
    bool showUI = true;
    bool validCMD = true;
    bool setSeed = false;
    int levels = 0;
    char* relPath = NULL;
    uint32_t seed;

    if(argc > 1){
        showUI = false;
        for(int i = 1; i < argc; ++i){
            if(strcmp(argv[i], "-help") == 0 || strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "help") == 0 || strcmp(argv[i], "-help") == 0){
                displayHelp();
                validCMD = false;
            }
            else if(strcmp(argv[i], "-seed") == 0){
                ++i;
                if(i < argc){
                    seed = (uint32_t) atoi(argv[i]);
                    setSeed = true;
                }
                else{
                    displayHelp();
                    validCMD = false;
                }
            }
            else if(strcmp(argv[i], "-rel") == 0){
                ++i;
                if(i < argc){
                    relPath = argv[i];
                }
                else{
                    displayHelp();
                    validCMD = false;
                }
            }
            else if(strcmp(argv[i], "-levels") == 0){

                ++i;
                std::string levelType(argv[i]);
                std::transform(levelType.begin(), levelType.end(), levelType.begin(), ::tolower);
                if(levelType == "story"){
                    levels = 0;
                }
                else if(levelType == "challenge"){
                    levels = 1;
                }
                else if(levelType == "storyandchallenge"){
                    levels = 2;
                }
                else if(levelType == "all"){
                    levels = 3;
                }
                else{
                    displayHelp();
                    validCMD = false;
                }
            }
            else{
                displayHelp();
                validCMD = false;
            }
        }
    }
    else{
#ifdef _WIN32
        // Close unneeded console window
        FreeConsole();
#endif
    }

    if(!showUI && !validCMD)
        return 0;

    QApplication a(argc, argv);
    MainWindow w;
    w.setup();
    if(showUI){
        w.show();
        return a.exec();
    }
    else{
        if(relPath == NULL){
            displayHelp();
        }
        else{
            w.setCMD(true);
            if(setSeed){
                w.setSeed(seed);
            }
            w.setLevels(levels);
            w.setRelPath(relPath);
            w.generateAndWriteToFile();
        }
#ifdef _WIN32
        // Close unneeded console window
        FreeConsole();
#endif
        return 0;
    }
}

void displayHelp(){
    //QTextStream ts(stdout, QIODevice::WriteOnly);
    std::cout << "Usage" << '\n'
    << "\tSMB_Story_Randomizer.exe [OPTION...]" << '\n'
    << "Options:" << '\n'
    << "\t-help Show this output" << '\n'
    << "\t-seed <NUMBER> Set the seed to be used for the randomizer (unsigned int)" << '\n'
    << "\t-rel <REL FILE> Set the mkb2.main_loop.rel rel file to be used" << '\n'
    << "\t-levels <LEVEL_TYPE> Set which levels to retrieve from (story, challenge, storyandchallenge, all)" << std::endl;
    //ts.flush();

}
