let append = (hash, value, offset) => {
  for (j in 0 to 3) {
    Bytes.set(hash, j + offset, (value lsr (j * 8) land 0xFF)->Char.chr);
  };
};

let append32 = (hash, value, offset) => {
  for (j in 0 to 3) {
    Bytes.set(
      hash,
      j + offset,
      Int32.shift_right_logical(value, 24 - j * 8)
      ->Int32.logand(0xFFl)
      ->Int32.to_int
      ->Char.chr,
    );
  };
};

let append64 = (hash, value, offset) => {
  for (j in 0 to 7) {
    Bytes.set(
      hash,
      j + offset,
      Int64.shift_right_logical(value, 56 - j * 8)
      ->Int64.logand(0xFFL)
      ->Int64.to_int
      ->Char.chr,
    );
  };
};

let stringToHex = input => {
  let hex = "0123456789abcdef";
  let length = String.length(input);
  String.init(
    length * 2,
    index => {
      let char = input.[index / 2];
      let charCode = Char.code(char);
      if (index mod 2 == 0) {
        hex.[charCode lsr 4 land 0x0F];
      } else {
        hex.[charCode land 0x0F];
      };
    },
  );
};