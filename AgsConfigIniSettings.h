//
// Created by erico on 19/01/2020.
//

#ifndef AGSCONFIG_AGSCONFIGINISETTINGS_H
#define AGSCONFIG_AGSCONFIGINISETTINGS_H

#include<string>
#include"nonstd/optional.hpp"
using namespace std;

class AgsConfigIniSettings {
    struct Game {
        optional <string> executable;
        void Reset();
        void SetSaneInitialValue();
        Game();
    };

    const string DefaultIni = ".config";
public:
    Game game = Game();

    void Reset();
    void SetSaneInitialValue();
    void LoadFromIni(const string& filename_with_path);
    void LoadFromIni();
    string ToIniString();
    void WriteToFile(const string& filename_with_path);
    void WriteToFile();
    AgsConfigIniSettings();
};


#endif //AGSCONFIG_AGSCONFIGINISETTINGS_H
