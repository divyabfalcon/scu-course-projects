#Name: Divya Bengali
#Date: November 21st, 2025 
#Title: Lab7 – Step 3
#Description: This program reads the output using a second chance page replacement.



#!/bin/bash
make;
echo "----------FIFO----------"
cat testInput.txt | ./step3_fifo 10
echo "----------End FIFO----------"
echo
echo "----------LRU----------"
cat testInput.txt | ./step3_lru 10
echo "----------End LRU----------"
echo
echo "----------Second Chance----------"
cat testInput.txt | ./step3_secondChance 10
echo "----------End Second Chance----------"
echo "FIFO 10K Test with cache size = 10, 50, 100, 250, 500"
cat accesses.txt | ./step3_fifo 10 | wc -l
cat accesses.txt | ./step3_fifo 50 | wc -l
cat accesses.txt | ./step3_fifo 100 | wc -l
cat accesses.txt | ./step3_fifo 250 | wc -l
cat accesses.txt | ./step3_fifo 500 | wc -l
echo
echo "LRU 10K Test with cache size = 10, 50, 100, 250, 500"
cat accesses.txt | ./step3_lru 10 | wc -l
cat accesses.txt | ./step3_lru 50 | wc -l
cat accesses.txt | ./step3_lru 100 | wc -l
cat accesses.txt | ./step3_lru 250 | wc -l
cat accesses.txt | ./step3_lru 500 | wc -l
echo
echo "Second Chance 10K Test with cache size = 10, 50, 100, 250, 500"
cat accesses.txt | ./step3_secondChance 10 | wc -l
cat accesses.txt | ./step3_secondChance 50 | wc -l
cat accesses.txt | ./step3_secondChance 100 | wc -l
cat accesses.txt | ./step3_secondChance 250 | wc -l
cat accesses.txt | ./step3_secondChance 500 | wc -l
echo
make clean;
echo