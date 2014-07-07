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

ResourceMgr* CreateResourceMgr(const std::vector<std::string>& AchieveFileNames, uint8_t GameID)
{
    std::vector<INpaFile*> Archives;
    Archives.resize(AchieveFileNames.size());
    for (uint32_t i = 0; i < AchieveFileNames.size(); ++i)
        Archives[i] = new INipaFile(AchieveFileNames[i], GameID);
    return new ResourceMgr(Archives);
}

class CHInterpreter : public NsbInterpreter
{
public:
    CHInterpreter(uint8_t GameID)
    {
        NpaFile::SetLocale("ja_JP.CP932");
        sResourceMgr = CreateResourceMgr({"cg.npa", "nss.npa", "voice.npa", "sound.npa"}, GameID);
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
