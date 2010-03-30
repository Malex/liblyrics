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


#ifndef LYRICS_DBINTERFACE_HPP
#define LYRICS_DBINTERFACE_HPP

#include <string>

namespace lyrics{

class dbinterface {

	public:
	
	dbinterface();
	dbinterface( std::string dbPath );
	// questo ↑ è provvisorio, alla fine sarà
	// dbinterface( config );
	
	lyric get( string title, string author);
	void addEntry( lyric );
	// per ora non serve altro.

	private:

	void dbinit();

	string dbpath;
	sqlite3*	dbHandle;
	sqlite3_stmt*	stmt;
	uint 		retval;
	// Queryes. TODO: c'è un modo migliore?
	string QgetEntry;
	string QaddEntry;



};

} // namespace lyrics

#endif // LYRICS_DBINTERFACE_HPP
