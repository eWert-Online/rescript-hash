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

  let va = ref(length * 8);
  for (i in 0 to 7) {
    Bytes.set(bytes, i + (size^ - 8), Char.chr(va^ land 0xFF));
    va := va^ lsr 8;
  };

  bytes;
};