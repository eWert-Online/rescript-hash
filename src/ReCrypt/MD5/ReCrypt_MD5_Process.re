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

    ReCrypt_MD5_Constants.k->Belt.Array.forEachWithIndex((j, k) => {
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
        + ReCrypt_Functions.MD.rotl(
            a^ + f + w->Belt.Array.get(g)->Belt.Option.getWithDefault(0) + k,
            ReCrypt_MD5_Constants.s
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
  ->ReCrypt_Utils.append(a^, 0)
  ->ReCrypt_Utils.append(b^, 4)
  ->ReCrypt_Utils.append(c^, 8)
  ->ReCrypt_Utils.append(d^, 12)
  ->Belt.Array.reduce("", (acc, curr) => acc ++ Js.String.fromCharCode(curr))
  ->ReCrypt_Utils.stringToHex;
};
