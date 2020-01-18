//
// Created by erico on 18/01/2020.
//

#include <fstream>
#include "agsdata.h"
#include "inipp.h"
#include "util_str.h"

using namespace std;

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

void AgsData::Graphics::Reset() {
    driver.reset();
    windowed.reset();
    screen_def.reset();
    screen_width.reset();
    screen_height.reset();
    match_device_ratio.reset();
    game_scale_fs.reset();
    game_scale_win.reset();
    filter.reset();
    refresh.reset();
    render_at_screenres.reset();
    supersampling.reset();
    vsync.reset();
}

AgsData::Sound::Sound() {
    digiid = "";
    midiid = "";
    usespeech = true;
    threaded = true;
}

void AgsData::Sound::Reset() {
    digiid.reset();
    midiid.reset();
    usespeech.reset();
    threaded.reset();
}

AgsData::Mouse::Mouse() {
    auto_lock = false;
    control_when = "never";
    control_enabled = false;
    speed_def = "absolute";
    speed = 1.0f;
}

void AgsData::Mouse::Reset() {
    auto_lock.reset();
    control_when.reset();
    control_enabled.reset();
    speed_def.reset();
    speed.reset();
}

AgsData::Language::Language() {
    translation = "";
}

void AgsData::Language::Reset() {
    translation.reset();
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

void AgsData::Misc::Reset() {
    log.reset();
    datafile.reset();
    datadir.reset();
    user_data_dir.reset();
    shared_data_dir.reset();
    antialias.reset();
    cachemax.reset();
}

AgsData::Override::Override() {
    multitasking = false;
    os = "";
    upscale = false;
}

void AgsData::Override::Reset() {
    multitasking.reset();
    os.reset();
    upscale.reset();
}

AgsData::Disabled::Disabled() {
    render_at_screenres = false;
    speechvox = false;
    filters = false;
}

void AgsData::Disabled::Reset() {
    render_at_screenres.reset();
    speechvox.reset();
    filters.reset();
}

string AgsData::ToIniString() {
    string ini_string;
    std::stringstream iniStream(ini_string);
    inipp::Ini<char> ini;
    if( graphics.driver.has_value())
        ini.sections["graphics"]["driver"] = graphics.driver.value();
    if( graphics.windowed.has_value())
        ini.sections["graphics"]["windowed"] = BoolToStr(graphics.windowed.value());
    if( graphics.screen_def.has_value())
        ini.sections["graphics"]["screen_def"] = graphics.screen_def.value();
    if( graphics.screen_width.has_value())
        ini.sections["graphics"]["screen_width"] = IntToStr(graphics.screen_width.value());
    if( graphics.screen_height.has_value())
        ini.sections["graphics"]["screen_height"] = IntToStr(graphics.screen_height.value());
    if( graphics.match_device_ratio.has_value())
        ini.sections["graphics"]["match_device_ratio"] = BoolToStr(graphics.match_device_ratio.value());
    if( graphics.game_scale_fs.has_value())
        ini.sections["graphics"]["game_scale_fs"] = graphics.game_scale_fs.value();
    if( graphics.game_scale_win.has_value())
        ini.sections["graphics"]["game_scale_win"] = graphics.game_scale_win.value();
    if( graphics.filter.has_value())
        ini.sections["graphics"]["filter"] = graphics.filter.value();
    if( graphics.refresh.has_value())
        ini.sections["graphics"]["refresh"] = IntToStr(graphics.refresh.value());
    if( graphics.render_at_screenres.has_value())
        ini.sections["graphics"]["render_at_screenres"] = BoolToStr(graphics.render_at_screenres.value());
    if( graphics.supersampling.has_value())
        ini.sections["graphics"]["supersampling"] = IntToStr(graphics.supersampling.value());
    if( graphics.vsync.has_value())
        ini.sections["graphics"]["vsync"] = BoolToStr(graphics.vsync.value());

    if( sound.digiid.has_value())
        ini.sections["sound"]["digiid"] = sound.digiid.value();
    if( sound.midiid.has_value())
        ini.sections["sound"]["midiid"] = sound.midiid.value();
    if( sound.usespeech.has_value())
        ini.sections["sound"]["usespeech"] = BoolToStr(sound.usespeech.value());
    if( sound.threaded.has_value())
        ini.sections["sound"]["threaded"] = BoolToStr(sound.threaded.value());

    if( mouse.auto_lock.has_value())
        ini.sections["mouse"]["auto_lock"] = BoolToStr(mouse.auto_lock.value());
    if( mouse.control_when.has_value())
        ini.sections["mouse"]["control_when"] = mouse.control_when.value();
    if( mouse.control_enabled.has_value())
        ini.sections["mouse"]["control_enabled"] = BoolToStr(mouse.control_enabled.value());
    if( mouse.speed_def.has_value())
        ini.sections["mouse"]["speed_def"] = mouse.speed_def.value();
    if( mouse.speed.has_value())
        ini.sections["mouse"]["speed"] = FloatToStr(mouse.speed.value());

    if( language.translation.has_value())
        ini.sections["language"]["translation"] = language.translation.value();

    if( misc.cachemax.has_value())
        ini.sections["misc"]["log"] = BoolToStr(misc.log.value());
    if( misc.datafile.has_value())
        ini.sections["misc"]["datafile"] = misc.datafile.value();
    if( misc.datadir.has_value())
        ini.sections["misc"]["datadir"] = misc.datadir.value();
    if( misc.user_data_dir.has_value())
        ini.sections["misc"]["user_data_dir"] = misc.user_data_dir.value();
    if( misc.shared_data_dir.has_value())
        ini.sections["misc"]["shared_data_dir"] = misc.shared_data_dir.value();
    if( misc.antialias.has_value())
        ini.sections["misc"]["antialias"] = BoolToStr(misc.antialias.value());
    if( misc.cachemax.has_value())
        ini.sections["misc"]["cachemax"] = IntToStr(misc.cachemax.value());

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

void AgsData::Reset() {
    graphics.Reset();
    sound.Reset();
    mouse.Reset();
    language.Reset();
    misc.Reset();
    override.Reset();
    disabled.Reset();
}
