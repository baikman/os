#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include "lodepng.h"

using namespace std;

vector<unsigned char> image;
unsigned width, height;

void decode(const char* filename) {
    // Decode image at filename into vector<unsigned char> image
    lodepng::decode(image, width, height, filename);
}

void encode(const char* filename, vector<unsigned char>& image, unsigned width, unsigned height) {
    // Encode image at filename with vector<unsigned char> image
    lodepng::encode(filename, image, width, height);
}

void modify(const char* textBuff) {
    // Every 4 (RGB*A*) characters, replace with respective character from encoded message
    for (int textIdx = 0, i = 3; i < image.size() && textIdx < strlen(textBuff); i += 4) {
        image[i] = textBuff[textIdx++];
        image[i + 4] = '\0';
    }
}

void decodeText(void) {
    // Print every four characters from the image vector.
    for (int i = 3, textIdx = 3; i < image.size() && image[i]; i += 4) cout << image[i];
    cout << endl;
}

const char* fileToTextBuff(const char* textBuff) {
    // Set file as an input stream and buffer as an output string stream
    ifstream file(textBuff);
    ostringstream buffer;

    // Dump all of file(textBuff) into the buffer stream and create a string from it
    buffer << file.rdbuf();
    string buffString = buffer.str();

    // c-string to hold the contents of buffString
    char* returnBuff = new char[buffString.length() + 1]; 
    strcpy(returnBuff, buffString.c_str());

    file.close();

    return (const char*)returnBuff;
}

void textBuffToFile(const char* file) {
    // Decodes image to provided file.
    ofstream outFile(file);
    for (int i = 3, textIdx = 3; i < image.size() && image[i]; i += 4) outFile << image[i];
    outFile.close();
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cerr << "Please provide at least two arguments to the program in the following format:\n";
        cerr << "./steg.exe -e <original image name> <modified image name> [input ASCII text file name]\n";
        cerr << "./steg.exe -d <modified image name> [output ASCII text file name]\n";
        return 1;
    }

    const char* modeSel = argv[1];
    const char* filename = argv[2];
    const char* postFilename;
    const char* textBuff;

    if (strcmp(modeSel, "-e") == 0) {
        if (argc < 4 || argc > 5) {
            cerr << "For encoding, at least two arguments are needed in the followin format:\n";
            cerr << "./steg.exe -e <original image name> <modified image name> [input ASCII text file name]\n";
            return 1;
        }
        postFilename = argv[3];
        if (argc == 5) {  
            textBuff = argv[4];
            decode(filename);
            // Determine if argv[4] is a one-word argument to be encoded or if it is a file name with .txt extension
            const char *extension = strchr(textBuff, '.');
            if (extension && strcmp(extension, ".txt") == 0) {
                const char *newBuff = fileToTextBuff(textBuff);
                modify(newBuff);
            } else {
                modify(textBuff);
            }
        } else {
            // Gather input from stdin
            cout << "Enter lines to be encoded. When done, hit enter twice.\n";
            string input, line;
            while (getline(cin, line) && !line.empty()) input += line + '\n';
            input.pop_back();
            const char *newBuff = new char[input.size()];
            strcpy((char*)newBuff, input.c_str());
            decode(filename);
            modify(newBuff);
        }
        
        encode(postFilename, image, width, height);
        cout << "Encoded image!\n";
    } else if (strcmp(modeSel, "-d") == 0) {
        decode(filename);
        if (argc < 4) decodeText();
        else textBuffToFile(argv[3]);
        cout << "Decoded image!\n";
    }
    
    return 0;
}