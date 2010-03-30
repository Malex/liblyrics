/*
 *  This file is part of liblyrics
 *  Copyright (C) 2010  
 *  	tilde  <tilde AT autistici DOT org>
 *  	malex
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


#include "types.hpp"
#include <curl/curl.h>

enum sitemode {
	ChartLyrics = 0
};

enum curlErr {
	NoErr = 0,
	ConnectionErr = 1,
	ParsingErr = 2
};

class crawler {

	public:

	lyric getLyric(sitemode site, std::string auth, std::string title);

	crawler() {
		this->curl = curl_easy_init();
	}

	~crawler() {
		curl_easy_cleanup(this->curl);
	}

	//std::string getCurlErrMessage();

	private:

	CURL* curl;
	CURLcode res;

	curlErr e;
	//char* errMessage;

	//Needed for cURL
	static int curl_write(char* data,size_t size,size_t nsize,std::string* buffer);

	std::string getData(std::string path);
	std::string TextFromData(std::string data);

};
#endif // LYRICS_CRAWLER_HPP
