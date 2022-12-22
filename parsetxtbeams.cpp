#include "parsetxtbeams.h"
#include <random>
#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif


parseTxtBeams::parseTxtBeams()
{
    std::vector<std::string> beams =  std::vector<std::string>();
    std::vector<int> x_coord = std::vector<int>();
    std::vector<int> y_coord = std::vector<int>();
}

void parseTxtBeams::readFile(std::string filename){
    // from https://techoverflow.net/2020/01/30/how-to-read-tsv-tab-separated-values-in-c/

    std::ifstream fin(filename,std::ios::in);
    std::string beam,x,y;


    if(!fin){
        std::cerr << "[ERROR] File " << filename << " could not be opened. Stopping program" << std::endl;
    }
    else{
        std::cout << "[SUCCESS] File " << filename << " opened successfully" << std::endl;
    }

    int count = 0;

    // this method relies on the fact that all rows are filled and columns are in order "beam" "x coordinate" "y coordinate"

    // get beam name
    while (getline(fin, beam, '\t')) {

        // get x coordinate as string
        std::getline(fin,x,'\t');

        // get y coordinate as string
        std::getline(fin,y,'\n');

        // add columns to respective private vectors
        this->beams.push_back(beam);
        this->x.push_back(stoi(x));
        this->y.push_back(stoi(y));

        // visualize data read
        std::cout << count << "\t" << "Beam: " << beam << "\t x-coordinate: " << x << "\t y-coordinate: " << y << std::endl;


        count++;
    }
    // close file
    fin.close();


}

void parseTxtBeams::createDummyFile(unsigned int rows, std::string filename){
    // this operation sets the seed for the randomization (generates different values for each iteration)
    srand(time(nullptr));

    // list of base names
    std::vector<std::string> list{"A", "G", "T", "C"};


    // file stream
    std::ofstream fout;

    // open file
    fout.open(filename);

    // check if file was opened correctly
    if(!fout){
        std::cerr << "[ERROR] File " << filename << " could not be opened. Stopping program" << std::endl;
    }
    else{
        std::cout << "[SUCCESS] File " << filename << " opened successfully" << std::endl;
    }


    // define maximum range for coordinates
    int MAX_COORD = 2000;

    for(unsigned int i = 0; i < rows; i++){ //for each row i

        // randomly generate a beam name
        std::string beam = "";
        for(int j = 0; j < 9; j++){
            int index = random()%list.size(); // pick a random index
            std::string base = list[index];
            beam.append(base);
        }
        int x = random()%MAX_COORD;
        int y = random()%MAX_COORD;
        fout << beam << "\t" << x << "\t" << y << "\n";
        std::cout << beam << "\t" << x << "\t" << y << "\n" << std::endl;
    }
    // close the file (stream)
    fout.close();
}
