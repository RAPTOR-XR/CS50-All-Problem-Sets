import csv
import sys

if len(sys.argv) != 3:
    print("Usage Error")
    exit(1)


def main():
    csv_plot = sys.argv[1]
    with open(csv_plot) as file:
        file_reader = csv.reader(file)
        a_seq = next(file_reader)[1:]
            
        txt_plot = sys.argv[2]
        with open(txt_plot) as txt_file:
            strng = txt_file.read()
            act = [count(strng, sequ) for sequ in a_seq]
        match(file_reader, act)
            
            
def count(strng, sub):
    a = [0] * len(strng)
    for i in range(len(strng) - len(sub), -1, -1):
        if strng[i: i + len(sub)] == sub:
            if i + len(sub) > len(strng) - 1:
                a[i] = 1
            else:
                a[i] = 1 + a[i + len(sub)]
    return max(a)
            
            
def match(file_reader, act):
    for line in file_reader:
        peep = line[0]
        val = [int(j) for j in line[1:]]
        if val == act:
            print(peep)
            return
    print("No match")
            
            
if __name__ == "__main__":
    main()