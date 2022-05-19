from decimal import *
import re
pattern = re.compile("([0-9]+)(,[0-9]+)?(M|K)$")

def is_decimal(s):
    try:
        Decimal(s)
        return True
    except:
        return False
    
def is_size(s):
    if pattern.match(s):
        return True
    else:
        return False

def average(file):
    f = open(file, "r")
    dest = open("average_result_index_text_size.txt", "x")
    count = 1
    sum = 0
    size = ""
    try:
        for i in f:
            if is_decimal(i):
                num = Decimal(i)
                if count == 3:
                    sum = sum + num
                    avg = (sum / 3).quantize(Decimal('.01'))
                    sum = 0
                    count = 1
                    dest.write(str(avg) + "\n")
                else:
                    sum = sum + num
                    count += 1
            elif is_size(i):
                size = i
            else:
                dest.write(size)
                aux = i.split(" ")
                aux = aux[0] + "\n"
                dest.write(aux)
    finally:
        f.close()
        dest.close()

def main():
    average("result_index_text_size.txt")

if __name__ == "__main__":
    main()
