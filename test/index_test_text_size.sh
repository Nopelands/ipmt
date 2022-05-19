#!/bin/bash 

count=3

logfile="result_index_text_size.txt"
one="english.1MB"
five="english.5MB"
ten="english.10MB"
fifty="english.50MB"
hundred="english.100MB"
one_out="english.1MB.idx"
five_out="english.5MB.idx"
ten_out="english.10MB.idx"
fifty_out="english.50MB.idx"
hundred_out="english.100MB.idx"

echo "index 1 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a ./ipmt index $one
    ls -lh $one_out | awk '{print $5}' | tee -a $logfile
    rm $one_out
done

echo "index 5 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a ./ipmt index $five
    ls -lh $five_out | awk '{print $5}' | tee -a $logfile
    rm $five_out
done

echo "index 10 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a ./ipmt index $ten
    ls -lh $ten_out | awk '{print $5}' | tee -a $logfile
    rm $ten_out
done

echo "index 50 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a ./ipmt index $fifty
    ls -lh $fifty_out | awk '{print $5}' | tee -a $logfile
    rm $fifty_out
done

echo "index 100 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a ./ipmt index $hundred
    ls -lh $hundred_out | awk '{print $5}' | tee -a $logfile
    rm $hundred_out
done 
