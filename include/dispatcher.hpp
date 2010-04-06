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
#include "crawler.hpp"
#include "dbinterface.hpp"

namespace lyrics {

class dispatcher {

	public:

	dispatcher();
	dispatcher(std::string);

	~dispatcher();

	std::string get( std::string, std::string) const;
	lyric getLyric(std::string,std::string) const;

	std::string getStatus() const;

	private:

	lyric getLyric(std::string,std::string,sitemode) const;

	// Queste a che servono?
	std::string status;
	void setStatus(std::string);

	lyric getFromCrawler(sitemode,std::string,std::string) const;
	lyric getFromDB(std::string,std::string) const;

	dbinterface* db;
	crawler* craw;
};

} // namespace lyrics

#endif //LYRICS_LYRICS_HPP
