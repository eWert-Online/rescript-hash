let make = message => {
  let chunks = Belt.Array.length(message) / 128;

  let a = ref(0x6a09e667f3bcc908L);
  let b = ref(0xbb67ae8584caa73bL);
  let c = ref(0x3c6ef372fe94f82bL);
  let d = ref(0xa54ff53a5f1d36f1L);
  let e = ref(0x510e527fade682d1L);
  let f = ref(0x9b05688c2b3e6c1fL);
  let g = ref(0x1f83d9abfb41bd6bL);
  let h = ref(0x5be0cd19137e2179L);

  for (i in 0 to chunks - 1) {
    let w = Belt.Array.make(80, 0x00L);

    for (t in 0 to 15) {
      for (j in 0 to 7) {
        let result =
          Int64.shift_left(
            w->Belt.Array.get(t)->Belt.Option.getWithDefault(0x00L),
            8,
          )
          ->Int64.add(
              (
                message
                ->Belt.Array.get(j + (i * 128 + 8 * t))
                ->Belt.Option.getWithDefault(0x00)
                land 0xff
              )
              ->Int64.of_int,
            );

        w->Belt.Array.set(t, result)->ignore;
      };
    };

    for (t in 16 to 79) {
      let t2 = w->Belt.Array.get(t - 2)->Belt.Option.getWithDefault(0x00L);
      let t7 = w->Belt.Array.get(t - 7)->Belt.Option.getWithDefault(0x00L);
      let t15 = w->Belt.Array.get(t - 15)->Belt.Option.getWithDefault(0x00L);
      let t16 = w->Belt.Array.get(t - 16)->Belt.Option.getWithDefault(0x00L);

      let result =
        ReCrypt_Functions.SHA2.Int64.sigma1(t2)
        ->Int64.add(t7)
        ->Int64.add(ReCrypt_Functions.SHA2.Int64.sigma0(t15))
        ->Int64.add(t16);

      w->Belt.Array.set(t, result)->ignore;
    };

    let originalA = a^;
    let originalB = b^;
    let originalC = c^;
    let originalD = d^;
    let originalE = e^;
    let originalF = f^;
    let originalG = g^;
    let originalH = h^;

    ReCrypt_Sha512_Constants.k->Belt.Array.forEachWithIndex((t, k) => {
      let temp1 =
        (h^)
        ->Int64.add(ReCrypt_Functions.SHA2.Int64.sum1(e^))
        ->Int64.add(ReCrypt_Functions.SHA2.Int64.change(e^, f^, g^))
        ->Int64.add(k)
        ->Int64.add(
            w->Belt.Array.get(t)->Belt.Option.getWithDefault(0x00L),
          );

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
    });

    a := Int64.add(originalA, a^);
    b := Int64.add(originalB, b^);
    c := Int64.add(originalC, c^);
    d := Int64.add(originalD, d^);
    e := Int64.add(originalE, e^);
    f := Int64.add(originalF, f^);
    g := Int64.add(originalG, g^);
    h := Int64.add(originalH, h^);
  };

  Belt.Array.make(64, 0x00)
  ->ReCrypt_Utils.append64(a^, 0)
  ->ReCrypt_Utils.append64(b^, 8)
  ->ReCrypt_Utils.append64(c^, 16)
  ->ReCrypt_Utils.append64(d^, 24)
  ->ReCrypt_Utils.append64(e^, 32)
  ->ReCrypt_Utils.append64(f^, 40)
  ->ReCrypt_Utils.append64(g^, 48)
  ->ReCrypt_Utils.append64(h^, 56)
  ->Belt.Array.reduce("", (acc, curr) => acc ++ Js.String.fromCharCode(curr))
  ->ReCrypt_Utils.stringToHex;
};
