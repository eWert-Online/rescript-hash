/* constants [§4.2.3] */
let initialHash = [|
  (-0x3efa6128l),
  0x367cd507l,
  0x3070dd17l,
  (-0x8f1a6c7l),
  (-0x3ff4cfl),
  0x68581511l,
  0x64f98fa7l,
  (-0x4105b05cl),
|];

let processMessage = (message: Bytes.t) => {
  let chunks = (Bytes.length(message) + 8) asr 6;

  let a = ref(initialHash[0]);
  let b = ref(initialHash[1]);
  let c = ref(initialHash[2]);
  let d = ref(initialHash[3]);
  let e = ref(initialHash[4]);
  let f = ref(initialHash[5]);
  let g = ref(initialHash[6]);
  let h = ref(initialHash[7]);

  for (i in 0 to chunks - 1) {
    let w = Array.make(64, Int32.zero);

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

    for (t in 16 to 63) {
      w[t] =
        ReCrypt_Functions.Sha224_256.sigma1(w[t - 2])
        ->Int32.add(w[t - 7])
        ->Int32.add(ReCrypt_Functions.Sha224_256.sigma0(w[t - 15]))
        ->Int32.add(w[t - 16]);
    };

    let originalA = a^;
    let originalB = b^;
    let originalC = c^;
    let originalD = d^;
    let originalE = e^;
    let originalF = f^;
    let originalG = g^;
    let originalH = h^;

    for (t in 0 to 63) {
      let temp1 =
        (h^)
        ->Int32.add(ReCrypt_Functions.Sha224_256.sum1(e^))
        ->Int32.add(ReCrypt_Functions.Sha224_256.change(e^, f^, g^))
        ->Int32.add(ReCrypt_Constants.sha224[t])
        ->Int32.add(w[t]);

      let temp2 =
        Int32.add(
          ReCrypt_Functions.Sha224_256.sum0(a^),
          ReCrypt_Functions.Sha224_256.majority(a^, b^, c^),
        );

      h := g^;
      g := f^;
      f := e^;
      e := Int32.add(d^, temp1);
      d := c^;
      c := b^;
      b := a^;
      a := Int32.add(temp1, temp2);
    };

    a := Int32.add(originalA, a^);
    b := Int32.add(originalB, b^);
    c := Int32.add(originalC, c^);
    d := Int32.add(originalD, d^);
    e := Int32.add(originalE, e^);
    f := Int32.add(originalF, f^);
    g := Int32.add(originalG, g^);
    h := Int32.add(originalH, h^);
  };

  let sha224raw = Bytes.make(28, Char.chr(0));
  ReCrypt_Utils.append32(sha224raw, a^, 0);
  ReCrypt_Utils.append32(sha224raw, b^, 4);
  ReCrypt_Utils.append32(sha224raw, c^, 8);
  ReCrypt_Utils.append32(sha224raw, d^, 12);
  ReCrypt_Utils.append32(sha224raw, e^, 16);
  ReCrypt_Utils.append32(sha224raw, f^, 20);
  ReCrypt_Utils.append32(sha224raw, g^, 24);

  Bytes.to_string(sha224raw)->ReCrypt_Utils.stringToHex;
};

let make = message => {
  let messageBytes = Bytes.of_string(message);
  let paddedMessage = ReCrypt_Preprocess.Sha224_256.pad(messageBytes);
  processMessage(paddedMessage);
};