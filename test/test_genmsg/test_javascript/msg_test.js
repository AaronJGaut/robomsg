// Polyfill for UTF-8 encoding features in node
encoding = require('./encoding');
TextEncoder = encoding.TextEncoder;
TextDecoder = encoding.TextDecoder;

MyMessage = require("./artifacts/MyMessage");

m = new MyMessage.MyMessage();
m.asdf = 5
m.qwer = "qwer"
m.myfoo.foo = 10
m.myfoo.pi = 3.14159
m.myfoo.i = "hi"
m.mybar.is_valid = true;

console.log(m);

const buffer = m.serialize();
const view = new Uint8Array(buffer);

hex_bytes = [];
for (let i in view)
{
    let b_str = view[i].toString(16);
    if (b_str.length < 2)
    {
        b_str = "0" + b_str;
    }
    hex_bytes.push(b_str);
}
console.log(hex_bytes.join(" "));

m2 = MyMessage.MyMessage.deserialize(buffer);

console.log(m2);

