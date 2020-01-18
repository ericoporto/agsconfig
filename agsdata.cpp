//
// Created by erico on 18/01/2020.
//

#include <fstream>
#include "agsdata.h"
#include "inipp.h"

using namespace std;

string BoolToStr(bool b){
    return b ? "1" : "0";
}

string IntToStr(int i){
    return to_string(i);
}

string FloatToStr(float f){
    return to_string(f);
}

bool StrToBool(const string& b_str){
    return b_str != "0";
}

int StrToInt(const string& i_str){
    return stoi(i_str);
}

float StrToFloat(const string& f_str){
    return stof(f_str);
}

AgsData::Graphics::Graphics() {
    driver = "Software";
    windowed = false;
    screen_def = "scaling";
    screen_width = 0;
    screen_height = 0;
    match_device_ratio = true;
    game_scale_fs = "proportional";
    game_scale_win = "proportional";
    filter = "none";
    refresh = 60;
    render_at_screenres = false;
    supersampling = 1;
    vsync = true;
}

AgsData::Sound::Sound() {
    digiid = "";
    midiid = "";
    usespeech = true;
    threaded = true;
}

AgsData::Mouse::Mouse() {
    auto_lock = false;
    control_when = "never";
    control_enabled = false;
    speed_def = "absolute";
    speed = 1.0f;
}

AgsData::Language::Language() {
    translation = "";
}

AgsData::Misc::Misc() {
    log = false;
    datafile = "";
    datadir = "";
    user_data_dir = "";
    shared_data_dir = "";
    antialias = false;
    cachemax = 131072;
}

AgsData::Override::Override() {
    multitasking = false;
    os = "";
    upscale = false;
}

AgsData::Disabled::Disabled() {
    render_at_screenres = false;
    speechvox = false;
    filters = false;
}

string AgsData::ToIniString() {
    string ini_string;
    std::stringstream iniStream(ini_string);
    inipp::Ini<char> ini;
    ini.sections["graphics"]["driver"] = graphics.driver;
    ini.sections["graphics"]["windowed"] = BoolToStr(graphics.windowed);
    ini.sections["graphics"]["screen_def"] = graphics.screen_def;
    ini.sections["graphics"]["screen_width"] = IntToStr(graphics.screen_width);
    ini.sections["graphics"]["screen_height"] = IntToStr(graphics.screen_height);
    ini.sections["graphics"]["match_device_ratio"] = BoolToStr(graphics.match_device_ratio);
    ini.sections["graphics"]["game_scale_fs"] = graphics.game_scale_fs;
    ini.sections["graphics"]["game_scale_win"] = graphics.game_scale_win;
    ini.sections["graphics"]["filter"] = graphics.filter;
    ini.sections["graphics"]["refresh"] = IntToStr(graphics.refresh);
    ini.sections["graphics"]["render_at_screenres"] = BoolToStr(graphics.render_at_screenres);
    ini.sections["graphics"]["supersampling"] = IntToStr(graphics.supersampling);
    ini.sections["graphics"]["vsync"] = BoolToStr(graphics.vsync);

    ini.sections["sound"]["digiid"] = sound.digiid;
    ini.sections["sound"]["midiid"] = sound.midiid;
    ini.sections["sound"]["usespeech"] = BoolToStr(sound.usespeech);
    ini.sections["sound"]["threaded"] = BoolToStr(sound.threaded);

    ini.sections["mouse"]["auto_lock"] = BoolToStr(mouse.auto_lock);
    ini.sections["mouse"]["control_when"] = mouse.control_when;
    ini.sections["mouse"]["control_enabled"] = BoolToStr(mouse.control_enabled);
    ini.sections["mouse"]["speed_def"] = mouse.speed_def;
    ini.sections["mouse"]["speed"] = FloatToStr(mouse.speed);

    ini.sections["language"]["translation"] = language.translation;

    ini.sections["misc"]["log"] = BoolToStr(misc.log);
    ini.sections["misc"]["datafile"] = misc.datafile;
    ini.sections["misc"]["datadir"] = misc.datadir;
    ini.sections["misc"]["user_data_dir"] = misc.user_data_dir;
    ini.sections["misc"]["shared_data_dir"] = misc.shared_data_dir;
    ini.sections["misc"]["antialias"] = BoolToStr(misc.antialias);
    ini.sections["misc"]["cachemax"] = IntToStr(misc.cachemax);

    ini.generate(iniStream);
    ini_string = iniStream.str();
    return ini_string;
}

void AgsData::WriteToFile(const string& filename_with_path) {
    ofstream output_ini_file(filename_with_path);
    output_ini_file << ToIniString();
    output_ini_file.close();
}

void AgsData::LoadFromIni(const string &filename_with_path) {
    inipp::Ini<char> ini;
    std::ifstream is(filename_with_path);
    ini.parse(is);

    graphics.driver = ini.sections["graphics"]["driver"];
    graphics.windowed = StrToBool(ini.sections["graphics"]["windowed"]);
    graphics.screen_def = ini.sections["graphics"]["screen_def"];
    graphics.screen_width = StrToInt(ini.sections["graphics"]["screen_width"]);
    graphics.screen_height = StrToInt(ini.sections["graphics"]["screen_height"]);
    graphics.match_device_ratio = StrToBool(ini.sections["graphics"]["match_device_ratio"]);
    graphics.game_scale_fs = ini.sections["graphics"]["game_scale_fs"];
    graphics.game_scale_win = ini.sections["graphics"]["game_scale_win"];
    graphics.filter = ini.sections["graphics"]["filter"];
    graphics.refresh = StrToInt(ini.sections["graphics"]["refresh"]);
    graphics.render_at_screenres = StrToBool(ini.sections["graphics"]["render_at_screenres"]);
    graphics.supersampling = StrToInt(ini.sections["graphics"]["supersampling"]);
    graphics.vsync = StrToBool(ini.sections["graphics"]["vsync"]);

    sound.digiid = ini.sections["sound"]["digiid"];
    sound.midiid = ini.sections["sound"]["midiid"];
    sound.usespeech = StrToBool(ini.sections["sound"]["usespeech"]);
    sound.threaded = StrToBool(ini.sections["sound"]["threaded"]);

    mouse.auto_lock = StrToBool(ini.sections["mouse"]["auto_lock"]);
    mouse.control_when = ini.sections["mouse"]["control_when"];
    mouse.control_enabled = StrToBool(ini.sections["mouse"]["control_enabled"]);
    mouse.speed_def = ini.sections["mouse"]["speed_def"];
    mouse.speed = StrToFloat(ini.sections["mouse"]["speed"]);

    language.translation = ini.sections["language"]["translation"];

    misc.log = StrToBool(ini.sections["misc"]["log"]);
    misc.datafile = ini.sections["misc"]["datafile"];
    misc.datadir = ini.sections["misc"]["datadir"];
    misc.user_data_dir = ini.sections["misc"]["user_data_dir"];
    misc.shared_data_dir = ini.sections["misc"]["shared_data_dir"];
    misc.antialias = StrToBool(ini.sections["misc"]["antialias"]);
    misc.cachemax = StrToInt(ini.sections["misc"]["cachemax"]);
}
