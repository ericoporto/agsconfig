//
// Created by erico on 09/02/2020.
//

#ifndef AGSCONFIG_AGSCONFIGCORE_H
#define AGSCONFIG_AGSCONFIGCORE_H

#include <string>
#include <vector>

using std::string;
using std::vector;

#include "AgsConfigIniSettings.h"
#include "AgsData.h"
#include "AgsTold.h"

class AgsConfigCore {
private:

    AgsConfigIniSettings agsConfigIniSettings;
    AgsTold agsTold;

    AgsData agsData_default;
    AgsData agsData_global;
    AgsData agsData_user;

    AgsData agsData_current;

    AgsData agsData;

    vector<string> ScalingOptions;
    vector<string> FilterOptions;
    vector<string> SoundOptionsDigiid;
    vector<string> SoundOptionsMidiid;
    vector<string> SpriteCacheOptions = { "16 MB","32 MB","64 MB", "128 MB (default)","256 MB","512 MB"};
    vector<int> SpriteCacheOptionsValue = { 16*1024,32*1024,64*1024, 128*1024,256*1024,512*1024};

public:
    vector<string>* GetOptionsScalling();
    vector<string>* GetOptionsFilter();
    vector<string>* GetOptionsSoundDigiid();
    vector<string>* GetOptionsSoundMidiid();

    vector<string>* GetOptionsSpriteCache();
    vector<int>* GetOptionsSpriteCacheValue();
    vector<string>* GetOptionsGraphicsDriver();

    vector<string>* GetOptionsFullscrenScaling();
    vector<string>* GetOptionsWindowedScaling();

    AgsConfigIniSettings GetConfigIniSettings();

    void RunGame();

    void ResetConfigToCurrent();
    void ResetConfigToGameDefault();

    void SaveConfig();
    void Initialize();

    string GetGraphicsDriver();
    void SetGraphicsDriver(string graphics_driver);

    string GetFullscreenScale();
    void SetFullscreenScale(string fs_scale);

    string GetWindowedScale();
    void SetWindowedScale(string win_scale);

    string GetGraphicsFilter();
    void SetGraphicsFilter(string graphics_filter);

    string GetSpriteCacheMaxSize();
    void SetSpriteCacheMaxSize(int max_cache);

    string GetSoundDriver();
    void SetSoundDriver(string sound_driver);

    string GetMidiDriver();
    void SetMidiDriver(string midi_driver);

    bool* GraphicsWindowed;
    bool* GraphicsVsync;
    bool* GraphicsRenderAtScreenResolution;
    bool* GraphicsMatchDeviceRatio;
    bool* SoundThreaded;
    bool* SoundUsesSpeechPack;
    float* MouseSpeed;

    string GetTitleText();

    AgsConfigCore();
    ~AgsConfigCore(void);
};


#endif //AGSCONFIG_AGSCONFIGCORE_H
