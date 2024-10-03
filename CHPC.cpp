#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

namespace CodeDelay
{
    template <typename T> T waitForInput()
    {
        T temp;
        std::getline(std::cin, temp);
        return temp;
    }
}

class FileIterator
{
    typedef std::vector<std::string> FileLines;

private:
    FileLines fileLines;
    std::string fileContents;
    std::vector<std::string> result;

    // Helper function to split lines by new line and store in fileLines
    void splitLines()
    {
        std::stringstream sStream(this->fileContents);
        std::string line;
        while (std::getline(sStream, line))
        {
            fileLines.push_back(line);
        }
    }

    // Helper function to read the content of a file
    std::string readFile(const std::string& filePath)
    {
        std::ifstream file(filePath);
        if (!file.is_open()) 
        {
            std::cerr << "Error: Could not open file " << filePath << std::endl;
            return "";
        }
        
        std::stringstream buffer;
        buffer << file.rdbuf();  // Read the whole file into buffer
        return buffer.str();
    }

public:
    // Constructor to read the initial C++ file
    FileIterator(const std::string& filePath)
    {
        std::ifstream file(filePath);
        if (!file.is_open())
        {
            std::cerr << "Error: Could not open file " << filePath << std::endl;
            return;
        }

        // Read entire file contents into fileContents
        std::stringstream buffer;
        buffer << file.rdbuf();
        this->fileContents = buffer.str();
    }

    // Function to process the file and include header content
    void loadHeaders(const std::string& outputFilePath)
    {
        splitLines();

        for (const std::string& line : this->fileLines)
        {
            if (line.find("#include") != std::string::npos)
            {
                // Look for includes with double quotes (local headers)
                size_t open_quote = line.find('"');
                size_t close_quote = line.rfind('"');

                if (open_quote != std::string::npos && close_quote != std::string::npos && open_quote < close_quote)
                {
                    // Extract header file name from #include "header.h"
                    std::string headerFilePath = line.substr(open_quote + 1, close_quote - open_quote - 1);

                    // Read the header file contents
                    std::string headerContent = readFile(headerFilePath);

                    if (!headerContent.empty())
                    {
                        this->result.push_back(headerContent);  // Replace #include line with header content
                    }
                    else
                    {
                        this->result.push_back("// Error: Could not include " + headerFilePath);  // Error if the file can't be opened
                    }
                }
                else
                {
                    this->result.push_back(line);  // Keep the line if it's not a valid include
                }
            }
            else
            {
                this->result.push_back(line);  // Keep non-include lines
            }
        }

        // Write the result to the output file
        std::ofstream outputFile(outputFilePath);
        if (!outputFile.is_open())
        {
            std::cerr << "Error: Could not open output file " << outputFilePath << std::endl;
            return;
        }

        for (const std::string& resultLine : this->result)
        {
            outputFile << resultLine << "\n";
        }

        outputFile.close();
        std::cout << "Processed file written to " << outputFilePath << std::endl;
    }
};

int main(int argc, const char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input.cpp> <output.cpp>" << std::endl;
        return 1;
    }

    std::string inputFilePath = argv[1];
    std::string outputFilePath = argc > 2 ? argv[2] : "output.cpp";  // Default output file if not provided

    // Create FileIterator object and process the input file
    FileIterator fIterator(inputFilePath);
    fIterator.loadHeaders(outputFilePath);

    return 0;
}
