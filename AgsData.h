//
// Created by erico on 18/01/2020.
//
#pragma once
#ifndef AGSCONFIG_AGSDATA_H
#define AGSCONFIG_AGSDATA_H

#include<string>
#include"nonstd/optional.hpp"
using nonstd::optional;
using std::string;

class AgsData {
    struct Graphics {
        optional<string> driver;
        optional<bool> windowed;
        optional<string> screen_def;
        optional<int> screen_width;
        optional<int> screen_height;
        optional<bool> match_device_ratio;
        optional<string> game_scale_fs;
        optional<string> game_scale_win;
        optional<string> filter;
        optional<int> refresh;
        optional<bool> render_at_screenres;
        optional<int> supersampling;
        optional<bool> vsync;
        Graphics();
        void Reset();
        void SetSaneInitialValue();
    };

    struct Sound {
        optional<string> digiid;
        optional<string> midiid;
        optional<bool> usespeech;
        optional<bool> threaded;
        Sound();
        void Reset();
        void SetSaneInitialValue();
    };

    struct Mouse {
        optional<bool> auto_lock;
        optional<string> control_when;
        optional<bool> control_enabled;
        optional<string> speed_def;
        optional<float> speed;
        Mouse();
        void Reset();
        void SetSaneInitialValue();
    };

    struct Language {
        optional<string> translation;
        Language();
        void Reset();
        void SetSaneInitialValue();
    };

    struct Misc {
        optional<bool> log;
        optional<string> datafile;
        optional<string> datadir;
        optional<string> user_data_dir;
        optional<string> shared_data_dir;
        optional<bool> antialias;
        optional<int> cachemax;
        Misc();
        void Reset();
        void SetSaneInitialValue();
    };

    struct Override {
        optional<bool> multitasking;
        optional<string> os;
        optional<bool> upscale;
        Override();
        void Reset();
        void SetSaneInitialValue();
    };

    struct Disabled {
        optional<bool> render_at_screenres;
        optional<bool> speechvox;
        optional<bool> filters;
        Disabled();
        void Reset();
        void SetSaneInitialValue();
    };


public:

    Graphics graphics = Graphics();
    Sound sound = Sound();
    Mouse mouse = Mouse();
    Language language = Language();
    Misc misc = Misc();
    Override override = Override();
    Disabled disabled = Disabled();

    void Reset();
    void SetSaneInitialValue();
    void LoadFromIni(const string& filename_with_path);
    string ToIniString();
    void WriteToFile(const string& filename_with_path);
    void MergeIn(AgsData data);
};


#endif //AGSCONFIG_AGSDATA_H
