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
#include "CHWindow.hpp"
#include "inipafile.hpp"

int main(int argc, char** argv)
{
    uint8_t GameID = INipaFile::CHAOSHEAD;

    if (argc == 2)
    {
        GameID = INipaFile::GameStringToID(argv[1]);
        if (GameID == 0xFF)
        {
            std::cout << "Invalid game specified." << std::endl;
            return 1;
        }
    }

    unique_ptr<CHWindow> pWindow(new CHWindow(GameID));
    pWindow->Run();
}
