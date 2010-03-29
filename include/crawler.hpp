#ifndef LYRICS_CRAWLER_HPP
#define LYRICS_CRAWLER_HPP


#include "types.hpp"
#include <curl/curl.h>

enum sitemode {
	ChartLyrics = 0
};

class crawler {

	public:

	lyric getLyric(sitemode site, string auth, string title);

	crawler() {
		this->curl = curl_easy_init();
	}

	~crawler() {
		curl_easy_cleanup(this->curl);
	}

	private:

	CURL* curl;
	CURLcode res;

	string getText(string path);

};
#endif // LYRICS_CRAWLER_HPP
