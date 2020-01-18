//
// Created by erico on 18/01/2020.
//
#pragma once
#ifndef AGSCONFIG_AGSTOLD_H
#define AGSCONFIG_AGSTOLD_H

#include<string>
#include<vector>
using namespace std;

class AgsTold {
    struct Config_AT_graphics {
        string driver;
        bool windowed;
        string screen_def;
        string game_scale_fs;
        string game_scale_win;
        string filter;
        bool render_at_screenres;
        bool vsync;
        Config_AT_graphics();
    };

    struct Config_AT_sound {
        string digiid;
        string midiid;
        bool usespeech;
        bool threaded;
        Config_AT_sound();
    };

    struct Config_AT_mouse {
        bool auto_lock;
        bool control_enabled;
        float speed;
        Config_AT_mouse();
    };

    struct Config_AT_language {
        string translation;
        Config_AT_language();
    };

    struct Config_AT_misc {
        bool antialias;
        int cachemax;
        int defaultres;
        int game_height;
        int game_width;
        int gamecolordepth;
        bool letterbox;
        bool notruecolor;
        string titletext;
        string shared_data_dir;
        Config_AT_misc();
    };

    struct ConfigPath {
        string _default;
        string global;
        string user;
        ConfigPath();
    };

    struct Data {
        string basepack;
        string compiledwith;
        string gamename;
        string version;
        Data();
    };

    struct Engine {
        string name;
        string version;
        Engine();
    };

    struct Graphicdriver {
        vector<string> drivers;
        Graphicdriver();
    };

public:
    Config_AT_graphics config_AT_graphics = Config_AT_graphics();
    Config_AT_sound config_AT_sound = Config_AT_sound();
    Config_AT_mouse config_AT_mouse = Config_AT_mouse();
    Config_AT_language config_AT_language = Config_AT_language();
    Config_AT_misc config_AT_misc = Config_AT_misc();
    ConfigPath configPath = ConfigPath();
    Data data = Data();
    Engine engine = Engine();
    Graphicdriver graphicdriver = Graphicdriver();

    void InitFromTell(string agsExecutable);

};


#endif //AGSCONFIG_AGSTOLD_H
