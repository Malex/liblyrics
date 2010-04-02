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

lyric crawler::getLyric(sitemode site, string title, string auth)
{
	string path;
	string lyr;
	lyric* ret;

	auth = crawler::atohex(auth);
	title = crawler::atohex(title);

	switch(site) {
		case ChartLyrics:
			path = "http://api.chartlyrics.com/apiv1.asmx/SearchLyricDirect?artist="+auth+"&song="+title;
			break;
		default:
			this->e = NotSuchSite;
			break;
	}

	if(this->e != NotSuchSite)
		lyr = this->getData(path);
	else
		ret->e.setStatus(WEB_OTHER,"Not supported sitemode");

	if(this->e == ConnectionErr) {
		ret->e.setStatus(WEB_OTHER,this->getCurlErrMessage());
	} else {
		ret = this->getLyricFromXML(lyr);
	}

	if(this->e == ParsingErr) {
		ret->e.setStatus(WEB_NO_RES,"Not valid XML file");
	}

	return *ret;
}

crawler::crawler()
{
	this->curl = curl_easy_init();

	curl_easy_setopt( this->curl, CURLOPT_HEADER, 0 );
	curl_easy_setopt( this->curl, CURLOPT_WRITEFUNCTION, crawler::curl_write );
	curl_easy_setopt( this->curl, CURLOPT_ERRORBUFFER, this->errMessage );
}

string crawler::getCurlErrMessage()
{
	if(this->e == ConnectionErr) {
		return (string) this->errMessage;
	} else {
		return "No cURL Error";
	}
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

string crawler::getData(string path)
{
	string ret;

	curl_easy_setopt( this->curl, CURLOPT_URL, path.c_str() );
	curl_easy_setopt( this->curl, CURLOPT_WRITEDATA, &ret );

	this->res = curl_easy_perform(this->curl);
	if(this->res!=0) {
		this->e = ConnectionErr;
	}
	return ret;
}

lyric* crawler::getLyricFromXML(string data)
{
	lyric* ret;
	string auth, title, text;

	title = crawler::getTagContent("<LyricSong>",&data);
	auth = crawler::getTagContent("<LyricArtist>",&data);
	text = crawler::getTagContent("<Lyric>",&data);

	if(text == "" || title == "" || auth == "") {
		this->e = ParsingErr;
		ret = new lyric();
		ret->e.setStatus(WEB_OTHER);
	} else {
		ret = new lyric(title,auth,text);
	}

	return ret;
}

string crawler::atohex(string str)
{
	char tmp[2];

	for(uint i=0;i<str.length();i++) {
		if((char) str[i] < 65 || ((char) str[i] > 90 && (char) str[i] < 97) || (char) str[i] > 122) {
			sprintf(tmp,"%x",(char) str[i]);
			str.insert(i,"%"+(string) tmp);
			str.erase(i+3,1);
			i+=2;
		}
	}
	return str;
}

string crawler::getTagContent(string tag, string* data)
{
	string ret;
	size_t p[2];

	p[0] = data->find(tag);
	tag.insert(1,"/");
	p[1] = data->find(tag);

	if(p[0] != string::npos) {
		ret = data->substr(p[0]+(tag.length())+1,p[1]-(p[0]+(tag.length())+1));
	} else {
		ret = "";
	}

	return ret;
}
