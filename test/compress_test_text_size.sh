#!/bin/bash 

count=3

logfile="result_compress_text_size.txt"
one="english.1MB"
five="english.5MB"
ten="english.10MB"
fifty="english.50MB"
hundred="english.100MB"
one_out="english.1MB.lz77"
five_out="english.5MB.lz77"
ten_out="english.10MB.lz77"
fifty_out="english.50MB.lz77"
hundred_out="english.100MB.lz77"
one_gz="english.1MB.gz"
five_gz="english.5MB.gz"
ten_gz="english.10MB.gz"
fifty_gz="english.50MB.gz"
hundred_gz="english.100MB.gz"

echo "lz77_1_1 1 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a ./ipmt zip $one
    ls -lh $one_out | awk '{print $5}' | tee -a $logfile
    rm $one_out
done

echo "lz77_1_1 5 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a ./ipmt zip $five
    ls -lh $five_out | awk '{print $5}' | tee -a $logfile
    rm $five_out
done

echo "lz77_1_1 10 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a ./ipmt zip $ten
    ls -lh $ten_out | awk '{print $5}' | tee -a $logfile
    rm $ten_out
done

echo "lz77_1_1 50 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a ./ipmt zip $fifty
    ls -lh $fifty_out | awk '{print $5}' | tee -a $logfile
    rm $fifty_out
done

echo "lz77_1_1 100 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a ./ipmt zip $hundred
    ls -lh $hundred_out | awk '{print $5}' | tee -a $logfile
    rm $hundred_out
done

echo "gzip 1 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a gzip -k $one
    ls -lh $one_gz | awk '{print $5}' | tee -a $logfile
    rm $one_gz
done

echo "gzip 5 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a gzip -k $five
    ls -lh $five_gz | awk '{print $5}' | tee -a $logfile
    rm $five_gz
done

echo "gzip 10 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a gzip -k $ten
    ls -lh $ten_gz | awk '{print $5}' | tee -a $logfile
    rm $ten_gz
done

echo "gzip 50 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a gzip -k $fifty
    ls -lh $fifty_gz | awk '{print $5}' | tee -a $logfile
    rm $fifty_gz
done

echo "gzip 100 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a gzip -k $hundred
    ls -lh $hundred_gz | awk '{print $5}' | tee -a $logfile
    rm $hundred_gz
done
