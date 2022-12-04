def main():
    input = get_input()
    ret1, ret2 = 0, 0
    for line in input:
        solve = solver(line)
        ret1 += solve[0]
        ret2 += solve[1]
    
    print(ret1)
    print(ret2)

def solver(line: str) -> int|int:
    ret1, ret2 = 0, 0
    assign = line.split(',')
    a1 = [int(x) for x in assign[0].split('-')]
    a2 = [int(x) for x in assign[1].split('-')]
    
    
    if (a2[0] <= a1[0] and a1[1] <= a2[1]) \
        or (a1[0] <= a2[0] and a2[1] <= a1[1]):
            ret1 = 1
    
    if a2[0] <= a1[0] <= a2[1] or a2[0] <= a1[1] <= a2[1] \
        or a1[0] <= a2[0] <= a1[1] or a1[0] <= a2[1] <= a1[1]:
            ret2 += 1

    return ret1, ret2


def get_input():
    input = []
    with open("input.txt", encoding='utf-8') as file:
        while (line := file.readline().rstrip()):
            input.append(line)
    
    return input

if __name__ == "__main__":
    main()

