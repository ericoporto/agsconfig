//
// Created by erico on 18/01/2020.
//

#include <fstream>
#include "agsdata.h"
#include "inipp.h"

using namespace std;

string ToBoolStr(bool b){
    return b ? "1" : "0";
}

string ToIntStr(int i){
    return to_string(i);
}

string ToFloatStr(float f){
    return to_string(f);
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
    ini.sections["graphics"]["windowed"] = ToBoolStr(graphics.windowed);
    ini.sections["graphics"]["screen_def"] = graphics.screen_def;
    ini.sections["graphics"]["screen_width"] = ToIntStr(graphics.screen_width);
    ini.sections["graphics"]["screen_height"] = ToIntStr(graphics.screen_height);
    ini.sections["graphics"]["match_device_ratio"] = ToBoolStr(graphics.match_device_ratio);
    ini.sections["graphics"]["game_scale_fs"] = graphics.game_scale_fs;
    ini.sections["graphics"]["game_scale_win"] = graphics.game_scale_win;
    ini.sections["graphics"]["filter"] = graphics.filter;
    ini.sections["graphics"]["refresh"] = ToIntStr(graphics.refresh);
    ini.sections["graphics"]["render_at_screenres"] = ToBoolStr(graphics.render_at_screenres);
    ini.sections["graphics"]["supersampling"] = ToIntStr(graphics.supersampling);
    ini.sections["graphics"]["vsync"] = ToBoolStr(graphics.vsync);

    ini.sections["sound"]["digiid"] = sound.digiid;
    ini.sections["sound"]["midiid"] = sound.midiid;
    ini.sections["sound"]["usespeech"] = ToBoolStr(sound.usespeech);
    ini.sections["sound"]["threaded"] = ToBoolStr(sound.threaded);

    ini.sections["mouse"]["auto_lock"] = ToBoolStr(mouse.auto_lock);
    ini.sections["mouse"]["control_when"] = mouse.control_when;
    ini.sections["mouse"]["control_enabled"] = ToBoolStr(mouse.control_enabled);
    ini.sections["mouse"]["speed_def"] = mouse.speed_def;
    ini.sections["mouse"]["speed"] = ToFloatStr(mouse.speed);

    ini.sections["language"]["translation"] = language.translation;

    ini.sections["misc"]["log"] = ToBoolStr(misc.log);
    ini.sections["misc"]["datafile"] = misc.datafile;
    ini.sections["misc"]["datadir"] = misc.datadir;
    ini.sections["misc"]["user_data_dir"] = misc.user_data_dir;
    ini.sections["misc"]["shared_data_dir"] = misc.shared_data_dir;
    ini.sections["misc"]["antialias"] = ToBoolStr(misc.antialias);
    ini.sections["misc"]["cachemax"] = ToIntStr(misc.cachemax);

    ini.generate(iniStream);
    ini_string = iniStream.str();
    return ini_string;
}

void AgsData::WriteToFile(const string& filename_with_path) {
    ofstream output_ini_file(filename_with_path);
    output_ini_file << ToIniString();
    output_ini_file.close();
}
