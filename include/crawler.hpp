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


#ifndef LYRICS_CRAWLER_HPP
#define LYRICS_CRAWLER_HPP

#include <string>
#include <curl/curl.h>
#include "types.hpp"

namespace liblyrics {

enum sitemode {
	ChartLyrics = 0
};

enum curlErr {
	NoErr = 0,
	ConnectionErr = 1,
	NotSuchSite = 2,
	ParsingErr = 3
};

class crawler {

	public:

	crawler();

	~crawler() {
		curl_easy_cleanup( this->curl );
	}

	lyric getLyric( std::string, std::string );

	std::string getCurlErrMessage() const;
	void setmode( sitemode );

	private:

	sitemode mode;

	std::string getData( std::string );
	lyric* getLyricFromXML( std::string );

	std::string atohex(std::string) const;
	std::string getTagContent( std::string,std::string* ) const;

	// cURL utils.
	static int curl_write( char*,size_t,size_t,std::string* );

	CURL* curl;
	CURLcode res;

	curlErr e;
	char* errMessage;

};

}  // namespace liblyrics

#endif // LYRICS_CRAWLER_HPP
