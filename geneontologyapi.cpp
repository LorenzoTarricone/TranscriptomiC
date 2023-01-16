#include "geneontologyapi.h"
#include <iostream>
#include <fstream>
using namespace std;

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main () {
    CURL* curl = curl_easy_init(); //Initialize curl
    std::string response;

    if (curl) { //Otherwise returns empty string
      // Search
      std::string url = "http://current.geneontology.org/ontology/go.obo";
      curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &WriteCallback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

      // Obtain the result
      CURLcode res = curl_easy_perform(curl);

      // Check for errors
      if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
      }

      // Reset curl
      curl_easy_cleanup(curl);
    }

    std::ofstream outfile ("geneontology.txt");
    outfile << response << std::endl;
    outfile.close();
    return 0;
}
