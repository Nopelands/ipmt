 #!/bin/bash 

words=300

logfile="result_search_patt_size.txt"
words_source="words.txt"
text="english.100MB"

echo "search 100 (${count} results per pattern size)" | tee -a $logfile
pattern=$(sed -n '1,1p' $words_source)
aux_count=1
for i in $(seq $words); do
    /usr/bin/time -f %e -o $logfile -a ./ipmt search -c $pattern $text
    aux_count=$((aux_count+1))
    pattern=$(sed -n "${aux_count},${aux_count}p" $words_source)
done

echo "grep 100 (${count} results per pattern size)" | tee -a $logfile
pattern=$(sed -n '1,1p' $words_source)
aux_count=1
for i in $(seq $words); do
    /usr/bin/time --quiet -f %e -o $logfile -a grep -c $pattern $text
    aux_count=$((aux_count+1))
    pattern=$(sed -n "${aux_count},${aux_count}p" $words_source)
done
