'''
E->I
E->(E+E)
E->(E-E)
E->(E*E)
E->(E/E)
'''
# l(n) = l(n-1) + 1/2

import random

def E(vars):
    if random.randint(0, 1) == 0:
        return [random.choice(list(range(-20, 20)) + vars)]
    else:
        return ['('] + E(vars) + [random.choice(['+', '-', '*', '/'])] + E(vars) + [')']
    
# print(E())

def E_iter(vars):
    ret = ['E']
    e_count = 1
    while(e_count):
        n = len(ret)
        i = 0
        while(i < n):
            if(ret[i] == 'E'):
                if random.randint(1, 100) > 60:
                    ret[i] = random.randint(1, 100)
                    e_count -= 1
                else:
                    ret[i:i+1] = ['(','E', random.choice(['+', '-', '*', '/']), 'E',')']
                    e_count += 1
                    i+=4
                    n+=4
            i += 1
    return ret

# print(E_iter())

def random_var():
    return ''.join([chr(random.randint(ord('a'), ord('z'))) for _ in range(random.randint(1, 2))])

def generate(n):
    vars = []
    ret = []
    for _ in range(n-1):
        if len(vars) == 0 or random.randint(1, 100) > 70:
            while True:
                var = random_var()
                if var not in vars:
                    break
            ret.append(str(var) +' := '+' '.join([str(e) for e in E(vars)]))
            vars.append(var)
        else:
            var = random.choice(vars)
            ret.append('del := '+ str(var))
            vars.remove(var)
    ret.append('ret := '+ ' '.join([str(e) for e in E(vars)]))
    return ret

s = generate(100)

with open('./bin/a.txt', 'w') as f:
    f.write('\n\n'.join(s))

def infix_to_prefix(s):
    s = s.split(' ')
    s.remove(':=')
    s.reverse()
    stack = []
    ret = []
    for e in s:
        if e in ['+', '-', '*', '/']:
            stack.append(e)
        elif e == '(':
            ret.append(stack.pop())
        elif e == ')':
            pass
        else:
            ret.append(e)
    return ret

dic = {}
h = []
a = []

def check_int(s):
    if s[0] == '-':
        return s[1:].isdigit()
    return s.isdigit()

for x in s:
    k = infix_to_prefix(x)
    if(k[1] == 'del'):
        a.append('DEL = mem['+ str(dic[k[0]]) + ']')
        h.append(dic[k[0]])
        dic.pop(k[0])
        a.append('')
        continue
    for y in k[:-1]:
        if(check_int(y)):
            a.append('PUSH '+y)
        elif(y == '+'):
            a.append('ADD')
        elif(y == '-'):
            a.append('SUB')
        elif(y == '*'):
            a.append('MUL')
        elif(y == '/'):
            a.append('DIV')
        else:
            a.append('PUSH mem['+ str(dic[y]) + ']')
    if(k[-1] == 'ret'):
        a.append('RET = POP')
    else:
        if len(h) == 0:
            aa = len(dic)
        else:
            aa = min(h)
            h.remove(aa)
        dic[k[-1]] = aa
        a.append('mem['+ str(aa) + '] = POP')
    a.append('')

with open('./bin/b.txt', 'w') as f:
    f.write('\n'.join(a))
