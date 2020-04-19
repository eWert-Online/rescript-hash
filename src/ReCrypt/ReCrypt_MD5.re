let constants = [|
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

let initialHash = [|0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476|];

let preprocess = (msgBytes: Bytes.t) => {
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

let processMessage = (message: Bytes.t) => {
  let chunks = (Bytes.length(message) + 8) asr 6;

  let a = ref(initialHash[0]);
  let b = ref(initialHash[1]);
  let c = ref(initialHash[2]);
  let d = ref(initialHash[3]);

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
        + ReCrypt_Functions.MD5.rotl(
            a^ + f + w[g] + constants[j],
            s[(j lsr 4) lsl 2 lor (j land 3)],
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

let make = message => {
  let messageBytes = Bytes.of_string(message);
  let paddedMessage = preprocess(messageBytes);
  processMessage(paddedMessage);
};