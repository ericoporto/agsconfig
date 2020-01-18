//
// Created by erico on 18/01/2020.
//

#include "agstold.h"

agstold::Config_AT_graphics::Config_AT_graphics() {
    driver = "";
    windowed = false;
    screen_def = "";
    game_scale_fs = "";
    game_scale_win = "";
    filter = "";
    render_at_screenres = false;
    vsync = true;
}

agstold::Config_AT_sound::Config_AT_sound() {
    digiid = "-1";
    midiid = "-1";
    usespeech = true;
    threaded = true;
}

agstold::Config_AT_mouse::Config_AT_mouse() {
    auto_lock = false;
    control_enabled = true;
    speed = 1.0f;
}

agstold::Config_AT_language::Config_AT_language() {
    translation = "";
}

agstold::Config_AT_misc::Config_AT_misc() {
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

agstold::ConfigPath::ConfigPath() {
    _default = "";
    global = "";
    user = "";
}

agstold::Data::Data() {
    basepack = "";
    compiledwith = "";
    gamename = "";
    version = "";
}

agstold::Engine::Engine() {
    name = "";
    version = "";
}

agstold::Graphicdriver::Graphicdriver() {
    drivers = {};
}

