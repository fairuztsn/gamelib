#include <iostream>
#include <string>
#include <fstring>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        //std::cerr << "Usage: " << argv[0] << " --dir=\"your_directory\"" << std::endl;
        return 1;
    }

    std::string key;
    std::string value;
    size_t equalSignPosition;

    for(int i=0; i < argc; i ++) {
        std::string argument = argv[i];
        std::cout<<argument<<std::endl;

        if(argument.compare(0, 2, "--") == 0) {
            equalSignPosition = argument.find("=");
            key = argument.substr(2,equalSignPosition-2);
            if(key == "help") {
                // TODO: Add usage
                std::cout<<"Usage"<<std::endl;
                return 1;
            }
            
            value = argument.substr(equalSignPosition+1);
        }
    }
    
    return 0;
}