//Name: Divya Bengali
//Date: November 21st, 2025 
//Title: Lab7 – Step 3
//Description: This program reads the output using a LRU alogrithm.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

typedef struct {
    int pageno;
    long last_used;
} ref_page;

static int parse_page_num(const char *line, int *out) {
    //Skips anything like spaces, tabs, etc
    while (isspace((unsigned char)*line)){
        line++;
    }
    errno = 0;
    char *endptr = NULL;
    long v = strtol(line, &endptr, 10);
    if (line == endptr){
        return 0; //in case there were no digits therefore not a page number
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
        fprintf(stderr, "Usage of C_SIZE is... %s \n", argv[0]); 
        return 1; 
    }
    int C_SIZE = atoi(argv[1]);
    if (C_SIZE <= 0){
        fprintf(stderr, "HELLO FUTURE ME: ERROR!!! CACHE SIZES NEEDS TO BE GREATER THAN 1\n"); 
        return 1; 
    }

    //Allocate memory for cache (fun)
    ref_page *cache = malloc(sizeof(ref_page) * (size_t)C_SIZE);
    if (!cache){
        perror("CODE MALLOC, I REPEAT, CODE MALLOC (I like to have fun with my errors...)'"); 
        return 1; 
    }

    //Initialise!!!!
    for (int i = 0; i < C_SIZE; i++) {
        cache[i].pageno = -1;
        cache[i].last_used = -1;
    }
    
    //This is where it changes (in comparison to FIFO, lol). It's the time counter!
    long t = 0;
    char pageCache[100];

    while (fgets(pageCache, sizeof(pageCache), stdin)) {
        int page_num;
        if (!parse_page_num(pageCache, &page_num)){
            continue;
        }
        t++;

        //See if it's a "hit" and already in the freame
        int hit_index = -1;
        for (int i = 0; i < C_SIZE; i++) {
            if (cache[i].pageno == page_num){
                hit_index = i;
                break;
            }
        }

        if (hit_index != -1) {
            cache[hit_index].last_used = t;
            continue;
        }

        printf("%d\n", page_num);

        //Emptry frame should be used first tho...
        int empty = -1;
        for (int i = 0; i < C_SIZE; i++) {
            if (cache[i].pageno == -1){
                empty = i; 
                break; 
            }
        }

        if (empty != -1) {
            cache[empty].pageno = page_num;
            cache[empty].last_used = t;
        } else {
            int victim = 0;
            for (int i = 1; i < C_SIZE; i++) {
                if (cache[i].last_used < cache[victim].last_used){
                    victim = i;
                }
            }
            cache[victim].pageno = page_num;
            cache[victim].last_used = t;
        }
    }
    //Free memory
    free(cache);
    return 0;
}
