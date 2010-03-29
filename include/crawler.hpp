#ifndef LYRICS_CRAWLER_HPP
#define LYRICS_CRAWLER_HPP

#include <curl/curl.h>

enum sitemode {
	ChartLyrics = 0;
};

class crawler {

	public:

	lyric getLyric(sitemode site, string auth, string title);
	crawler() {
		this->curl = curl_easy_init();
	}

	private:

	CURL* curl;
	CURLcode res;

	/* e qua mi stavo impiantando
	string getText(
	*/

};
#endif // LYRICS_CRAWLER_HPP
