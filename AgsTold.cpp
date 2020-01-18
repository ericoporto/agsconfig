//
// Created by erico on 18/01/2020.
//

#include "AgsTold.h"
#include "process.hpp"
#include "inipp.h"
#include "util_str.h"

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
    config_AT_graphics.windowed = ini.sections["config@graphics"]["windowed"];
    config_AT_graphics.screen_def = ini.sections["config@graphics"]["screen_def"];
    config_AT_graphics.game_scale_fs = ini.sections["config@graphics"]["game_scale_fs"];
    config_AT_graphics.game_scale_win = ini.sections["config@graphics"]["game_scale_win"];
    config_AT_graphics.filter = ini.sections["config@graphics"]["filter"];
    config_AT_graphics.render_at_screenres = ini.sections["config@graphics"]["render_at_screenres"];
    config_AT_graphics.vsync = ini.sections["config@graphics"]["vsync"];

    config_AT_sound.digiid
    config_AT_sound.midiid
    config_AT_sound.usespeech
    config_AT_sound.threaded

    config_AT_mouse.auto_lock
    config_AT_mouse.control_enabled
    config_AT_mouse.speed

    config_AT_language.translation

    config_AT_misc.antialias
    config_AT_misc.cachemax
    config_AT_misc.defaultres
    config_AT_misc.game_height
    config_AT_misc.game_width
    config_AT_misc.gamecolordepth
    config_AT_misc.letterbox
    config_AT_misc.notruecolor
    config_AT_misc.titletext
    config_AT_misc.shared_data_dir


    config_AT_path._default
    config_AT_path.global
    config_AT_path.user

    data.basepack
    data.compiledwith
    data.gamename
    data.version

    engine.name
    engine.version

    graphicdriver.drivers
}
