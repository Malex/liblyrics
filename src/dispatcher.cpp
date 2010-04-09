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
#include "dispatcher.hpp"

using namespace std;
using namespace liblyrics;

dispatcher::dispatcher( string dbPath ) {
	this->db = new dbinterface(dbPath);
	this->craw = new crawler();
}

dispatcher::~dispatcher() {
	delete this->db;
	delete this->craw;
}

int dispatcher::get( const string title, const string auth, string& outText ) {

	getLyric( title, auth, L );
	
	if( L.getStatus() == OK ) {
		outText = L.getText();
		return LYRIC_OK;
	} else {
		outText = L.getErrMsg();
		return LYRIC_DB_ERR;
	}


}

lyric& dispatcher::getLyric( const string title, const string auth, lyric& out ) {

	this->db->get( title, auth, out );
	
	if( out.getStatus() != OK ) {
		this->craw->getLyric( title, auth, out );
		this->db->addEntry( out );
	}

	return out;
}

