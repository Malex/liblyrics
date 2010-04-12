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
using namespace liblyrics;


crawler::crawler() {
	this->curl = curl_easy_init();

	curl_easy_setopt( this->curl, CURLOPT_HEADER, 0 );
	curl_easy_setopt( this->curl, CURLOPT_WRITEFUNCTION, crawler::curl_write );
	curl_easy_setopt( this->curl, CURLOPT_ERRORBUFFER, this->errMessage );

	this->setmode( ChartLyrics );
}

lyric& crawler::getLyric( string title, string auth, lyric& out ) {

	string path;
	string rawLyric;

	auth = crawler::atohex( auth );
	title = crawler::atohex( title );

	switch( this->mode ) {
		case ChartLyrics:
			path = "http://api.chartlyrics.com/apiv1.asmx/SearchLyricDirect?artist="+auth+"&song="+title;
			break;
		default:
			out.setStatus( CRAW_ERR, "Not Such Site" );
			return out;
			break;
	}


	rawLyric = this->getData( path );

	// I define res in the getData function, is the curl error code.
	if( this->res != 0 ) {
		out.setStatus( CRAW_ERR , (string)this->errMessage );
		return out;
	} else {
		this->getLyricFromXML( rawLyric, out );
	}

	return out;
}

void crawler::setmode( sitemode m ) {
	this->mode = m;
}

string crawler::getData( string& path ) {
	string ret;

	curl_easy_setopt( this->curl, CURLOPT_URL, path.c_str() );
	curl_easy_setopt( this->curl, CURLOPT_WRITEDATA, &ret );

	this->res = curl_easy_perform( this->curl );

	return ret;
}

lyric& crawler::getLyricFromXML( string& data, lyric& out ) {

	string auth, title, text;

	title = crawler::getTagContent( "<LyricSong>",data );
	auth = crawler::getTagContent( "<LyricArtist>",data );
	text = crawler::getTagContent( "<Lyric>",data );

	if( text == "" || title == "" || auth == "" ) {
		out.setStatus( CRAW_ERR, "Error while parsing XML" );
	} else {
		out.setData( title,auth,text );
	}

	return out;
}

string& crawler::atohex( string& str ) const {
	char tmp[2];

	for( size_t i=0; i<str.length(); i++ ) {
		if( (char) str[i] < 65 ||
			((char) str[i] > 90 && (char) str[i] < 97) ||
			(char) str[i] > 122 ) {

			sprintf( tmp, "%x", (char) str[i] );
			str.insert( i, "%"+(string) tmp );
			str.erase( i+3, 1 );
			i+=2;

		}
	}
	return str;
}

string crawler::getTagContent( string tag, string& data ) const {
	string ret;
	size_t p[2];

	p[0] = data.find( tag );
	tag.insert(1,"/");
	p[1] = data.find( tag );

	if( p[0] != string::npos ) {
		ret = data.substr( p[0]-1+(tag.length()),p[1]+1-(p[0]+(tag.length())) );
	} else {
		ret = "";
	}

	return ret;
}

int crawler::curl_write( char* data, size_t size, size_t nsize, string& buffer ) {
	int ret = 0;
	if( &buffer !=NULL ) {
		ret = size*nsize;
		buffer.append( data,ret );
	}
	return ret;
}
