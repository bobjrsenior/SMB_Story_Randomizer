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
    char* relPath = NULL;
    uint32_t seed;

    if(argc > 1){
        showUI = false;
        for(int i = 1; i < argc; ++i){
            if(strcmp(argv[i], "h") == 0 || strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "help") == 0 || strcmp(argv[i], "-help") == 0){
                displayHelp();
                validCMD = false;
            }
            else if(strcmp(argv[i], "-s") == 0){
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
            else if(strcmp(argv[i], "-r") == 0){
                ++i;
                if(i < argc){
                    relPath = argv[i];
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
    << "SMB_Story_Randomizer.exe [OPTION...]" << '\n'
    << "Options:" << '\n'
    << "-h Show this output" << '\n'
    << "-s <NUMBER> Set the seed to be used for the randomizer (unsigned int)" << '\n'
    << "-r <REL FILE Set the mkb2.main_loop.rel rel file to be used" << std::endl;
    //ts.flush();

}
