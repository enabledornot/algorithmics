import re
# import Math
def decodeAll(lines):
    lookupDict = {}
    for line in lines[:-1]:
        # pattern = r"\[(\d+)\]\s*([a-zA-Z]?)\s*-\s*\d+\s*-\s*([01]+)"
        # matches = re.findall(pattern, line)
        carcodes = int(line[1:4])
        carencode = line[6:38].replace(" ","")
        lookupDict[carencode] = carcodes
    return lookupDict
with open("output.txt","r") as f:
    output = f.read().split("\n")

lookupIndex = output.index("printing lookup") + 1
encodingIndex = output.index("printing encoding") + 1
encoding = output[lookupIndex:encodingIndex]
decoding = decodeAll(encoding)
print(decoding)
# for line in output[encodingIndex:-2]:
#     supposed_char = line[0]
#     encoded_data_unmasked = line[4:36]
#     data_start = int(line[39:42])
#     data_end = int(line[43:46])
#     try:
#         decoded = decoding[encoded_data_unmasked[data_start:data_end]]
#         print(decoded)
#     except:
#         print(supposed_char + "?")
#         print(encoded_data_unmasked)
#         print(data_start)
#         print(data_end)
cbuff = ""
decode_buffer = []
cnt = 0
for c in output[encodingIndex]:
    if c == " ":
        cbuff += '_'
        continue
    cbuff += c
    if cbuff.replace("_","") in decoding:
        decoded = decoding[cbuff.replace("_","")]
        if decoded == 256:
            break
        else:
            decoded = chr(decoded)
        print(decoded,end="")
        decode_buffer.append((decoded,cbuff))
        cbuff = ""
    cnt += 1
print("")
for v in decode_buffer:
    if len(v) != 0:
        print(v[0] + " " + v[1],end="")
    print('')