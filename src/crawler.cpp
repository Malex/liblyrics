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

#include <string>
#include "crawler.hpp"

using namespace std;
using namespace lyrics;

string crawler::getData(string path)
{
	string ret;

	curl_easy_setopt( this->curl, CURLOPT_URL, path.c_str() );
	curl_easy_setopt( this->curl, CURLOPT_HEADER, 0 );
	curl_easy_setopt( this->curl, CURLOPT_WRITEDATA, &ret );
	curl_easy_setopt( this->curl, CURLOPT_WRITEFUNCTION, crawler::curl_write );
	curl_easy_setopt( this->curl, CURLOPT_ERRORBUFFER, this->errMessage );

	this->res = curl_easy_perform(this->curl);
	if(this->res!=0) {
		this->e = ConnectionErr;
	}
	return ret;
}

int crawler::curl_write(char* data,size_t size,size_t nsize,string* buffer)
{
	int ret = 0;
	if(buffer!=NULL) {
		ret = size*nsize;
		buffer->append(data,ret);
	}
	return ret;
}

string crawler::getCurlErrMessage()
{
	if(this->e == ConnectionErr) {
		return (string) this->errMessage;
	} else {
		return "No cURL Error";
	}
}

string crawler::atohex(string str)
{
	char tmp[2];

	for(uint i=0;i<str.length();i++) {
		if((char) str[i] < 65 || ((char) str[i] > 90 && (char) str[i] < 97) || (char) str[i] > 122) {
			sprintf(tmp,"%x",(char) str[i]);
			str.insert(i,"%"+(string) tmp);
			str.erase(i,1);
			i+=2;
		}
	}

	return str;
}

lyric crawler::getLyric(sitemode site, string auth, string title)
{
	string path;
	string lyr;
	lyric* ret;

	auth = crawler::atohex(auth);
	title = crawler::atohex(title);

	switch(site) {
		case ChartLyrics:
			path = "http://api.chartlyrics.com/apiv1.asmx/SearchLyric?artist="+auth+"&song="+title;
			break;
		default:
			this->e = NotSuchSite;
			break;
	}

	if(this->e != NotSuchSite)
		lyr = this->getData(path);
	else
		ret->e.setStatus(WEB_OTHER);

	if(this->e == ConnectionErr) {
		ret->e.setStatus(WEB_OTHER);
	} else {
		ret = this->getLyricFromXML(lyr);
	}

	if(this->e == ParsingErr) {
		ret->e.setStatus(WEB_NO_RES);
	}

	return *ret;
}

lyric* crawler::getLyricFromXML(string data)
{
	lyric* ret;
	string auth, title, text;
	size_t auth_p[2], title_p[2], text_p[2];

	title_p[0] = data.find("<LyricSong>");
	title_p[1] = data.find("</LyricSong>");
	if(title_p[0] != string::npos) {
		title = data.substr(title_p[0]+12,title_p[1]-(title_p[0]+11));
	} else {
		title = "";
	}

	auth_p[0] = data.find("<LyricArtist>");
	auth_p[1] = data.find("</LyricArtist>");
	if(auth_p[0] != string::npos) {
		auth = data.substr(auth_p[0]+14,auth_p[1]-(auth_p[0]+13));
	} else {
		auth = "";
	}

	text_p[0] = data.find("<Lyric>");
	text_p[1] = data.find("</Lyric>");
	if(text_p[0] != string::npos) {
		text = data.substr(text_p[0]+8,text_p[1]-(text_p[0]+7));
	} else {
		text = "";
	}

	if(text == "" || title == "" || auth == "") {
		this->e = ParsingErr;
		ret = new lyric();
		ret->e.setStatus(WEB_OTHER);
	} else {
		ret = new lyric(title,auth,text);
	}

	return ret;
}

