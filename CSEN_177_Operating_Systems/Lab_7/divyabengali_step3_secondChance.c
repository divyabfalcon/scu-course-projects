//Name: Divya Bengali
//Date: November 21st, 2025 
//Title: Lab7 – Step 3
//Description: This program reads the output using a second chance page replacement.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

typedef struct{
    int pageno; 
} ref_page;
//Basically all the same comments as the last two here...
static int parse_page_num(const char *line, int *out) {
    while (isspace((unsigned char)*line)){
        line++;
    }
    errno = 0;
    char *endptr = NULL;
    long v = strtol(line, &endptr, 10);
    if (line == endptr){
        return 0;
    }

    //Got this part from: https://learn.microsoft.com/en-us/cpp/c-language/cpp-integer-limits?view=msvc-170 
    if (errno != 0 || v < 0 || v > INT_MAX){
        return 0;
    }
    *out = (int)v;
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2){
        fprintf(stderr, "Usage is... %s \n", argv[0]); 
        return 1; 
    }
    int C_SIZE = atoi(argv[1]);
    if (C_SIZE <= 0){
        fprintf(stderr, "We're met to be above ground yet you give me a number under...why? CACHE SIZE MUST BE EQUAL TO OR GREATER THAN 0!!\n"); 
        return 1; 
    }

    ref_page *cache = malloc(sizeof(ref_page) * (size_t)C_SIZE);
    unsigned char *ref = malloc((size_t)C_SIZE);
    if (!cache || !ref){
        perror("Give me an 'M', give me an 'A', give me an 'LLOC'...what's that spell? MALLOC ERROR!!!!!! (A spin on Descendants DCOOM)");
        free(cache);
        free(ref);
        return 1; 
}

    for (int i = 0; i < C_SIZE; i++){
        cache[i].pageno = -1;
        ref[i] = 0;
    }

    int placeInArray = 0;
    char pageCache[100];

    while (fgets(pageCache, sizeof(pageCache), stdin)) {
        int page_num;
        if (!parse_page_num(pageCache, &page_num)){
            continue;
        }

        int hit = 0;
        for (int i = 0; i < C_SIZE; i++) {
            //Second chance!! :)))
            if (cache[i].pageno == page_num) {
                ref[i] = 1;   
                hit = 1;
                break;
            }
        }
        if (hit){
            continue;
        }

        // fault :((((
        printf("%d\n", page_num);

        while (1) {
            //Gotta use those empty frames first!
            if (cache[placeInArray].pageno == -1) {
                cache[placeInArray].pageno = page_num;
                ref[placeInArray] = 1;
                placeInArray = (placeInArray + 1) % C_SIZE;
                break;
            }
            if (ref[placeInArray] == 0) {
                cache[placeInArray].pageno = page_num;
                ref[placeInArray] = 1;
                placeInArray = (placeInArray + 1) % C_SIZE;
                break;
            }
            ref[placeInArray] = 0;
            placeInArray = (placeInArray + 1) % C_SIZE;
        }
    }

    free(cache);
    free(ref);
    return 0;
}
