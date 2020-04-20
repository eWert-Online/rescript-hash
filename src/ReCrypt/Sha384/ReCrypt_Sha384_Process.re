let make = (message: Bytes.t) => {
  let chunks = Bytes.length(message) / 128;

  let a = ref(ReCrypt_Sha384_Constants.initialHash[0]);
  let b = ref(ReCrypt_Sha384_Constants.initialHash[1]);
  let c = ref(ReCrypt_Sha384_Constants.initialHash[2]);
  let d = ref(ReCrypt_Sha384_Constants.initialHash[3]);
  let e = ref(ReCrypt_Sha384_Constants.initialHash[4]);
  let f = ref(ReCrypt_Sha384_Constants.initialHash[5]);
  let g = ref(ReCrypt_Sha384_Constants.initialHash[6]);
  let h = ref(ReCrypt_Sha384_Constants.initialHash[7]);

  for (i in 0 to chunks - 1) {
    let w = Array.make(80, Int64.zero);

    for (t in 0 to 15) {
      for (j in 0 to 7) {
        w[t] =
          Int64.shift_left(w[t], 8)
          ->Int64.add(
              switch (Bytes.get(message, j + (i * 128 + 8 * t))) {
              | exception _ => Int64.zero
              | some => Int64.of_int(Char.code(some) land 0xff)
              },
            );
      };
    };

    for (t in 16 to 79) {
      w[t] =
        ReCrypt_Functions.SHA2.Int64.sigma1(w[t - 2])
        ->Int64.add(w[t - 7])
        ->Int64.add(ReCrypt_Functions.SHA2.Int64.sigma0(w[t - 15]))
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
        ->Int64.add(ReCrypt_Functions.SHA2.Int64.sum1(e^))
        ->Int64.add(ReCrypt_Functions.SHA2.Int64.change(e^, f^, g^))
        ->Int64.add(ReCrypt_Sha384_Constants.k[t])
        ->Int64.add(w[t]);

      let temp2 =
        Int64.add(
          ReCrypt_Functions.SHA2.Int64.sum0(a^),
          ReCrypt_Functions.SHA2.Int64.majority(a^, b^, c^),
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