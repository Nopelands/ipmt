 #!/bin/bash 

count=3

logfile="result_decompress_text_size.txt"
one="english.1MB.lz77"
five="english.5MB.lz77"
ten="english.10MB.lz77"
fifty="english.50MB.lz77"
hundred="english.100MB.lz77"
one_out="english.1MB.unlz77"
five_out="english.5MB.unlz77"
ten_out="english.10MB.unlz77"
fifty_out="english.50MB.unlz77"
hundred_out="english.100MB.unlz77"
one_gz="english.1MB.gz"
five_gz="english.5MB.gz"
ten_gz="english.10MB.gz"
fifty_gz="english.50MB.gz"
hundred_gz="english.100MB.gz"

echo "lz77_1_1 1 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a ./ipmt unzip $one
    rm $one_out
done

echo "lz77_1_1 5 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a ./ipmt unzip $five
    rm $five_out
done

echo "lz77_1_1 10 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a ./ipmt unzip $ten
    rm $ten_out
done

echo "lz77_1_1 50 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a ./ipmt unzip $fifty
    rm $fifty_out
done

echo "lz77_1_1 100 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a ./ipmt unzip $hundred
    rm $hundred_out
done

echo "gzip 1 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a gzip -c -d $one_gz
done

echo "gzip 5 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a gzip -c -d $five_gz
done

echo "gzip 10 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a gzip -c -d $ten_gz
done

echo "gzip 50 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a gzip -c -d $fifty_gz
done

echo "gzip 100 (${count} results per text size)" | tee -a $logfile
for j in $(seq $count); do
    /usr/bin/time -f %e -o $logfile -a gzip -c -d $hundred
done
