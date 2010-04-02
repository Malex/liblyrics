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
#include "dbinterface.hpp"
#include "types.hpp"

using namespace std;
using namespace lyrics;

dbinterface::dbinterface( string dbPath ) {
	this->dbinit( dbPath );
	
	this->outLyric.setData( "","","" );
	this->outLyric.e.setStatus( NOT_INIT );

}

lyric dbinterface::get( string title, string author ) {

	string QGetEntry = "select distinct * from lyrics where \
			title='"+title+"'and author='"+author+"'";
	string ltitle;
	string lauth;
	string ltext;

	// TODO: Gestione errori
	this->retval = sqlite3_prepare_v2( dbHandle, QGetEntry.c_str(),
				-1, &stmt, NULL );	
	
	while( sqlite3_step(stmt) == SQLITE_ROW ) { 
		for( int i=1; i<sqlite3_column_count(stmt); ++i ) {
		
			if( (string)sqlite3_column_name(stmt, i) == "title")  {
	
				ltitle = (const char*)sqlite3_column_text(stmt,i);
	
			} else if( (string)sqlite3_column_name(stmt, i) == "author") {
	
				lauth = (const char*)sqlite3_column_text(stmt,i);
	
			} else if( (string)sqlite3_column_name(stmt, i) == "text")  {
	
				ltext = (const char*)sqlite3_column_text(stmt,i);
	
			} else {
				//TODO: HERE
			}
		}
	}
	//TODO: Gestione errori
	this->outLyric.setData( ltitle, lauth, ltext ); 
	this->outLyric.e.setStatus( OK );
	return this->outLyric;

}

void dbinterface::addEntry( lyric in ) {

	//TODO: Gestione errori.
	string QAddEntry = "insert into lyrics(title, author, text) \
			values('"+in.getTitle()+"','"+in.getAuth()+"','"+in.getText()+"')";
	this->retval = sqlite3_prepare_v2( dbHandle, QAddEntry.c_str(), 
				-1, &stmt, NULL );
	this->retval = sqlite3_step( stmt );

}

// Private

void dbinterface::dbinit( string dbPath ) {

	string QCreateTable = "create table if not exists lyrics (\
			id integer primary key autoincrement,\
			title varchar(255),\
			author varchar(255),\
			text data)";

	// TODO: Gestione errori
	this->retval = sqlite3_open( dbPath.c_str(), &dbHandle );

	this->retval = sqlite3_prepare_v2( dbHandle, QCreateTable.c_str(),
				-1, &stmt, NULL );
	this->retval = sqlite3_step( stmt );
	
}

