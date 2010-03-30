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

#include <string>
#include "types.hpp"

using namespace std;
using namespace lyrics;

// Errors class implementation.

errors::errors() {
	status = OK;
	this->initeMsg();
}

errors::errors( int init )  {
	this->setStatus( init );
	this->initeMsg();
}

status_t errors::getStatus() {
	return this->status;
}

string errors::getErrMsg()  {
	return this->eMsg[this->status];
}

void errors::setStatus( int error ) {
	this->status = (status_t)error;
}


// Pivate.

// TODO: Sistemare più in dettaglio con gli errori di curl.
void errors::initeMsg() {
	eMsg[0]	= "All ok.";
	eMsg[1] = "The lyric was not initialized.";
	eMsg[2] = "No corrispondence in db.";		
	eMsg[3] = "Unknown db error.";
	eMsg[4] = "No corrispondence in internet.";
	eMsg[5] = "Unknown web error.";
}


// Lyric class implementation.

lyric::lyric() {
	this->setData( "", "", "" );
	this->e.setStatus( NOT_INIT );
}

lyric::lyric( string title, string auth, string text ) {
	this->setData( title, auth, text );
}

string lyric::getTitle() {
	return this->title;
}

string lyric::getAuth() {
	return this->author;
}

string lyric::getText() {
	return this->text;
}

void lyric::setData( string title, string auth, string text ) {
	this->title	= title;
	this->author	= auth;
	this->text	= text;
	this->e.setStatus( OK );
}
