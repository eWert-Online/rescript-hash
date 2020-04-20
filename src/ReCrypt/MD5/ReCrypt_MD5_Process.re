let make = (message: Bytes.t) => {
  let chunks = (Bytes.length(message) + 8) asr 6;

  let a = ref(ReCrypt_MD5_Constants.initialHash[0]);
  let b = ref(ReCrypt_MD5_Constants.initialHash[1]);
  let c = ref(ReCrypt_MD5_Constants.initialHash[2]);
  let d = ref(ReCrypt_MD5_Constants.initialHash[3]);

  let w = Array.make(16, 0);

  for (i in 0 to chunks - 1) {
    for (j in 0 to 63) {
      w[j lsr 2] =
        Bytes.get(message, i lsl 6 + j)->Char.code lsl 24 lor w[j lsr 2] lsr 8;
    };

    let originalA = a^;
    let originalB = b^;
    let originalC = c^;
    let originalD = d^;

    for (j in 0 to 63) {
      let f =
        if (0 <= j && j <= 15) {
          b^ land c^ lor (lnot(b^) land d^);
        } else if (16 <= j && j <= 31) {
          b^ land d^ lor (c^ land lnot(d^));
        } else if (32 <= j && j <= 47) {
          b^ lxor c^ lxor d^;
        } else {
          c^ lxor (b^ lor lnot(d^));
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
            a^ + f + w[g] + ReCrypt_MD5_Constants.k[j],
            ReCrypt_MD5_Constants.s[(j lsr 4) lsl 2 lor (j land 3)],
          );

      a := d^;
      d := c^;
      c := b^;
      b := temp;
    };

    a := originalA + a^;
    b := originalB + b^;
    c := originalC + c^;
    d := originalD + d^;
  };

  let md5 = Bytes.make(16, Char.chr(0));

  ReCrypt_Utils.append(md5, a^, 0);
  ReCrypt_Utils.append(md5, b^, 4);
  ReCrypt_Utils.append(md5, c^, 8);
  ReCrypt_Utils.append(md5, d^, 12);

  Bytes.to_string(md5)->ReCrypt_Utils.stringToHex;
};