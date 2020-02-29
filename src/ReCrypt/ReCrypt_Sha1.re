/* constants [§4.2.3] */
let initialHash = [|
  0x67452301l,
  0xEFCDAB89l,
  0x98BADCFEl,
  0x10325476l,
  0xC3D2E1F0l,
|];

let processMessage = (message: Bytes.t) => {
  let chunks = (Bytes.length(message) + 8) asr 6;

  let a = ref(initialHash[0]);
  let b = ref(initialHash[1]);
  let c = ref(initialHash[2]);
  let d = ref(initialHash[3]);
  let e = ref(initialHash[4]);

  for (i in 0 to chunks - 1) {
    let w = Array.make(80, Int32.zero);

    for (t in 0 to 15) {
      w[t] =
        Bytes.unsafe_get(message, i * 64 + 4 * t)
        ->Char.code
        ->Int32.of_int
        ->Int32.shift_left(24)
        ->Int32.logand(-0x1000000l);

      w[t] =
        w[t]
        ->Int32.logor(
            Bytes.unsafe_get(message, i * 64 + 4 * t + 1)
            ->Char.code
            ->Int32.of_int
            ->Int32.shift_left(16)
            ->Int32.logand(0x00FF0000l),
          );
      w[t] =
        w[t]
        ->Int32.logor(
            Bytes.unsafe_get(message, i * 64 + 4 * t + 2)
            ->Char.code
            ->Int32.of_int
            ->Int32.shift_left(8)
            ->Int32.logand(0xFF00l)
            ->Int32.logor(
                Bytes.unsafe_get(message, i * 64 + 4 * t + 3)
                ->Char.code
                ->Int32.of_int
                ->Int32.logand(0xFFl),
              ),
          );
    };

    for (t in 16 to 79) {
      w[t] =
        ReCrypt_Functions.Sha1.rotl(
          w[t - 3]
          ->Int32.logxor(w[t - 8])
          ->Int32.logxor(w[t - 14])
          ->Int32.logxor(w[t - 16]),
          1,
        );
    };

    let originalA = a^;
    let originalB = b^;
    let originalC = c^;
    let originalD = d^;
    let originalE = e^;

    for (t in 0 to 79) {
      let temp =
        ReCrypt_Functions.Sha1.rotl(a^, 5)
        ->Int32.add(ReCrypt_Functions.Sha1.f(t, b^, c^, d^))
        ->Int32.add(e^)
        ->Int32.add(ReCrypt_Constants.sha1(t))
        ->Int32.add(w[t]);

      e := d^;
      d := c^;
      c := ReCrypt_Functions.Sha1.rotl(b^, 30);
      b := a^;
      a := temp;
    };

    a := Int32.add(originalA, a^);
    b := Int32.add(originalB, b^);
    c := Int32.add(originalC, c^);
    d := Int32.add(originalD, d^);
    e := Int32.add(originalE, e^);
  };

  let sha1raw = Bytes.make(20, Char.chr(0));
  ReCrypt_Utils.append32(sha1raw, a^, 0);
  ReCrypt_Utils.append32(sha1raw, b^, 4);
  ReCrypt_Utils.append32(sha1raw, c^, 8);
  ReCrypt_Utils.append32(sha1raw, d^, 12);
  ReCrypt_Utils.append32(sha1raw, e^, 16);

  Bytes.to_string(sha1raw)->ReCrypt_Utils.stringToHex;
};

let make = message => {
  let messageBytes = Bytes.of_string(message);
  let paddedMessage = ReCrypt_Preprocess.Sha1_224_256.pad(messageBytes);
  processMessage(paddedMessage);
};