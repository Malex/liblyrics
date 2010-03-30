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


#include "crawler.hpp"

std::string crawler::getData(std::string path)
{
	std::string ret;
	uint perform;

	curl_easy_setopt( this->curl, CURLOPT_URL, path.c_str() );
	curl_easy_setopt( this->curl, CURLOPT_HEADER, 0 );
	curl_easy_setopt( this->curl, CURLOPT_WRITEDATA, &ret );
	curl_easy_setopt( this->curl, CURLOPT_WRITEFUNCTION, crawler::curl_write );
	//curl_easy_setopt( this->curl, CURLOPT_ERRORBUFFER, this->errMessage );

	perform = curl_easy_perform(this->curl);
	if(perform!=0) {
		this->e = ConnectionErr;
	}
	return ret;
}

static int crawler::curl_write(char* data,size_t size,size_t nsize,std::string* buffer)
{
	int ret = 0;
	if(buffer!=NULL) {
		ret = size*nsize;
		buffer->append(data,ret);
	}
	return ret;
}

/*std::string getCurlErrMessage()
{
	if(this->e == ConnectionErr) {
		return (string) this->errMessage;
	} else {
		return "No cURL Error";
	}
}*/

lyric crawler::getLyric(sitemode site, std::string auth, std::string title)
{
	std::string path;
	std::string lyr;
	lyric* ret

	switch(site) {
		case ChartLyrics:
			path = "http://api.chartlyrics.com/apiv1.asmx/SearchLyric?artist="+auth+"&song="+title;
			break;
		default:
			path = "";
			break;
	}

	lyr = this->TextFromData( this->getData(path) );

	if(this->e == ConnectionErr) {
		ret->e.setError(WEB_OTHER);
	} else if(this->e == ParsingErr) {
		ret->e.setError(WEB_NO_RES);
	} else {
		ret = new lyric(title,auth,lyr);
	}

	return *ret;
}







