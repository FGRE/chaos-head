/* 
 * chaos-head: Alternative Chaos;Head Visual Novel executable
 * Copyright (C) 2014-2016 Mislav Blažević <krofnica996@gmail.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * */
#include "CHResourceMgr.hpp"
#include "inipafile.hpp"
#include "scriptfile.hpp"

static const char* ArchieveFileNames[] =
{
    "cg.npa",
    "nss.npa",
    "voice.npa",
    "sound.npa",
    nullptr
};

CHResourceMgr::CHResourceMgr(uint8_t GameID)
{
    Archives.resize(sizeof(ArchieveFileNames) / sizeof(const char*) - 1);
    for (uint32_t i = 0; ArchieveFileNames[i]; ++i)
        Archives[i] = new INipaFile(ArchieveFileNames[i], GameID);
    assert(!Archives.empty());
}

// TODO: This is a hackfix to skip prefix like cg/ or nss/
char* CHResourceMgr::Read(std::string Path, uint32_t& Size)
{
    return ResourceMgr::Read(Path.substr(Path.find('/') + 1), Size);
}

// TODO: Also a hackfix
Resource CHResourceMgr::GetResource(std::string Path)
{
    return ResourceMgr::GetResource(Path.substr(Path.find('/') + 1));
}

ScriptFile* CHResourceMgr::ReadScriptFile(const std::string& Path)
{
    ScriptFile* pScript = nullptr;
    uint32_t NssSize;
    char* NssData = Read(Path, NssSize);

    if (NssData)
    {
        string Utf8Data = NpaFile::ToUtf8(NssData, NssSize);
        pScript = new ScriptFile(Path, Utf8Data.c_str(), Utf8Data.size());
        delete[] NssData;
    }

    return pScript;
}
