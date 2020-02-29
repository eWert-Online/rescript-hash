/* constants [§4.2.3] */
let initialHash = [|
  (-0x344462a23efa6128L),
  0x629a292a367cd507L,
  (-0x6ea6fea5cf8f22e9L),
  0x152fecd8f70e5939L,
  0x67332667ffc00b31L,
  (-0x714bb57897a7eaefL),
  (-0x24f3d1f29b067059L),
  0x47b5481dbefa4fa4L,
|];

let processMessage = (message: Bytes.t) => {
  let chunks = Bytes.length(message) / 128;

  let a = ref(initialHash[0]);
  let b = ref(initialHash[1]);
  let c = ref(initialHash[2]);
  let d = ref(initialHash[3]);
  let e = ref(initialHash[4]);
  let f = ref(initialHash[5]);
  let g = ref(initialHash[6]);
  let h = ref(initialHash[7]);

  for (i in 0 to chunks - 1) {
    let w = Array.make(80, Int64.zero);

    for (t in 0 to 15) {
      w[t] = ReCrypt_Utils.int64_of_bytes(message, i * 128 + 8 * t);
    };

    for (t in 16 to 79) {
      w[t] =
        ReCrypt_Functions.Sha384_512.sigma1(w[t - 2])
        ->Int64.add(w[t - 7])
        ->Int64.add(ReCrypt_Functions.Sha384_512.sigma0(w[t - 15]))
        ->Int64.add(w[t - 16]);
    };

    let originalA = a^;
    let originalB = b^;
    let originalC = c^;
    let originalD = d^;
    let originalE = e^;
    let originalF = f^;
    let originalG = g^;
    let originalH = h^;

    for (t in 0 to 79) {
      let temp1 =
        (h^)
        ->Int64.add(ReCrypt_Functions.Sha384_512.sum1(e^))
        ->Int64.add(ReCrypt_Functions.Sha384_512.change(e^, f^, g^))
        ->Int64.add(ReCrypt_Constants.sha384[t])
        ->Int64.add(w[t]);

      let temp2 =
        Int64.add(
          ReCrypt_Functions.Sha384_512.sum0(a^),
          ReCrypt_Functions.Sha384_512.majority(a^, b^, c^),
        );

      h := g^;
      g := f^;
      f := e^;
      e := Int64.add(d^, temp1);
      d := c^;
      c := b^;
      b := a^;
      a := Int64.add(temp1, temp2);
    };

    a := Int64.add(originalA, a^);
    b := Int64.add(originalB, b^);
    c := Int64.add(originalC, c^);
    d := Int64.add(originalD, d^);
    e := Int64.add(originalE, e^);
    f := Int64.add(originalF, f^);
    g := Int64.add(originalG, g^);
    h := Int64.add(originalH, h^);
  };

  let sha384raw = Bytes.make(48, Char.chr(0));
  ReCrypt_Utils.append64(sha384raw, a^, 0);
  ReCrypt_Utils.append64(sha384raw, b^, 8);
  ReCrypt_Utils.append64(sha384raw, c^, 16);
  ReCrypt_Utils.append64(sha384raw, d^, 24);
  ReCrypt_Utils.append64(sha384raw, e^, 32);
  ReCrypt_Utils.append64(sha384raw, f^, 40);

  Bytes.to_string(sha384raw)->ReCrypt_Utils.stringToHex;
};

let make = message => {
  let messageBytes = Bytes.of_string(message);
  let paddedMessage = ReCrypt_Preprocess.Sha384_512.pad(messageBytes);
  processMessage(paddedMessage);
};