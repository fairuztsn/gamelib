#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>

std::map<std::string, std::string> readGamelibFile(const std::string &filename)
{
    std::ifstream inFile(filename);
    std::map<std::string, std::string> fileContent;

    std::string line, key, value;
    size_t equalSignPosition;

    while (std::getline(inFile, line))
    {
        if (!line.empty())
        {
            equalSignPosition = line.find("=");

            if (equalSignPosition != std::string::npos)
            {
                key = line.substr(0, equalSignPosition);
                value = line.substr(equalSignPosition + 1);

                fileContent[key] = value;
            }
            else
            {
                std::cerr << "Invalid line format: " << line << std::endl;
            }
        }
    }

    return fileContent;
}

int main(int argc, char *argv[]) 
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " --dir=\"your_directory\"" << std::endl;
        return 1;
    }

    std::string key;
    std::string value;
    std::string fileName = ".gamelib";
    
    size_t equalSignPosition;

    std::ifstream fileCheck(fileName);

    if (!fileCheck)
    {
        std::ofstream newFile(fileName);
    }

    std::map<std::string, std::string> gameDirectoryMap = readGamelibFile(fileName);

    for(int i=0; i < argc; i ++) 
    {
        std::string argument = argv[i];

        if(argument.compare(0, 2, "--") == 0) 
        {
            equalSignPosition = argument.find("=");
            key = argument.substr(2,equalSignPosition-2);
            
            if(key == "help") {
                // TODO: Add usage
                std::cout<<"Usage"<<std::endl;
                return 0;
            }else if(key == "remove") {
                if(argc == 2) {
                    std::cerr<<"No arguments found, use eg. --remove game1 game2 ..";
                    return 1;
                }

                for (int j = 2; j < argc; ++j)
                {
                    auto it = gameDirectoryMap.find(argv[j]);

                    if (it != gameDirectoryMap.end())
                    {
                        gameDirectoryMap.erase(it);
                        std::cout << "'" << argv[j] << "' removed from the lib." << std::endl;
                    }
                    else
                    {
                        std::cerr << "'" << argv[j] << "' not found in the lib." << std::endl;
                    }
                }

                break;
            }else if(key == "ls") {
                return 0;
            }
            
            value = argument.substr(equalSignPosition+1);
            gameDirectoryMap[key] = value;

            std::cout<<key<<"="<<gameDirectoryMap[key]<<std::endl;
        }
    }

    std::ofstream outFile(fileName);
    
    if (outFile.is_open())
    {
        for (std::map<std::string, std::string>::const_iterator it = gameDirectoryMap.begin(); it != gameDirectoryMap.end(); ++it)
        {
            const std::string &key = it->first;
            const std::string &value = it->second;
            outFile<<key<<"="<<value<<std::endl;
        }
    }else
    {
        std::cerr << "Unable to open the .gamelib file for writing." << std::endl;
    }
    
    outFile.close();
    
    return 0;
}