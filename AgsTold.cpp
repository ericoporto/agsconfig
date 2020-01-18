//
// Created by erico on 18/01/2020.
//

#include "AgsTold.h"
#include "process.hpp"
#include "inipp.h"
#include "AgsConfigUtilStr.h"
#ifdef WIN32
#include "dirent.h"
#else
#include <unistd.h>
#include <dirent.h>
#endif

std::string get_working_path()
{
    char temp[512];
    return ( getcwd(temp, sizeof(temp)) ? std::string( temp ) : std::string("") );
}

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

void AgsTold::InitFromTell(const string agsExecutable) {
    string current_dir = get_working_path();
    std::shared_ptr<std::string> output;
    output = std::make_shared<std::string>();

    std::string cmd_get_ags_config = "";
    cmd_get_ags_config = current_dir + "/" + agsExecutable + " " + "--tell-all";

    TinyProcessLib::Process process(cmd_get_ags_config, "", [output](const char *bytes, size_t n) {
        *output += std::string(bytes, n);
    });

    // get exit status is actually blocking apparently! There's a while there so we need this here.
    if(process.get_exit_status() != 0){
        //error
        return;
    }

    inipp::Ini<char> ini;
    std::stringstream iniStream(*output);

    ini.parse(iniStream);

    if(!ini.sections["config@graphics"]["driver"].empty())
        config_AT_graphics.driver = ini.sections["config@graphics"]["driver"];
    if(!ini.sections["config@graphics"]["windowed"].empty())
        config_AT_graphics.windowed = StrToBool(ini.sections["config@graphics"]["windowed"]);
    if(!ini.sections["config@graphics"]["screen_def"].empty())
        config_AT_graphics.screen_def = ini.sections["config@graphics"]["screen_def"];
    if(!ini.sections["config@graphics"]["game_scale_fs"].empty())
        config_AT_graphics.game_scale_fs = ini.sections["config@graphics"]["game_scale_fs"];
    if(!ini.sections["config@graphics"]["game_scale_win"].empty())
        config_AT_graphics.game_scale_win = ini.sections["config@graphics"]["game_scale_win"];
    if(!ini.sections["config@graphics"]["filter"].empty())
        config_AT_graphics.filter = ini.sections["config@graphics"]["filter"];
    if(!ini.sections["config@graphics"]["render_at_screenres"].empty())
        config_AT_graphics.render_at_screenres = StrToBool(ini.sections["config@graphics"]["render_at_screenres"]);
    if(!ini.sections["config@graphics"]["vsync"].empty())
        config_AT_graphics.vsync = StrToBool(ini.sections["config@graphics"]["vsync"]);

    if(!ini.sections["config@sound"]["digiid"].empty())
        config_AT_sound.digiid = ini.sections["config@sound"]["digiid"];
    if(!ini.sections["config@sound"]["midiid"].empty())
        config_AT_sound.midiid = ini.sections["config@sound"]["midiid"];
    if(!ini.sections["config@sound"]["usespeech"].empty())
        config_AT_sound.usespeech = StrToBool(ini.sections["config@sound"]["usespeech"]);
    if(!ini.sections["config@sound"]["threaded"].empty())
        config_AT_sound.threaded = StrToBool(ini.sections["config@sound"]["threaded"]);

    if(!ini.sections["config@mouse"]["auto_lock"].empty())
        config_AT_mouse.auto_lock = StrToBool(ini.sections["config@mouse"]["auto_lock"]);
    if(!ini.sections["config@mouse"]["control_enabled"].empty())
        config_AT_mouse.control_enabled = StrToBool(ini.sections["config@mouse"]["control_enabled"]);
    if(!ini.sections["config@mouse"]["speed"].empty())
        config_AT_mouse.speed = StrToFloat(ini.sections["config@mouse"]["speed"]);

    if(!ini.sections["config@language"]["translation"].empty())
        config_AT_language.translation = ini.sections["config@language"]["translation"];

    if(!ini.sections["config@misc"]["antialias"].empty())
        config_AT_misc.antialias = StrToBool(ini.sections["config@misc"]["antialias"]);
    if(!ini.sections["config@misc"]["cachemax"].empty())
        config_AT_misc.cachemax = StrToInt(ini.sections["config@misc"]["cachemax"]);
    if(!ini.sections["config@misc"]["defaultres"].empty())
        config_AT_misc.defaultres = StrToInt(ini.sections["config@misc"]["defaultres"]);
    if(!ini.sections["config@misc"]["game_height"].empty())
        config_AT_misc.game_height = StrToInt(ini.sections["config@misc"]["game_height"]);
    if(!ini.sections["config@misc"]["game_width"].empty())
        config_AT_misc.game_width = StrToInt(ini.sections["config@misc"]["game_width"]);
    if(!ini.sections["config@misc"]["gamecolordepth"].empty())
        config_AT_misc.gamecolordepth = StrToInt(ini.sections["config@misc"]["gamecolordepth"]);
    if(!ini.sections["config@misc"]["letterbox"].empty())
        config_AT_misc.letterbox = StrToBool(ini.sections["config@misc"]["letterbox"]);
    if(!ini.sections["config@misc"]["notruecolor"].empty())
        config_AT_misc.notruecolor = StrToBool(ini.sections["config@misc"]["notruecolor"]);
    if(!ini.sections["config@misc"]["titletext"].empty())
        config_AT_misc.titletext = ini.sections["config@misc"]["titletext"];
    if(!ini.sections["config@misc"]["shared_data_dir"].empty())
        config_AT_misc.shared_data_dir = ini.sections["config@misc"]["shared_data_dir"];

    if(!ini.sections["config@path"]["default"].empty())
        configPath._default = ini.sections["config@path"]["default"];
    if(!ini.sections["config@path"]["global"].empty())
        configPath.global = ini.sections["config@path"]["global"];
    if(!ini.sections["config@path"]["user"].empty())
        configPath.user = ini.sections["config@path"]["user"];

    if(!ini.sections["data"]["basepack"].empty())
        data.basepack = ini.sections["data"]["basepack"];
    if(!ini.sections["data"]["compiledwith"].empty())
        data.compiledwith = ini.sections["data"]["compiledwith"];
    if(!ini.sections["data"]["gamename"].empty())
        data.gamename = ini.sections["data"]["gamename"];
    if(!ini.sections["data"]["version"].empty())
        data.version = ini.sections["data"]["version"];

    if(!ini.sections["engine"]["name"].empty())
        engine.name = ini.sections["engine"]["name"];
    if(!ini.sections["engine"]["version"].empty())
        engine.version = ini.sections["engine"]["version"];

    graphicdriver.drivers.clear();
    if(!ini.sections["graphicdriver"]["0"].empty())
        graphicdriver.drivers.push_back(ini.sections["graphicdriver"]["0"]);
    if(!ini.sections["graphicdriver"]["1"].empty())
        graphicdriver.drivers.push_back(ini.sections["graphicdriver"]["1"]);
    if(!ini.sections["graphicdriver"]["2"].empty())
        graphicdriver.drivers.push_back(ini.sections["graphicdriver"]["2"]);

}
