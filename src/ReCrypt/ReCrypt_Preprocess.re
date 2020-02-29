/**
  * Preprocessing [§5]
  */
module Sha256 = {
  let pad = (msgBytes: Bytes.t) => {
    let size = ref(Bytes.length(msgBytes) + 8 + 1);
    while (size^ mod 64 != 0) {
      size := size^ + 1;
    };

    let length = Bytes.length(msgBytes);

    let bytes =
      Bytes.init(size^, index => {
        switch (index) {
        | i when i < length => Bytes.get(msgBytes, i)
        | i when i == length => Char.chr(0x80)
        | _ => Char.chr(0x00)
        }
      });

    ReCrypt_Utils.toBytes(length * 8, bytes);
  };
};

module Sha384_512 = {
  let pad = (msgBytes: Bytes.t) => {
    let size = ref(Bytes.length(msgBytes) + 16 + 1);
    while (size^ mod 128 != 0) {
      size := size^ + 1;
    };

    let length = Bytes.length(msgBytes);

    let bytes =
      Bytes.init(size^, index => {
        switch (index) {
        | i when i < length => Bytes.get(msgBytes, i)
        | i when i == length => Char.chr(0x80)
        | _ => Char.chr(0x00)
        }
      });

    ReCrypt_Utils.toBytes(length * 8, bytes);
  };
};