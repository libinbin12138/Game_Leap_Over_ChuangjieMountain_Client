#include <QApplication>
#include"playscreen.h"
#include"game_ready_page.h"
#include"log_in.h"
#include"game_mainpage.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //    PlayScreen playscreen;
    //    playscreen.show();

//    Game_Ready_Page game_ready_page;
//    game_ready_page.show();

            Log_In log_in;
            log_in.show();
    //    Game_MainPage game_mainpage;
    //    game_mainpage.show();
    return a.exec();
}
