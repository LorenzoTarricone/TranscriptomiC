#include <iostream>
#include <string>
#include <curl/curl.h> // requires installation of libcurl

//Takes as input a string with the name of a gene and returns the gene id.

std::string searchGene(const std::string& geneName) {
  CURL* curl = curl_easy_init(); //Initialize curl
  std::string response;

  if (curl) { //Otherwise returns empty string
    // Search
    std::string url = "https://clinicaltables.nlm.nih.gov/api/ncbi_genes/v3/search?terms=" + geneName;
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

  return response;
}

// Appends the data to the response and returns the size of what was written
size_t WriteCallback(void* ptr, size_t size, size_t nmemb, std::string* data) {
  data->append((char*) ptr, size * nmemb);
  return size * nmemb;
}


//Example:
std::string geneName = "MEI";
std::string geneInfo = searchGene(geneName);
