//Name: Divya Bengali
//Date: November 21st, 2025 
//Title: Lab7 – Step 3
//Description: This program reads the output using a FIFO alogrithm.

//NOTE: I took out the total faults variable from the skeleton since the lab didn't ask for it


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>


//GIVEN:REQUIRMEMNR TO DEFINE
typedef struct{
    int pageno;
}ref_page;

static int parse_page_num(const char *line, int *out) {
    //Skips anything like spaces, tabs, etc
    while (isspace((unsigned char)*line)){
        line++;
    }
    errno = 0;
    char *endptr = NULL;
    long v = strtol(line, &endptr, 10);

    //This would mean there were no digits
    if (line == endptr){
        return 0;
    }
    //Got this part from: https://learn.microsoft.com/en-us/cpp/c-language/cpp-integer-limits?view=msvc-170 
    if (errno != 0 || v < 0 || v > INT_MAX){ 
        return 0;
    }

    //Storing value
    *out = (int)v;
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2){
        fprintf(stderr, "The usage of C_SIZE is... %s \n", argv[0]); 
        return 1; 
    }
    int C_SIZE = atoi(argv[1]);
    if (C_SIZE <= 0){ 
        fprintf(stderr, "ERROR!!! C_SIZE must be > 0\n");
        return 1; 
    }

    ref_page *cache = malloc(sizeof(ref_page) * (size_t)C_SIZE);
    if (!cache){
        perror("MALLOC ERROR!!!!!!"); 
        return 1; 
    }
    for (int i = 0; i < C_SIZE; i++){
        cache[i].pageno = -1; //it's empty!
    }

    int placeInArray = 0;
    char pageCache[100];

    //Read the request lines
    while (fgets(pageCache, sizeof(pageCache), stdin)) {
        int page_num;

        //Skipping the invalid lines
        if (!parse_page_num(pageCache, &page_num)){
            continue;
        }

        int hit = 0;
        for (int i = 0; i < C_SIZE; i++) {
            //If it's a hit (yay!!!)
            if (cache[i].pageno == page_num){ 
                hit = 1; 
                break; 
            }
        }
        //If it's a miss (boo!!!) Adds to fault count :(
        if (!hit) {
            printf("%d\n", page_num);
            cache[placeInArray].pageno = page_num;
            placeInArray = (placeInArray + 1) % C_SIZE;
        }
    }

    //Freeing memory
    free(cache);
    return 0;
}
