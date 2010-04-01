/*
 *  This file is part of liblyrics
 *  Copyright (C) 2010
 *  	tilde  <tilde AT autistici DOT org>
 *  	malex  <malexprojects AT gmail DOT com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LYRICS_LYRICS_HPP
#define LYRICS_LYRICS_HPP

#include <string>
#include "types.hpp"

namespace lyrics {

class dispatcher {

	public:

	lyric getLyric(std::string,std::string);

	private:

	//ok, è brutto, ma mi pareva il modo + semplice
	bool inDatabase(std::string,std::string);

	lyric getFromCrawler(sitemode,std::string,std::string);
	lyric getFromDB(std::string,std::string);

};

} // namespace lyrics
#endif //LYRICS_LYRICS_HPP
