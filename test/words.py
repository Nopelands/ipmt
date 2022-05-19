from random import *


#  https://github.com/dwyl/english-words/blob/master/words_alpha.txt
#  palavras acima de tamanho 25 n tem 3 exemplos e foram geradas dinamicamente

def generate():
    file = open("words_alpha.txt", "r")
    words = []
    for i in range(0, 100):
        words.append([])
    for lines in file:
        line = lines.split('\n')
        for wds in line:
            if len(wds) <= 100 and wds != "":
                words[len(wds) - 1].append(wds)
    for i in words:
        shuffle(i)
    marker = False
    for i in range(0, len(words)):
        if len(words[i]) < 3:
            if not marker:
                marker = True
                print(i)
            for j in range(0, 3 - len(words[i])):
                shuffle(words[int(i / 2)])
                shuffle(words[int((i - 1) / 2)])
                if (i + 1) % 2 == 0:
                    if j == 0:
                        words[i].append(words[int(i / 2)][0] + words[int(i / 2)][1])
                    elif j == 1:
                        words[i].append(words[int(i / 2)][1] + words[int(i / 2)][2])
                    else:
                        words[i].append(words[int(i / 2)][0] + words[int(i / 2)][2])
                else:
                    if j == 0:
                        words[i].append(words[int((i - 1) / 2)][0] + words[int(((i - 1) / 2)) + 1][1])
                    elif j == 1:
                        words[i].append(words[int((i - 1) / 2)][1] + words[int(((i - 1) / 2)) + 1][2])
                    else:
                        words[i].append(words[int((i - 1) / 2)][0] + words[int(((i - 1) / 2)) + 1][2])

    output = open("words.txt", "a")
    for i in words:
        shuffle(i)
        output.write(i[0] + "\n")
        output.write(i[1] + "\n")
        output.write(i[2] + "\n")
    output.close()
    file.close()


if __name__ == '__main__':
    generate()
