#ifndef LYRICS_CRAWLER_HPP
#define LYRICS_CRAWLER_HPP


#include "types.hpp"
#include <curl/curl.h>

enum sitemode {
	ChartLyrics = 0
};

enum curlErr {
	NoErr = 0,
	ConnectionErr = 1,
	ParsingErr = 2
};

class crawler {

	public:

	lyric getLyric(sitemode site, std::string auth, std::string title);

	crawler() {
		this->curl = curl_easy_init();
	}

	~crawler() {
		curl_easy_cleanup(this->curl);
	}

	//std::string getCurlErrMessage();

	private:

	CURL* curl;
	CURLcode res;

	curlErr e;
	//char* errMessage;

	//Needed for cURL
	static int curl_write(char* data,size_t size,size_t nsize,std::string* buffer);

	std::string getData(std::string path);
	std::string TextFromData(std::string data);

};
#endif // LYRICS_CRAWLER_HPP
