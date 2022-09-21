def get_inputs():
    n, m = map(int,input().strip().split())
    h = list(map(int,input().strip().split()))
    a = []
    b = []
    c = []
    for _ in range(m):
        A,B,C = map(int,input().strip().split())
        a.append(A)
        b.append(B)
        c.append(C)
    return n,m,h,a,b,c

def print_answer_and_exit(answer):
    print(answer)
    exit(0)
