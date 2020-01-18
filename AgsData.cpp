//
// Created by erico on 18/01/2020.
//

#include <fstream>
#include "AgsData.h"
#include "inipp.h"
#include "AgsConfigUtilStr.h"

using namespace std;

AgsData::Graphics::Graphics() {
    Reset();
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

void AgsData::Graphics::SetSaneInitialValue() {
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
    Reset();
}

void AgsData::Sound::Reset() {
    digiid.reset();
    midiid.reset();
    usespeech.reset();
    threaded.reset();
}

void AgsData::Sound::SetSaneInitialValue() {
    digiid = "";
    midiid = "";
    usespeech = true;
    threaded = true;
}

AgsData::Mouse::Mouse() {
    Reset();
}

void AgsData::Mouse::Reset() {
    auto_lock.reset();
    control_when.reset();
    control_enabled.reset();
    speed_def.reset();
    speed.reset();
}

void AgsData::Mouse::SetSaneInitialValue() {
    auto_lock = false;
    control_when = "never";
    control_enabled = false;
    speed_def = "absolute";
    speed = 1.0f;
}

AgsData::Language::Language() {
    Reset();
}

void AgsData::Language::Reset() {
    translation.reset();
}

void AgsData::Language::SetSaneInitialValue() {
    translation = "";
}

AgsData::Misc::Misc() {
    Reset();
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

void AgsData::Misc::SetSaneInitialValue() {
    log = false;
    datafile = "";
    datadir = "";
    user_data_dir = "";
    shared_data_dir = "";
    antialias = false;
    cachemax = 131072;
}

AgsData::Override::Override() {
    Reset();
}

void AgsData::Override::Reset() {
    multitasking.reset();
    os.reset();
    upscale.reset();
}

void AgsData::Override::SetSaneInitialValue() {
    multitasking = false;
    os = "";
    upscale = false;
}

AgsData::Disabled::Disabled() {
    Reset();
}

void AgsData::Disabled::Reset() {
    render_at_screenres.reset();
    speechvox.reset();
    filters.reset();
}

void AgsData::Disabled::SetSaneInitialValue() {
    render_at_screenres = false;
    speechvox = false;
    filters = false;
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
    Reset();
    inipp::Ini<char> ini;
    std::ifstream is(filename_with_path);
    ini.parse(is);

    if(!ini.sections["graphics"]["driver"].empty())
        graphics.driver = ini.sections["graphics"]["driver"];
    if(!ini.sections["graphics"]["windowed"].empty())
        graphics.windowed = StrToBool(ini.sections["graphics"]["windowed"]);
    if(!ini.sections["graphics"]["screen_def"].empty())
        graphics.screen_def = ini.sections["graphics"]["screen_def"];
    if(!ini.sections["graphics"]["screen_width"].empty())
        graphics.screen_width = StrToInt(ini.sections["graphics"]["screen_width"]);
    if(!ini.sections["graphics"]["screen_height"].empty())
        graphics.screen_height = StrToInt(ini.sections["graphics"]["screen_height"]);
    if(!ini.sections["graphics"]["match_device_ratio"].empty())
        graphics.match_device_ratio = StrToBool(ini.sections["graphics"]["match_device_ratio"]);
    if(!ini.sections["graphics"]["game_scale_fs"].empty())
        graphics.game_scale_fs = ini.sections["graphics"]["game_scale_fs"];
    if(!ini.sections["graphics"]["game_scale_win"].empty())
        graphics.game_scale_win = ini.sections["graphics"]["game_scale_win"];
    if(!ini.sections["graphics"]["filter"].empty())
        graphics.filter = ini.sections["graphics"]["filter"];
    if(!ini.sections["graphics"]["refresh"].empty())
        graphics.refresh = StrToInt(ini.sections["graphics"]["refresh"]);
    if(!ini.sections["graphics"]["render_at_screenres"].empty())
        graphics.render_at_screenres = StrToBool(ini.sections["graphics"]["render_at_screenres"]);
    if(!ini.sections["graphics"]["supersampling"].empty())
        graphics.supersampling = StrToInt(ini.sections["graphics"]["supersampling"]);
    if(!ini.sections["graphics"]["vsync"].empty())
        graphics.vsync = StrToBool(ini.sections["graphics"]["vsync"]);

    if(!ini.sections["sound"]["digiid"].empty())
        sound.digiid = ini.sections["sound"]["digiid"];
    if(!ini.sections["sound"]["midiid"].empty())
        sound.midiid = ini.sections["sound"]["midiid"];
    if(!ini.sections["sound"]["usespeech"].empty())
        sound.usespeech = StrToBool(ini.sections["sound"]["usespeech"]);
    if(!ini.sections["sound"]["threaded"].empty())
        sound.threaded = StrToBool(ini.sections["sound"]["threaded"]);

    if(!ini.sections["mouse"]["auto_lock"].empty())
        mouse.auto_lock = StrToBool(ini.sections["mouse"]["auto_lock"]);
    if(!ini.sections["mouse"]["control_when"].empty())
        mouse.control_when = ini.sections["mouse"]["control_when"];
    if(!ini.sections["mouse"]["control_enabled"].empty())
        mouse.control_enabled = StrToBool(ini.sections["mouse"]["control_enabled"]);
    if(!ini.sections["mouse"]["speed_def"].empty())
        mouse.speed_def = ini.sections["mouse"]["speed_def"];
    if(!ini.sections["mouse"]["speed"].empty())
        mouse.speed = StrToFloat(ini.sections["mouse"]["speed"]);

    if(!ini.sections["language"]["translation"].empty())
        language.translation = ini.sections["language"]["translation"];

    if(!ini.sections["misc"]["log"].empty())
        misc.log = StrToBool(ini.sections["misc"]["log"]);
    if(!ini.sections["misc"]["datafile"].empty())
        misc.datafile = ini.sections["misc"]["datafile"];
    if(!ini.sections["misc"]["datadir"].empty())
        misc.datadir = ini.sections["misc"]["datadir"];
    if(!ini.sections["misc"]["user_data_dir"].empty())
        misc.user_data_dir = ini.sections["misc"]["user_data_dir"];
    if(!ini.sections["misc"]["shared_data_dir"].empty())
        misc.shared_data_dir = ini.sections["misc"]["shared_data_dir"];
    if(!ini.sections["misc"]["antialias"].empty())
        misc.antialias = StrToBool(ini.sections["misc"]["antialias"]);
    if(!ini.sections["misc"]["cachemax"].empty())
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

void AgsData::SetSaneInitialValue() {
    graphics.SetSaneInitialValue();
    sound.SetSaneInitialValue();
    mouse.SetSaneInitialValue();
    language.SetSaneInitialValue();
    misc.SetSaneInitialValue();
    override.SetSaneInitialValue();
    disabled.SetSaneInitialValue();
}

void AgsData::MergeIn(AgsData data) {
    if(data.graphics.driver.has_value()) graphics.driver = data.graphics.driver.value();
    if(data.graphics.windowed.has_value()) graphics.windowed = data.graphics.windowed.value();
    if(data.graphics.screen_def.has_value()) graphics.screen_def = data.graphics.screen_def.value();
    if(data.graphics.screen_width.has_value()) graphics.screen_width = data.graphics.screen_width.value();
    if(data.graphics.match_device_ratio.has_value()) graphics.match_device_ratio = data.graphics.match_device_ratio.value();
    if(data.graphics.game_scale_fs.has_value()) graphics.game_scale_fs = data.graphics.game_scale_fs.value();
    if(data.graphics.game_scale_win.has_value()) graphics.game_scale_win = data.graphics.game_scale_win.value();
    if(data.graphics.filter.has_value()) graphics.filter = data.graphics.filter.value();
    if(data.graphics.refresh.has_value()) graphics.refresh = data.graphics.refresh.value();
    if(data.graphics.render_at_screenres.has_value()) graphics.render_at_screenres = data.graphics.render_at_screenres.value();
    if(data.graphics.supersampling.has_value()) graphics.supersampling = data.graphics.supersampling.value();
    if(data.graphics.vsync.has_value()) graphics.vsync = data.graphics.vsync.value();

    if(data.sound.digiid.has_value()) sound.digiid = data.sound.digiid.value();
    if(data.sound.midiid.has_value()) sound.midiid = data.sound.midiid.value();
    if(data.sound.usespeech.has_value()) sound.usespeech = data.sound.usespeech.value();
    if(data.sound.threaded.has_value()) sound.threaded = data.sound.threaded.value();

    if(data.mouse.auto_lock.has_value()) mouse.auto_lock = data.mouse.auto_lock.value();
    if(data.mouse.control_when.has_value()) mouse.control_when = data.mouse.control_when.value();
    if(data.mouse.control_enabled.has_value()) mouse.control_enabled = data.mouse.control_enabled.value();
    if(data.mouse.speed_def.has_value()) mouse.speed_def = data.mouse.speed_def.value();
    if(data.mouse.speed.has_value()) mouse.speed = data.mouse.speed.value();

    if(data.language.translation.has_value()) language.translation = data.language.translation.value();

    if(data.misc.log.has_value()) misc.log = data.misc.log.value();
    if(data.misc.datafile.has_value()) misc.datafile = data.misc.datafile.value();
    if(data.misc.datadir.has_value()) misc.datadir = data.misc.datadir.value();
    if(data.misc.user_data_dir.has_value()) misc.user_data_dir = data.misc.user_data_dir.value();
    if(data.misc.shared_data_dir.has_value()) misc.shared_data_dir = data.misc.shared_data_dir.value();
    if(data.misc.antialias.has_value()) misc.antialias = data.misc.antialias.value();
    if(data.misc.cachemax.has_value()) misc.cachemax = data.misc.cachemax.value();
}
