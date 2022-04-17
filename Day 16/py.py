data1 = '''820D4100A1000085C6E8331F8401D8E106E1680021708630C50200A3BC01495B99CF6852726A88014DC9DBB30798409BBDF5A4D97F5326F050C02F9D2A971D9B539E0C93323004B4012960E9A5B98600005DA7F11AFBB55D96AFFBE1E20041A64A24D80C01E9D298AF0E22A98027800BD4EE3782C91399FA92901936E0060016B82007B0143C2005280146005300F7840385380146006900A72802469007B0001961801E60053002B2400564FFCE25FEFE40266CA79128037500042626C578CE00085C718BD1F08023396BA46001BF3C870C58039587F3DE52929DFD9F07C9731CC601D803779CCC882767E668DB255D154F553C804A0A00DD40010B87D0D6378002191BE11C6A914F1007C8010F8B1122239803B04A0946630062234308D44016CCEEA449600AC9844A733D3C700627EA391EE76F9B4B5DA649480357D005E622493112292D6F1DF60665EDADD212CF8E1003C29193E4E21C9CF507B910991E5A171D50092621B279D96F572A94911C1D200FA68024596EFA517696EFA51729C9FB6C64019250034F3F69DD165A8E33F7F919802FE009880331F215C4A1007A20C668712B685900804ABC00D50401C89715A3B00021516E164409CE39380272B0E14CB1D9004632E75C00834DB64DB4980292D3918D0034F3D90C958EECD8400414A11900403307534B524093EBCA00BCCD1B26AA52000FB4B6C62771CDF668E200CC20949D8AE2790051133B2ED005E2CC953FE1C3004EC0139ED46DBB9AC9C2655038C01399D59A3801F79EADAD878969D8318008491375003A324C5A59C7D68402E9B65994391A6BCC73A5F2FEABD8804322D90B25F3F4088F33E96D74C0139CF6006C0159BEF8EA6FBE3A9CEC337B859802B2AC9A0084C9DCC9ECD67DD793004E669FA2DE006EC00085C558C5134001088E308A20
'''.splitlines()
data=data1[0].splitlines()

s = bin(int(data[0], 16))[2:]
n = len(s)
if n % 4 != 0:
    s = '0' * (4 - n % 4) + s
n = len(s)
res = 0
c = 0

while c < n and '1' in s[c:]:
    v = int(s[c: c + 3], 2)
    res += v
    c += 3
    t = int(s[c: c + 3], 2)
    c += 3

    if t == 4:
        num = ''
        while s[c] == '1':
            num += s[c + 1: c + 5]
            c += 5
        num += s[c + 1: c + 5]
        c += 5
        num = int(num, 2)
    else:
        l = int(s[c], 2)
        c += 1
        if l == 0:
            num = int(s[c: c + 15], 2)
            c += 15
        else:
            num = int(s[c: c + 11], 2)
            c += 11

print(res)

from functools import reduce

funcDict = {
    0: sum,
    1: lambda a: reduce(lambda x, y: x * y, a),
    2: min,
    3: max,
    5: lambda a: int(a[0] > a[1]),
    6: lambda a: int(a[0] < a[1]),
    7: lambda a: int(a[0] == a[1])
}

string = ""

def evaluate(u):
    global string
    if packets[u][1] == 4:
        return packets[u][2]

    res = []
    for v in graph[u]:
        res.append(evaluate(v))
    string += str(packets[u][1]) + " "
    return funcDict[packets[u][1]](res)

s = bin(int(data[0], 16))[2:]
for i in data[0]:
    if i != '0':
        break
    s = '0' * 4 + s
n = len(s)
if n % 4 != 0:
    s = '0' * (4 - n % 4) + s
n = len(s)
c = 0
packets = []

while c < n and '1' in s[c:]:
    v = int(s[c: c + 3], 2)
    c += 3
    t = int(s[c: c + 3], 2)
    c += 3

    if t == 4:
        num = ''
        while s[c] == '1':
            num += s[c + 1: c + 5]
            c += 5
        num += s[c + 1: c + 5]
        c += 5
        num = int(num, 2)

        packets.append([v, t, num, c])
    else:
        l = int(s[c], 2)
        c += 1
        if l == 0:
            num = int(s[c: c + 15], 2)
            c += 15
        else:
            num = int(s[c: c + 11], 2)
            c += 11

        packets.append([v, t, l, num, c])

stack = []
graph = [[] for _ in range(len(packets))]

for i, u in enumerate(packets):
    if len(stack) > 0:
        p = stack[-1]
        graph[p].append(i)
        packets[p][3] -= 1
        if packets[p][3] == 0:
            stack.pop()

    while len(stack) > 0:
        p = stack[-1]
        if packets[p][2] == 0 and packets[p][3] <= u[-1] - packets[p][-1]:
            stack.pop()
        else:
            break

    if u[1] != 4:
        stack.append(i)

print(evaluate(0))
print(string)
