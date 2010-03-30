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

#define uint unsigned int

namespace lyrics {

enum status_t {
	OK		= 0,
	DB_NO_ENTRY	= 1,
	DB_OTHER	= 2,
	WEB_NO_RES	= 3,
	WEB_OTHER	= 4
};

class errors {

	public:

	errors() {
		status = OK;
		this->initeMsg();
	}

	errors( int  init ) {
		status = (status_t) init;
		this->initeMsg();
	}

	int getStatus() {
		return this->status;
	}

	std::string getErrMsg() {
		return this->eMsg[this->status];
	}

	void setError( int error ) {
		this->status = error;
	}

	private:
	
	status_t status;

	std::string eMsg[5];
	// non ho trovato un modo migliore, così fa cagare ma funzia.
	void initeMsg() {
		status = OK;

		eMsg[0]	= "All ok.";
		eMsg[1] = "No corrispondence in db.";
		eMsg[2] = "Unknown db error.";
		eMsg[3] = "No corrispondence in internet.";
		eMsg[4] = "Unknown web error.";

	}
};


class lyric {

	public:

	lyric( std::string title, std::string auth , std::string text ) {
		this->title	= title;
		this->author	= auth;
		this->text	= text; 
	}

	std::string getTitle() {
		return this->title;
	}

	std::string getAuth() {
		return this->author;
	}

	std::string getText() {
		return this->text;
	}	

	errors e;

	private:

	std::string title;
	std::string author;
	std::string text;

};


}

#endif // TYPES_HPP
