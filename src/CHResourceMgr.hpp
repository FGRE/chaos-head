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
#ifndef CH_RESOURCE_MGR_HPP
#define CH_RESOURCE_MGR_HPP

#include "ResourceMgr.hpp"

class CHResourceMgr : public ResourceMgr
{
public:
    CHResourceMgr(uint8_t GameID);

    char* Read(std::string Path, uint32_t& Size);
    Resource GetResource(std::string Path);

protected:
    ScriptFile* ReadScriptFile(const std::string& Path);
};

#endif
