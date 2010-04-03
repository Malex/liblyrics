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

namespace lyrics {

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
		curl_easy_cleanup(this->curl);
	}

	lyric getLyric(sitemode, std::string, std::string);

	std::string getCurlErrMessage();

	private:

	CURL* curl;
	CURLcode res;

	curlErr e;
	char* errMessage;

	std::string getData(std::string);
	lyrics::lyric* getLyricFromXML(std::string);

	std::string atohex(std::string);
	std::string getTagContent(std::string,std::string*);

	// cURL utils.
	static int curl_write(char*,size_t,size_t,std::string*);
};

}  // namespace lyrics

#endif // LYRICS_CRAWLER_HPP
