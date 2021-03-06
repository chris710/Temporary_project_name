//////////////////////////////////////////////////
///                   GAME                     ///
///                  game.h                    ///
//////////////////////////////////////////////////

#ifndef GAME_H
#define GAME_H

///BIBLIOTEKA ALLEGRO
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

///POTRZEBNE BIBLIOTEKI
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

///WYSUNIETE DEKLARACJE
class unitInstance;

///POTRZEBNE PLIKI
#include "unit.h"

class gameInstance
{
    public:
        gameInstance();
        ~gameInstance() { }; //Destruktor, wywoluje czyszczenie pamieci
        struct unitStruct //Struktura jednostki na liscie
        {
            std::string name; //Zawiera domyslne dane o jednostce
            ALLEGRO_BITMAP* bitmap;
            int HP,attack,defence,ful;
            std::string sound_movement,sound_attack,sound_death;
        };
        struct soundStruct
        {                       //Element listy dzwiekow
            std::string name;
            ALLEGRO_SAMPLE* file;
        };
        struct objStruct
        {                       //Element listy obiektow
            std::string name;
            ALLEGRO_BITMAP* bitmap;
        };
        struct mapTile //Kafelek mapy
        {
            ALLEGRO_BITMAP* tile;
            std::string effect;
            int rotation;
            unitInstance* currentUnit; //Przechowuje wskaznik na obecna na tym polu jednostke
        };
        ///KONTROLA OKNA
        ALLEGRO_DISPLAY* displayAL; //Uchwyt okna
        ALLEGRO_MOUSE_STATE mouseState;
        ALLEGRO_MOUSE_CURSOR* mouseCursor[2]; //normalny, klikniete
        ALLEGRO_EVENT_QUEUE *eventQueueAL; //Zdarzenia i timery ALLEGRO
        ALLEGRO_EVENT gameEventsAL;
        ALLEGRO_TIMER *gameTimerAL;
        ALLEGRO_KEYBOARD_STATE keyStateAL;
        bool CreateDisplay(int ScreenHeight,int ScreenWidth); //Tworzenie ekranu gry o podanej rozdzielczosci

        void ReleaseMemory(); //Zwalnianie pamieci zajetej przez Allegro, np. timer czy keystate
        void DisplayMessage(std::string title,std::string message); //Wyswietlanie wiadomosci na ekran
        int fps; //Ilosc klatek na sekunde
        int height,width; //wysokosc okna i jego szerokosc
        bool updateDisplay; //Zmienna wskazujaca na to, czy trzeba przerysowywac cala mape
        bool exitGame; //Zmienna sterujace petla gry

        ///UI
        ALLEGRO_BITMAP* fieldBox; //zaznaczanie pol mapy
        ALLEGRO_BITMAP* cursor[2]; //kursory
        ALLEGRO_BITMAP* highlight; //zaznaczanie pol mapy

        ///RESOURCE LOADER
        bool PushUnitCFG(std::string name,std::string file,int HP,int attack, int defence,std::string sound_movement,
                         std::string sound_attack,std::string sound_death); //Dodawanie do listy jednostek
        bool PushSoundCFG(std::string name,std::string file); //Dodawanie do listy dzwiekow
        bool PushObjCFG(std::string name,std::string file); //Dodawanie do listy dzwiekow
        bool ResourceLoader(); //Ladowanie calych list danych
        void ResourceUnloader(); //Usuwanie calych list danych

        std::vector<unitStruct*> unitLib; //Listy dostepnych plikow jednostek oraz innych assetow
        std::vector<soundStruct*> soundLib;
        std::vector<objStruct*> objLib;

        ///MAP LOADER
        bool LoadMap(std::string file); //Ladowanie mapy o podanej nazwie
        void UnloadMap(); //Usuwanie obecnie zaladowanej mapy
        bool mapLoaded; //Zmienna stanu wczytania mapy
        int mapSize[2]; // jej rozmiar
        std::vector<mapTile*> gameMap; //Macierz mapy
        std::string mapName; //Nazwa mapy


        ///MAP RENDER
        bool MapScroll();
        bool RenderMap();
        bool RenderFieldBox();
        bool RenderUnitRange();
        int mapOffset[2]; //offset mapy, 0 -> szer, 1 -> wys
        bool mapScroll;
        bool mapDrawUnitRange;


        ///MOUSE
        void MapClick();

        ///SWIAT GRY
        void CreateUnit(std::string type); //Funkcja tworzaca jednostke, typ z unitLib
        std::vector<unitInstance*> unitList; //lista jednostek na mapie
        unitInstance* selectedUnit;

        ///GRACZE
        int GetCurrentPlayer(); //Funkcja zwraca numer obecnego gracza
        void EndTurn(); //Funkcja ustawia nastepnego gracza na obecnego
        int playerCurrent; //Numer obecnego gracza
        std::vector<std::string> playerList; //Lista graczy
};

#endif
