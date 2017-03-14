#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>

void displayHelp();

int main(int argc, char *argv[])
{
    bool showUI = true;
    bool validCMD = true;
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
        }
    }

    if(!showUI && !validCMD)
        return 0;

    QApplication a(argc, argv);
    MainWindow w;
    w.setup();
    if(showUI){
        w.show();
    }
    else{

    }


    return a.exec();
}

void displayHelp(){

}
