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
#include "lyrics.hpp"

using namespace std;
using namespace lyrics;

dispatcher::dispatcher()
{
	this->db = new dbinterface("data.db");
	this->craw = new crawler();
}

dispatcher::dispatcher(string dbPath)
{
	this->db = new dbinterface(dbPath);
	this->craw = new crawler();
}

dispatcher::~dispatcher()
{
	delete this->db;
	delete this->craw;
}

lyric dispatcher::getLyric(string title,string auth) const
{
	return this->getLyric(title,auth,ChartLyrics);
}

lyric dispatcher::getLyric(string title,string auth,sitemode site) const 
{
	lyric ret;

	ret = this->db->get(title,auth);

	if(ret.e.getStatus()!= OK) {
		ret = this->craw->getLyric(site,title,auth);
		this->db->addEntry(&ret);
	}

	return ret;
}

string dispatcher::getStatus() const
{
	return this->status;
}

void dispatcher::setStatus(string new_status)
{
	this->status = new_status;
}
