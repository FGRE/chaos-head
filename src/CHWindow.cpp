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
#include "CHInterpreter.hpp"

CHWindow::CHWindow(uint8_t GameID) : Window("FGRE: Chaos;Head", 800, 600)
{
    pInterpreter = new CHInterpreter(this, GameID);
    pInterpreter->ExecuteScript("nss/boot.nss");
}
