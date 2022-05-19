#!/bin/bash 

count=3

logfile="result_search_text_size.txt"
one="english.1MB.idx"
five="english.5MB.idx"
ten="english.10MB.idx"
fifty="english.50MB.idx"
hundred="english.100MB.idx"

echo "search 1 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a ./ipmt search -c test $one
done

echo "search 5 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a ./ipmt search -c test $five
done

echo "search 10 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a ./ipmt search -c test $ten
done

echo "search 50 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a ./ipmt search -c test $fifty
done

echo "search 100 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a ./ipmt search -c test $hundred
done 



echo "grep 1 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a --quiet grep -c test $one
done

echo "grep 5 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a --quiet grep -c test $five
done

echo "grep 10 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a --quiet grep -c test $ten
done

echo "grep 50 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a --quiet grep -c test $fifty
done

echo "grep 100 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a --quiet grep -c test $hundred
done 
