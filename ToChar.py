str = "2b7e151628aed2a6abf7158809cf4f3c"

e = True
cnt = 0
sCnt = 0

ret = ""

for i in str:
    if sCnt == 2368:
        break
    
    if e:
        ret += ", "
        if cnt == 32:
            cnt = 0
            ret += "\n"
        ret += "0x"
        
    cnt += 1
    sCnt += 1
    ret += i
    e = not e

print(ret)
        
