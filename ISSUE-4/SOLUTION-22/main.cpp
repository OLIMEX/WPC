#include <cstdio>
#include <cctype>
#include <cstring>
#include <vector>

using namespace std;

#define MAX_WORD_LENGTH 4096

unsigned int maxIsogramLength = 0; // Length of the longest isograms
vector<char*> maxIsograms; // Container of longest isograms

inline void deleteIsograms(){
    for(unsigned int i = 0; i < maxIsograms.size(); i++){ delete [] maxIsograms[i]; }
    maxIsograms.clear();
}

int main(int argc, char* argv[]){

    // arg checks: exactly one argument is needed and the text file must be available for reading
    if(argc != 2){
        printf("Usage: Olimex_W4 TEXT_FILE\nExample: Olimex_W4 alice_in_wonderland.txt\n");
        return 1;
    }
    FILE* textFile = fopen(argv[1], "r");
    if (!textFile){
        printf("Cannot open text file: %s\n", argv[1]);
        return 2;
    }

    // Var init
    char* word = new char[MAX_WORD_LENGTH]; // Word buffer
    int ch;

    // Loop through each word
    do{
        // Read a word
        char* wordIndex = word - 1;
        do{
            ch = fgetc(textFile);
            if(ch != EOF){
                *(++wordIndex) = tolower(static_cast<char>(ch));
                if(!isalpha(*wordIndex)) break;
            }else{
                ++wordIndex;
                break;
            }
        }while(true);

        // Add string termination
        *wordIndex = '\0';

        // Check if the word is an isogram
        unsigned int len = wordIndex - word;
        // Filter by length to speed up the test
        if(len >= maxIsogramLength){
            // Check if the word is an isogram
            bool isIsogram = true;
            for(unsigned int i = 0; i < len && isIsogram; i++){
                char c = word[i];
                for(unsigned int j = i + 1; j < len && isIsogram; j++){
                    if(c == word[j]) isIsogram = false;
                }
            }

            // If yes, update the length and the container of longest isograms
            if(isIsogram){
                if(len > maxIsogramLength){
                    maxIsogramLength = len;
                    deleteIsograms();
                }
                if(len > 0){
                    char* wordCopy = new char[len + 1];
                    strcpy(wordCopy, word);
                    maxIsograms.push_back(wordCopy);
                }
            }
        }
    } while(ch != EOF);

    // Print the results
    unsigned int numOfMaxIsograms = maxIsograms.size();
    printf("Number of longest isograms: %u\n", numOfMaxIsograms);
    printf("Isogram length: %u\n", maxIsogramLength);
    printf("Isogram(s):\n");
    for(unsigned int i = 0; i < numOfMaxIsograms; i++){
        printf("\t%s\n", maxIsograms[i]);
    }
    deleteIsograms();
    delete [] word;
    fclose(textFile);
    return 0;
}
