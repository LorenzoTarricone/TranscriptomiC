<<<<<<< Updated upstream
#include <iostream>
#include <string>
#include <curl/curl.h> // requires installation of libcurl

std::string searchBioProcess(const std::string& geneList, const std::string& geneOrganism) {
  CURL* curl = curl_easy_init(); //Initialize curl
  std::string response;
  std::string annotDataSet;

  if (curl) { //Otherwise returns empty string
    // Search
    std::string url = "http://pantherdb.org/services/oai/pantherdb/supportedannotdatasets";
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &annotDataSet);

    // Obtain the result
    CURLcode res = curl_easy_perform(curl);

    // Check for errors
    if (res != CURLE_OK) {
      std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
    }

    // Reset curl
    curl_easy_cleanup(curl);
  }

  if (curl) { //Otherwise returns empty string
    // Search
    std::string url = "http://pantherdb.org/services/oai/pantherdb/enrich/overrep?geneInputList=" + geneList + "&organism=" + geneOrganism + "&annotDataSet=" + annotDataSet + "&enrichmentTestType=FISHER&correction=FDR";
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
std::string geneList = "MEI";
std::string geneOrganism = "9606";
std::string geneBioProcess = searchBioProcess(geneList);
=======
#include <iostream>
#include <string>
#include <curl/curl.h> // requires installation of libcurl

std::string searchBioProcess(const std::string& geneList, const std::string& geneOrganism) {
  CURL* curl = curl_easy_init(); //Initialize curl
  std::string response;
  std::string annotDataSet;

  if (curl) { //Otherwise returns empty string
    // Search
    std::string url = "http://pantherdb.org/services/oai/pantherdb/supportedannotdatasets";
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &annotDataSet);

    // Obtain the result
    CURLcode res = curl_easy_perform(curl);

    // Check for errors
    if (res != CURLE_OK) {
      std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
    }

    // Reset curl
    curl_easy_cleanup(curl);
  }

  if (curl) { //Otherwise returns empty string
    // Search
    std::string url = "http://pantherdb.org/services/oai/pantherdb/enrich/overrep?geneInputList=" + geneList + "&organism=" + geneOrganism + "&annotDataSet=" + annotDataSet + "&enrichmentTestType=FISHER&correction=FDR";
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
std::string geneList = "MEI";
std::string geneOrganism = "9606";
std::string geneBioProcess = searchBioProcess(geneList);
>>>>>>> Stashed changes
