import re
# import Math
def decodeAll(lines):
    decoded = []
    for line in lines:
        pattern = r"\[(\d+)\]\s*([a-zA-Z]?)\s*-\s*\d+\s*-\s*([01]+)"
        matches = re.findall(pattern, line)
        if len(matches) > 0:
            decoded.append(matches[0])
    lookupDict = {}
    for decode in decoded:
        lookupDict[decode[2]] = chr(int(decode[0]))
    return lookupDict
with open("output.txt","r") as f:
    output = f.read().split("\n")

lookupIndex = output.index("printing lookup") + 1
encodingIndex = output.index("printing encoding") + 1
encoding = output[lookupIndex:encodingIndex]
decoding = decodeAll(encoding)
cbuff = ""
decode_buffer = []
cnt = 0
for c in output[encodingIndex]:
    if c == " ":
        cbuff += '_'
        continue
    cbuff += c
    # if cnt % 32 == 31:
    #     decode_buffer.append(())
    if cbuff.replace("_","") in decoding:
        print(decoding[cbuff.replace("_","")],end="")
        decode_buffer.append((decoding[cbuff.replace("_","")],cbuff))
        cbuff = ""
    cnt += 1
print("")
for v in decode_buffer:
    if len(v) != 0:
        print(v[0] + " " + v[1],end="")
    print('')