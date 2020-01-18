//
// Created by erico on 18/01/2020.
//

#ifndef AGSCONFIG_AGSDATA_H
#define AGSCONFIG_AGSDATA_H

#include<string>
using namespace std;

class AgsData {
    struct Graphics {
        string driver;
        bool windowed;
        string screen_def;
        int screen_width;
        int screen_height;
        bool match_device_ratio;
        string game_scale_fs;
        string game_scale_win;
        string filter;
        int refresh;
        bool render_at_screenres;
        int supersampling;
        bool vsync;
        Graphics();
    };

    struct Sound {
        string digiid;
        string midiid;
        bool usespeech;
        bool threaded;
        Sound();
    };

    struct Mouse {
        bool auto_lock;
        string control_when;
        bool control_enabled;
        string speed_def;
        float speed;
        Mouse();
    };

    struct Language {
        string translation;
        Language();
    };

    struct Misc {
        bool log;
        string datafile;
        string datadir;
        string user_data_dir;
        string shared_data_dir;
        bool antialias;
        int cachemax;
        Misc();
    };

    struct Override {
        bool multitasking;
        string os;
        bool upscale;
        Override();
    };

    struct Disabled {
        bool render_at_screenres;
        bool speechvox;
        bool filters;
        Disabled();
    };

    Graphics graphics = Graphics();
    Sound sound = Sound();
    Mouse mouse = Mouse();
    Language language = Language();
    Misc misc = Misc();
    Override override = Override();
    Disabled disabled = Disabled();

public:
    string ToIniString();
};


#endif //AGSCONFIG_AGSDATA_H
