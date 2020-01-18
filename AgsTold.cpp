//
// Created by erico on 18/01/2020.
//

#include "AgsTold.h"
#include "process.hpp"
#include "inipp.h"
#include "AgsConfigUtilStr.h"

AgsTold::Config_AT_graphics::Config_AT_graphics() {
    driver = "";
    windowed = false;
    screen_def = "";
    game_scale_fs = "";
    game_scale_win = "";
    filter = "";
    render_at_screenres = false;
    vsync = true;
}

AgsTold::Config_AT_sound::Config_AT_sound() {
    digiid = "-1";
    midiid = "-1";
    usespeech = true;
    threaded = true;
}

AgsTold::Config_AT_mouse::Config_AT_mouse() {
    auto_lock = false;
    control_enabled = true;
    speed = 1.0f;
}

AgsTold::Config_AT_language::Config_AT_language() {
    translation = "";
}

AgsTold::Config_AT_misc::Config_AT_misc() {
    antialias = false;
    cachemax = 131072;
    defaultres = 8;
    game_height = 480;
    game_width = 640;
    gamecolordepth = 32;
    letterbox = false;
    notruecolor = false;
    titletext = "AGS Config";
    shared_data_dir = "";
}

AgsTold::ConfigPath::ConfigPath() {
    _default = "";
    global = "";
    user = "";
}

AgsTold::Data::Data() {
    basepack = "";
    compiledwith = "";
    gamename = "";
    version = "";
}

AgsTold::Engine::Engine() {
    name = "";
    version = "";
}

AgsTold::Graphicdriver::Graphicdriver() {
    drivers = {};
}

void AgsTold::InitFromTell(string agsExecutable) {
    std::shared_ptr<std::string> output;
    output = std::make_shared<std::string>();

    std::string cmd_get_ags_config = agsExecutable + " --tell-all";

    TinyProcessLib::Process process(cmd_get_ags_config, "", [output](const char *bytes, size_t n) {
        *output += std::string(bytes, n);
    });

    inipp::Ini<char> ini;
    std::stringstream iniStream(*output);

    ini.parse(iniStream);

    config_AT_graphics.driver = ini.sections["config@graphics"]["driver"];
    config_AT_graphics.windowed = StrToBool(ini.sections["config@graphics"]["windowed"]);
    config_AT_graphics.screen_def = ini.sections["config@graphics"]["screen_def"];
    config_AT_graphics.game_scale_fs = ini.sections["config@graphics"]["game_scale_fs"];
    config_AT_graphics.game_scale_win = ini.sections["config@graphics"]["game_scale_win"];
    config_AT_graphics.filter = ini.sections["config@graphics"]["filter"];
    config_AT_graphics.render_at_screenres = StrToBool(ini.sections["config@graphics"]["render_at_screenres"]);
    config_AT_graphics.vsync = StrToBool(ini.sections["config@graphics"]["vsync"]);

    config_AT_sound.digiid = ini.sections["config@sound"]["digiid"];
    config_AT_sound.midiid = ini.sections["config@sound"]["midiid"];
    config_AT_sound.usespeech = StrToBool(ini.sections["config@sound"]["usespeech"]);
    config_AT_sound.threaded = StrToBool(ini.sections["config@sound"]["threaded"]);

    config_AT_mouse.auto_lock = StrToBool(ini.sections["config@mouse"]["control_enabled"]);
    config_AT_mouse.control_enabled = StrToBool(ini.sections["config@mouse"]["control_enabled"]);
    config_AT_mouse.speed = StrToFloat(ini.sections["config@mouse"]["speed"]);

    config_AT_language.translation = ini.sections["config@language"]["translation"];

    config_AT_misc.antialias = StrToBool(ini.sections["config@misc"]["antialias"]);
    config_AT_misc.cachemax = StrToInt(ini.sections["config@misc"]["cachemax"]);
    config_AT_misc.defaultres = StrToInt(ini.sections["config@misc"]["defaultres"]);
    config_AT_misc.game_height = StrToInt(ini.sections["config@misc"]["game_height"]);
    config_AT_misc.game_width = StrToInt(ini.sections["config@misc"]["game_width"]);
    config_AT_misc.gamecolordepth = StrToInt(ini.sections["config@misc"]["gamecolordepth"]);
    config_AT_misc.letterbox = StrToBool(ini.sections["config@misc"]["letterbox"]);
    config_AT_misc.notruecolor = StrToBool(ini.sections["config@misc"]["notruecolor"]);
    config_AT_misc.titletext = ini.sections["config@misc"]["titletext"];
    config_AT_misc.shared_data_dir = ini.sections["config@misc"]["shared_data_dir"];

    configPath._default = ini.sections["config@path"]["default"];
    configPath.global = ini.sections["config@path"]["global"];
    configPath.user = ini.sections["config@path"]["user"];

    data.basepack = ini.sections["data"]["basepack"];
    data.compiledwith = ini.sections["data"]["compiledwith"];
    data.gamename = ini.sections["data"]["gamename"];
    data.version = ini.sections["data"]["version"];

    engine.name = ini.sections["engine"]["name"];
    engine.version = ini.sections["engine"]["version"];

    graphicdriver.drivers.clear();
    if(!ini.sections["graphicdriver"]["0"].empty())
        graphicdriver.drivers.push_back(ini.sections["graphicdriver"]["0"]);
    if(!ini.sections["graphicdriver"]["1"].empty())
        graphicdriver.drivers.push_back(ini.sections["graphicdriver"]["1"]);
    if(!ini.sections["graphicdriver"]["2"].empty())
        graphicdriver.drivers.push_back(ini.sections["graphicdriver"]["2"]);
}
