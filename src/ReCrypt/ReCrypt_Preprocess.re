/**
  * Preprocessing [§5]
  */
module Sha512 = {
  let pad = (msgBytes: Bytes.t) => {
    let size = ref(Bytes.length(msgBytes) + 17);
    while (size^ mod 128 != 0) {
      size := size^ + 1;
    };

    Bytes.init(
      size^,
      index => {
        let length = Bytes.length(msgBytes);
        switch (index) {
        | i when i < length => Bytes.get(msgBytes, i)
        | i when i == length => Char.chr(0x80)
        | i when i == size^ - 1 => (length * 8)->char_of_int
        | _ => Char.chr(0x00)
        };
      },
    );
  };
};