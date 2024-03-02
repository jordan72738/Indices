#include <curl/curl.h>
#include <string>
#include <iostream>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string fetchUrl(const std::string &url) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        
        // Check for errors: if(res != CURLE_OK) ...
    }
    return readBuffer;
}

int main() {
    std::string content = fetchUrl("https://quod.lib.umich.edu/cgi/r/rsv/rsv-idx?type=DIV1&byte=4697892");
    // Now, content contains the fetched data, which can then be passed to the SHA256::hash function.