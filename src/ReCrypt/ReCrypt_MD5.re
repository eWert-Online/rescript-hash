module Functions = {
  let rotl = (x, n) => {
    x lsl n lor x lsr (64 - n);
  };
};

module Utils = {
  let append = (hash, value, offset) => {
    for (j in 0 to 3) {
      hash->Belt.Array.set(j + offset, value lsr (j * 8) land 0xFF)->ignore;
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
};

module Constants = {
  let k = [|
    0xd76aa478,
    0xe8c7b756,
    0x242070db,
    0xc1bdceee,
    0xf57c0faf,
    0x4787c62a,
    0xa8304613,
    0xfd469501,
    0x698098d8,
    0x8b44f7af,
    0xffff5bb1,
    0x895cd7be,
    0x6b901122,
    0xfd987193,
    0xa679438e,
    0x49b40821,
    0xf61e2562,
    0xc040b340,
    0x265e5a51,
    0xe9b6c7aa,
    0xd62f105d,
    0x02441453,
    0xd8a1e681,
    0xe7d3fbc8,
    0x21e1cde6,
    0xc33707d6,
    0xf4d50d87,
    0x455a14ed,
    0xa9e3e905,
    0xfcefa3f8,
    0x676f02d9,
    0x8d2a4c8a,
    0xfffa3942,
    0x8771f681,
    0x6d9d6122,
    0xfde5380c,
    0xa4beea44,
    0x4bdecfa9,
    0xf6bb4b60,
    0xbebfbc70,
    0x289b7ec6,
    0xeaa127fa,
    0xd4ef3085,
    0x04881d05,
    0xd9d4d039,
    0xe6db99e5,
    0x1fa27cf8,
    0xc4ac5665,
    0xf4292244,
    0x432aff97,
    0xab9423a7,
    0xfc93a039,
    0x655b59c3,
    0x8f0ccc92,
    0xffeff47d,
    0x85845dd1,
    0x6fa87e4f,
    0xfe2ce6e0,
    0xa3014314,
    0x4e0811a1,
    0xf7537e82,
    0xbd3af235,
    0x2ad7d2bb,
    0xeb86d391,
  |];

  let s = [|7, 12, 17, 22, 5, 9, 14, 20, 4, 11, 16, 23, 6, 10, 15, 21|];
};

module Preprocess = {
  let pad = msg => {
    let size = ref(Js.String.length(msg) + 8 + 1);
    while (size^ mod 64 != 0) {
      size := size^ + 1;
    };

    let length = Js.String.length(msg);

    let bytes =
      Belt.Array.makeBy(size^, index =>
        switch (index) {
        | i when i < length =>
          msg->(Js.String2.charCodeAt(i))->Belt.Int.fromFloat
        | i when i == length => 0x80
        | _ => 0x00
        }
      );

    let va = ref(length * 8);
    for (i in 0 to 7) {
      bytes->Belt.Array.set(i + (size^ - 8), va^ land 255)->ignore;
      va := va^ lsr 8;
    };

    bytes;
  };
};

module Process = {
  let make = message => {
    let chunks = (Belt.Array.length(message) + 8) asr 6;

    let a = ref(0x67452301);
    let b = ref(0xEFCDAB89);
    let c = ref(0x98BADCFE);
    let d = ref(0x10325476);

    let w = Belt.Array.make(16, 0);

    for (i in 0 to chunks - 1) {
      for (j in 0 to 63) {
        let result =
          Belt.Array.get(message, i lsl 6 + j)->Belt.Option.getWithDefault(0)
          lsl 24
          lor Belt.Array.get(w, j lsr 2)->Belt.Option.getWithDefault(0)
          lsr 8;

        w->Belt.Array.set(j lsr 2, result)->ignore;
      };

      let originalA = a^;
      let originalB = b^;
      let originalC = c^;
      let originalD = d^;

      Constants.k->Belt.Array.forEachWithIndex((j, k) => {
        let f =
          if (0 <= j && j <= 15) {
            b^ land c^ lor (b^ lxor (-1) land d^);
          } else if (16 <= j && j <= 31) {
            b^ land d^ lor (c^ land (d^ lxor (-1)));
          } else if (32 <= j && j <= 47) {
            b^ lxor c^ lxor d^;
          } else {
            c^ lxor (b^ lor (d^ lxor (-1)));
          };

        let g =
          if (0 <= j && j <= 15) {
            j;
          } else if (16 <= j && j <= 31) {
            (5 * j + 1) mod 16;
          } else if (32 <= j && j <= 47) {
            (3 * j + 5) mod 16;
          } else {
            7 * j mod 16;
          };

        let temp =
          b^
          + Functions.rotl(
              a^
              + f
              + w->Belt.Array.get(g)->Belt.Option.getWithDefault(0)
              + k,
              Constants.s
              ->Belt.Array.get((j lsr 4) lsl 2 lor (j land 3))
              ->Belt.Option.getWithDefault(0),
            );

        a := d^;
        d := c^;
        c := b^;
        b := temp;
      });

      a := originalA + a^;
      b := originalB + b^;
      c := originalC + c^;
      d := originalD + d^;
    };

    Belt.Array.make(16, 0x00)
    ->Utils.append(a^, 0)
    ->Utils.append(b^, 4)
    ->Utils.append(c^, 8)
    ->Utils.append(d^, 12)
    ->Belt.Array.reduce("", (acc, curr) =>
        acc ++ Js.String.fromCharCode(curr)
      )
    ->Utils.stringToHex;
  };
};

let make = message => {
  message->Preprocess.pad->Process.make;
};
