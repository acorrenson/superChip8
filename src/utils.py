
f = open("ASM_BRIX.txt")
f2 = open("ASM.txt", "w")

content = f.read()
lines = content.split("\n")
s = ""
i = 512

for l in lines:
    s += str(i) + " : " + l + "\n"
    i += 1

f2.write(s)

