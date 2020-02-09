//
// Created by erico on 19/01/2020.
//

#include <fstream>
#include "AgsConfigIniSettings.h"
#include "inipp.h"
#include "AgsConfigUtilStr.h"

AgsConfigIniSettings::Game::Game() {
    Reset();
}

void AgsConfigIniSettings::Game::Reset() {
    executable.reset();
}

void AgsConfigIniSettings::Game::SetSaneInitialValue() {
    // we can't guess the game name
    executable = (string) "ags"; //TODO: do not hardcode this!!!!!!!!!
}

void AgsConfigIniSettings::Reset() {
    game.Reset();
}

void AgsConfigIniSettings::SetSaneInitialValue() {
    game.SetSaneInitialValue();
}

void AgsConfigIniSettings::LoadFromIni(const string &filename_with_path) {
    inipp::Ini<char> ini;
    std::ifstream is(filename_with_path);
    ini.parse(is);

    if(!ini.sections["game"]["executable"].empty())
        game.executable = ini.sections["game"]["executable"];
}

string AgsConfigIniSettings::ToIniString() {
    string ini_string;
    std::stringstream iniStream(ini_string);
    inipp::Ini<char> ini;

    if( game.executable.has_value())
        ini.sections["game"]["executable"] = game.executable.value();

    ini.generate(iniStream);
    ini_string = iniStream.str();
    return ini_string;
}

void AgsConfigIniSettings::WriteToFile(const string &filename_with_path) {
    ofstream output_ini_file(filename_with_path);
    output_ini_file << ToIniString();
    output_ini_file.close();
}

void AgsConfigIniSettings::LoadFromIni() {
    LoadFromIni(DefaultIni);
}

void AgsConfigIniSettings::WriteToFile() {
    WriteToFile(DefaultIni);
}

AgsConfigIniSettings::AgsConfigIniSettings() {
    Reset();
}
