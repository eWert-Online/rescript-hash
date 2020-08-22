let append = (hash, value, offset) => {
  for (j in 0 to 3) {
    hash->Belt.Array.set(j + offset, value lsr (j * 8) land 0xFF)->ignore;
  };
  hash;
};

let append32 = (hash, value, offset) => {
  for (j in 0 to 3) {
    hash
    ->Belt.Array.set(
        j + offset,
        Int32.shift_right_logical(value, 24 - j * 8)
        ->Int32.logand(0xFFl)
        ->Int32.to_int,
      )
    ->ignore;
  };
  hash;
};

let append64 = (hash, value, offset) => {
  for (j in 0 to 7) {
    hash
    ->Belt.Array.set(
        j + offset,
        Int64.shift_right_logical(value, 56 - j * 8)
        ->Int64.logand(0xFFL)
        ->Int64.to_int,
      )
    ->ignore;
  };
  hash;
};

let stringToHex = input => {
  let hex = "0123456789abcdef";
  input
  ->Js.String2.split("")
  ->Belt.Array.reduce("", (acc, curr) => {
      let charCode = curr->(Js.String2.charCodeAt(0))->Belt.Int.fromFloat;

      acc
      ++ hex->Js.String2.charAt(charCode lsr 4 land 0x0F)
      ++ hex->Js.String2.charAt(charCode land 0x0F);
    });
};
