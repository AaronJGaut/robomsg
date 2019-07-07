import sys
from pprint import pprint

from MyMessage import MyMessage

m = MyMessage()
m.asdf = 5
m.qwer = "qwer"
m.myfoo.foo = 10
m.myfoo.pi = 3.14159
m.myfoo.i = "hi"
m.mybar.is_valid = True

print("m")
pprint(m.to_dict())

buffer = m.serialize()

for b in buffer:
    sys.stdout.write("%02x " % b)
sys.stdout.write("\n")
sys.stdout.flush()

m2 = MyMessage.deserialize(buffer)

print("m2")
pprint(m2.to_dict())
