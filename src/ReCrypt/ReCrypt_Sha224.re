/* constants [§4.2.3] */
let constants = [|
  0x428a2f98l,
  0x71374491l,
  (-0x4a3f0431l),
  (-0x164a245bl),
  0x3956c25bl,
  0x59f111f1l,
  (-0x6dc07d5cl),
  (-0x54e3a12bl),
  (-0x27f85568l),
  0x12835b01l,
  0x243185bel,
  0x550c7dc3l,
  0x72be5d74l,
  (-0x7f214e02l),
  (-0x6423f959l),
  (-0x3e640e8cl),
  (-0x1b64963fl),
  (-0x1041b87al),
  0x0fc19dc6l,
  0x240ca1ccl,
  0x2de92c6fl,
  0x4a7484aal,
  0x5cb0a9dcl,
  0x76f988dal,
  (-0x67c1aeael),
  (-0x57ce3993l),
  (-0x4ffcd838l),
  (-0x40a68039l),
  (-0x391ff40dl),
  (-0x2a586eb9l),
  0x06ca6351l,
  0x14292967l,
  0x27b70a85l,
  0x2e1b2138l,
  0x4d2c6dfcl,
  0x53380d13l,
  0x650a7354l,
  0x766a0abbl,
  (-0x7e3d36d2l),
  (-0x6d8dd37bl),
  (-0x5d40175fl),
  (-0x57e599b5l),
  (-0x3db47490l),
  (-0x3893ae5dl),
  (-0x2e6d17e7l),
  (-0x2966f9dcl),
  (-0xbf1ca7bl),
  0x106aa070l,
  0x19a4c116l,
  0x1e376c08l,
  0x2748774cl,
  0x34b0bcb5l,
  0x391c0cb3l,
  0x4ed8aa4al,
  0x5b9cca4fl,
  0x682e6ff3l,
  0x748f82eel,
  0x78a5636fl,
  (-0x7b3787ecl),
  (-0x7338fdf8l),
  (-0x6f410006l),
  (-0x5baf9315l),
  (-0x41065c09l),
  (-0x398e870el),
|];

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
        ReCrypt_Functions.SHA2.Int32.sigma1(w[t - 2])
        ->Int32.add(w[t - 7])
        ->Int32.add(ReCrypt_Functions.SHA2.Int32.sigma0(w[t - 15]))
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
        ->Int32.add(ReCrypt_Functions.SHA2.Int32.sum1(e^))
        ->Int32.add(ReCrypt_Functions.SHA2.Int32.change(e^, f^, g^))
        ->Int32.add(constants[t])
        ->Int32.add(w[t]);

      let temp2 =
        Int32.add(
          ReCrypt_Functions.SHA2.Int32.sum0(a^),
          ReCrypt_Functions.SHA2.Int32.majority(a^, b^, c^),
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
  let paddedMessage = ReCrypt_Preprocess.Sha1_224_256.pad(messageBytes);
  processMessage(paddedMessage);
};