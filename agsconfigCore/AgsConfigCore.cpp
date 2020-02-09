//
// Created by erico on 09/02/2020.
//

#include "AgsConfigCore.h"
#include "AgsData.h"
#include "AgsTold.h"
#include <fstream>
#include <iostream>
#include "inipp.h"
#include "AgsConfigUtilStr.h"
#include "AgsConfigIniSettings.h"
using std::string;
using std::vector;

const char* NumberToAutoOrNone(const char * cString) {
    if(std::string(cString) == "0") return "none";
    else if(std::string(cString) == "-1") return "auto";
    return cString;
}

const char* KBNumberToCString(int kb) {
    int mb = kb/1024;
    return string(IntToStr(mb) + " MB").c_str();
}

AgsConfigCore::AgsConfigCore() {
    Initialize();
}

AgsConfigCore::~AgsConfigCore(void) {

}


vector<string>* AgsConfigCore::GetOptionsScalling() {
    return &ScalingOptions;
}

vector<string>* AgsConfigCore::GetOptionsFilter() {
    return &FilterOptions;
}

vector<string>* AgsConfigCore::GetOptionsSoundDigiid() {
    return &SoundOptionsDigiid;
}

vector<string>* AgsConfigCore::GetOptionsSoundMidiid() {
    return &SoundOptionsMidiid;
}

vector<string>* AgsConfigCore::GetOptionsSpriteCache() {
    return &SpriteCacheOptions;
}

vector<int>* AgsConfigCore::GetOptionsSpriteCacheValue() {
    return &SpriteCacheOptionsValue;
}

vector<string>* AgsConfigCore::GetOptionsGraphicsDriver() {
    return &(agsTold.graphicdriver.drivers);
}

vector<string>* AgsConfigCore::GetOptionsFullscrenScaling() {
    return &ScalingOptions;
}

vector<string>* AgsConfigCore::GetOptionsWindowedScaling() {
    return &ScalingOptions;
}

void AgsConfigCore::SaveConfig() {
    agsData.WriteToFile(agsTold.configPath.user);
}

void AgsConfigCore::RunGame() {
    agsTold.RunGame();
}

void AgsConfigCore::Initialize() {
#ifdef LINUX
    SoundOptionsDigiid = { "auto", "none", "ALSA", "ARTS", "ESSD", "JACK", "OSSD", "SGIA", "SDL" };
    SoundOptionsMidiid = { "auto","none","AMID", "OSSM"};
#elif WIN32
    SoundOptionsDigiid = { "auto", "none","DXA","AXA","WOA"};
    SoundOptionsMidiid = { "auto","none","W32M","W32A"};
#else
    //Need to figure out what's available on MacOS!
    SoundOptionsDigiid = { "auto", "none"};
    SoundOptionsMidiid = { "auto", "none"};
#endif

    ScalingOptions = {"max_round", "stretch", "proportional", "1", "2", "3" };
    FilterOptions = { "none", "stdscale" };

    SpriteCacheOptions = { "16 MB","32 MB","64 MB", "128 MB (default)","256 MB","512 MB"};
    SpriteCacheOptionsValue = { 16*1024,32*1024,64*1024, 128*1024,256*1024,512*1024};

    agsConfigIniSettings.Reset();
    agsConfigIniSettings.SetSaneInitialValue();
    agsConfigIniSettings.LoadFromIni();
    agsTold.InitFromTell(agsConfigIniSettings.game.executable.value());

    agsData_default.Reset();
    agsData_default.LoadFromIni(agsTold.configPath._default);
    agsData_global.Reset();
    agsData_global.LoadFromIni(agsTold.configPath.global);
    agsData_user.Reset();
    agsData_user.LoadFromIni(agsTold.configPath.user);

    agsData_current.Reset();
    agsData_current.MergeIn(agsData_default);
    agsData_current.MergeIn(agsData_user);
    agsData_current.MergeIn(agsData_global);

    agsData.Reset();
    agsData.SetSaneInitialValue();
    agsData.MergeIn(agsData_current);
    GraphicsWindowed = &(agsData.graphics.windowed.value());
    GraphicsVsync = &(agsData.graphics.vsync.value());
    GraphicsRenderAtScreenResolution = &(agsData.graphics.render_at_screenres.value());
    GraphicsMatchDeviceRatio = &(agsData.graphics.match_device_ratio.value());
    SoundThreaded = &(agsData.sound.threaded.value());
    SoundUsesSpeechPack = &(agsData.sound.usespeech.value());
    MouseSpeed = &(agsData.mouse.speed.value());
}

AgsConfigIniSettings AgsConfigCore::GetConfigIniSettings() {
    return agsConfigIniSettings;
}

void AgsConfigCore::ResetConfigToCurrent() {
    agsData.SetSaneInitialValue();
    agsData.MergeIn(agsData_current);
}

void AgsConfigCore::ResetConfigToGameDefault() {
    agsData.SetSaneInitialValue();
    agsData.MergeIn(agsData_default);
}

string AgsConfigCore::GetGraphicsDriver() {
    return agsData.graphics.driver.value();
}

void AgsConfigCore::SetGraphicsDriver(string graphics_driver) {
    agsData.graphics.driver = graphics_driver;
}

string AgsConfigCore::GetFullscreenScale() {
    return agsData.graphics.game_scale_fs.value();
}

void AgsConfigCore::SetFullscreenScale(string fs_scale) {
    agsData.graphics.game_scale_fs = fs_scale;
}

string AgsConfigCore::GetWindowedScale() {
    return agsData.graphics.game_scale_win.value();
}

void AgsConfigCore::SetWindowedScale(string win_scale) {
    agsData.graphics.game_scale_win = win_scale;
}

string AgsConfigCore::GetGraphicsFilter() {
    return agsData.graphics.filter.value();
}

void AgsConfigCore::SetGraphicsFilter(string graphics_filter) {
    agsData.graphics.filter = graphics_filter;
}

string AgsConfigCore::GetSpriteCacheMaxSize() {
    if(agsData.misc.cachemax.has_value()) {
        return KBNumberToCString(agsData.misc.cachemax.value());
    }
    return KBNumberToCString(128*1024);
}

void AgsConfigCore::SetSpriteCacheMaxSize(int max_cache) {
    agsData.misc.cachemax = max_cache;
}

string AgsConfigCore::GetSoundDriver() {
    return  NumberToAutoOrNone(agsData.sound.digiid.value().c_str());
}

void AgsConfigCore::SetSoundDriver(string sound_driver) {
    agsData.sound.digiid = sound_driver;
}

string AgsConfigCore::GetMidiDriver() {
    return NumberToAutoOrNone(agsData.sound.midiid.value().c_str());
}

void AgsConfigCore::SetMidiDriver(string midi_driver) {
    agsData.sound.midiid = midi_driver;
}

string AgsConfigCore::GetTitleText() {
    return agsTold.config_AT_misc.titletext;
}
