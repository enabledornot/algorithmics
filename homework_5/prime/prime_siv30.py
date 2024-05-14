import random
magic_array = [1,7,11,13,17,19,23,29]
class special_set:
    def __init__(self,starting_value):
        if isinstance(starting_value,tuple):
            self.byte = starting_value[0]
            self.bit = starting_value[1]
            return
        self.byte = int(starting_value / 30)
        if starting_value % 30 in magic_array:
            self.bit = magic_array.index(starting_value % 30)
        else:
            raise ValueError("starting value does not exist within the set")
    def __add__(self,other):
        if isinstance(other, special_set):
            other = 30*other.byte + magic_array[other.bit]
        if isinstance(other, int):
            new_offset = magic_array[self.bit] + other
            while new_offset % 30 not in magic_array:
                new_offset += other
            return special_set((self.byte + int(new_offset / 30), magic_array.index(new_offset % 30)))
        else:
            raise TypeError("unsupported addition type {}".format(type(other)))
    def add_lookup(self,other):
        if isinstance(other, special_set):
            looked_up = lookup[self.bit][other.bit]
            print(looked_up)

            byte_offset = other.byte * looked_up[2] + looked_up[0]
            new_bit = looked_up[1]
            return special_set((self.byte + byte_offset, new_bit))
        elif isinstance(other, int):
            mod30 = other % 30
            div30 = int(other / 30)
            looked_up = lookup[self.bit][mod30]
            
            byte_offset = div30 * looked_up[2] + looked_up[0]
            new_bit = looked_up[1]
            return special_set((self.byte + byte_offset, new_bit))
        else:
            raise TypeError("unsupported addition type {}".format(type(other)))
    def get_add_offset(self,other):
        if isinstance(other, special_set):
            other = 30*other.byte + magic_array[other.bit]
        if isinstance(other, int):
            new_offset = magic_array[self.bit] + other
            count = 1
            while new_offset % 30 not in magic_array:
                new_offset += other
                count += 1
            return (int(new_offset / 30), magic_array.index(new_offset % 30),count)
        else:
            raise TypeError("unsupported addition type {}".format(type(other)))
    def __str__(self):
        return str(30 * self.byte + magic_array[self.bit])
    def __eq__(self,other):
        if isinstance(other,special_set):
            return self.byte == other.byte and self.bit == other.bit
def generate_lookup_table():
    lookup_table = []
    for i in range(8):
        lookup_table.append([])
        for ii in range(8):
            ss = special_set((0,i))
            lookup_table[-1].append(ss.get_add_offset(special_set((0,ii))))
    return lookup_table
lookup = generate_lookup_table()

def rand_ss(uppr):
    while True:
        try:
            return special_set(random.randint(1,uppr))
        except:
            pass
import json
with open("output.json","w") as f:
    json.dump(lookup,f,indent=4)
# for _ in range(10000):
#     ss = rand_ss(1000)
#     ss2 = rand_ss(1000)
#     if (ss+ss2 != ss.add_lookup(ss2)):
#         print("{}-{}".format(ss,ss2))
#         print("{}-{}".format(ss+ss2,ss.add_lookup(ss2)))
#         print("")

ss = special_set(7)
ss2 = special_set(7)
# ss2 = special_set(7)
print(ss+ss2)
print(ss.add_lookup(ss2))