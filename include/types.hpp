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


#ifndef LYRICS_TIPES_HPP
#define LYRICS_TYPES_HPP

#include <string>


namespace lyrics {

typedef unsigned int uint;

// TODO: Sistemare più in dettaglio con gli errori di curl.
enum status_t {
	OK		= 0,
	NOT_INIT	= 1,
	DB_NO_ENTRY	= 2,
	DB_OTHER	= 3,
	WEB_NO_RES	= 4,
	WEB_OTHER	= 5
};

class errors {

	public:

	errors();
	errors( int );

	status_t getStatus();

	std::string getErrMsg();
	void setStatus( int );

	private:
	
	void initeMsg(); 

	status_t status;
	std::string eMsg[6];
};

class lyric {

	public:

	lyric();
	lyric( std::string, std::string , std::string ) ;

	std::string getTitle(); 
	std::string getAuth();
	std::string getText();
	void setData( std::string, std::string, std::string );

	errors e;

	private:

	std::string title;
	std::string author;
	std::string text;

};


} // namespace lyrics

#endif // TYPES_HPP
