#include <iostream>

int main()
{
    size_t pageSum = 9808;
    size_t tempCount = 0;

    for(size_t i = 1; i < pageSum; ++i){
        tempCount = i;

        for(size_t j = i + 1; j < pageSum; ++j){
            tempCount += j;

            if(tempCount == pageSum){
                std :: cout << "from page " << i << " to page " << j << std :: endl;
            }
        }
    }

    //291 322

    return 0;
}
