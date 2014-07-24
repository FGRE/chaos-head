/* 
 * chaos-head: Alternative Chaos;Head Visual Novel executable
 * Copyright (C) 2014 Mislav Blažević <krofnica996@gmail.com>
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
#include "game.hpp"
#include "nsbinterpreter.hpp"
#include "resourcemgr.hpp"
#include "inipafile.hpp"
#include <thread>

static const char* ArchieveFileNames[] =
{
    "cg.npa",
    "nss.npa",
    "voice.npa",
    "sound.npa",
    nullptr
};

class CHResourceMgr : public ResourceMgr
{
public:
    CHResourceMgr(uint8_t GameID)
    {
        Archives.resize(sizeof(ArchieveFileNames) / sizeof(const char*) - 1);
        for (uint32_t i = 0; ArchieveFileNames[i]; ++i)
            Archives[i] = new INipaFile(ArchieveFileNames[i], GameID);
        assert(!Archives.empty());
    }

    // TODO: This is a hackfix to skip prefix like cg/ or nss/
    char* Read(std::string Path, uint32_t& Size)
    {
        size_t i = Path.find('/') + 1;
        return ResourceMgr::Read(Path.substr(i), Size);
    }

protected:
    ScriptFile* ReadScriptFile(const std::string& Path)
    {
        ScriptFile* pScript = nullptr;
        uint32_t NssSize;
        char* NssData = Read(Path, NssSize);

        if (NssData)
        {
            string Utf8Data = NpaFile::ToUtf8(NssData, NssSize);
            pScript = new ScriptFile(Path, Utf8Data.c_str(), Utf8Data.size());
        }

        delete[] NssData;
        return pScript;
    }
};

class CHInterpreter : public NsbInterpreter
{
public:
    CHInterpreter(uint8_t GameID)
    {
        NpaFile::SetLocale("ja_JP.CP932");
        sResourceMgr = new CHResourceMgr(GameID);
    }

    ~CHInterpreter()
    {
        pScriptThread->join();
        delete pScriptThread;
    }

    void Initialize(Game* pGame)
    {
        NsbInterpreter::Initialize(pGame);
        pScriptThread = new std::thread(std::bind(&CHInterpreter::Main, this));
    }

    void Main()
    {
        Start();
        ExecuteScript("nss/boot.nss");
    }

private:
    std::thread* pScriptThread;
};

int main(int argc, char** argv)
{
    uint8_t GameID = INipaFile::CHAOSHEAD;

    if (argc == 2)
    {
        GameID = INipaFile::GameStringToID(argv[2]);
        if (GameID == -1)
        {
            std::cout << "Invalid game specified." << std::endl;
            return 1;
        }
    }

    CHInterpreter* pInterpreter = new CHInterpreter(GameID);
    Game* pGame = new Game(pInterpreter, "FGRE: Chaos;Head");
    pGame->GLCallback(std::bind(&CHInterpreter::Initialize, pInterpreter, pGame));
    pGame->Run();
    delete pGame;
    delete sResourceMgr;
    delete pInterpreter;
}
