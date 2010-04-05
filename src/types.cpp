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
#include "types.hpp"

using namespace std;
using namespace lyrics;

// Errors class implementation.

errors::errors() {
	status = OK;
	this->errMsg 	= "Nothing happened this far.";
}

status_t errors::getStatus() const {
	return this->status;
}

string errors::getErrMsg() const {
	return this->errMsg;
}

void errors::setStatus( status_t estatus ) {
	if( estatus == OK ) {
		this->status = OK;
		this->errMsg =  "All ok.";
	} else {
		this->status = estatus;
		this->errMsg = "No error message specified.";
	}
}

void errors::setStatus( status_t error, string estatus )
{
	this->status = error;
	this->errMsg = estatus;
}

// Lyric class implementation.

lyric::lyric() {
	this->setData( "", "", "" );
	this->e.setStatus( NOT_INIT, "The lyric was not initalized" );
}

lyric::lyric( string title, string auth, string text ) {
	this->setData( title, auth, text );
	this->e.setStatus( OK );
}

string lyric::getTitle() const {
	return this->title;
}

string lyric::getAuth() const {
	return this->author;
}

string lyric::getText() const {
	return this->text;
}

void lyric::setData( string title, string auth, string text ) {
	this->title	= title;
	this->author	= auth;
	this->text	= text;
	this->e.setStatus( OK );
}

