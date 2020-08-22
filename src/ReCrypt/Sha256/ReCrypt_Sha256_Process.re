let make = message => {
  let chunks = (Belt.Array.length(message) + 8) asr 6;

  let a = ref(0x6a09e667l);
  let b = ref(-0x4498517bl);
  let c = ref(0x3c6ef372l);
  let d = ref(-0x5ab00ac6l);
  let e = ref(0x510e527fl);
  let f = ref(-0x64fa9774l);
  let g = ref(0x1f83d9abl);
  let h = ref(0x5be0cd19l);

  for (i in 0 to chunks - 1) {
    let w = Belt.Array.make(64, 0x00l);

    for (t in 0 to 15) {
      let result =
        Belt.Array.getUnsafe(message, i * 64 + 4 * t)
        ->Int32.of_int
        ->Int32.shift_left(24)
        ->Int32.logand(-0x1000000l)
        ->Int32.logor(
            Belt.Array.getUnsafe(message, i * 64 + 4 * t + 1)
            ->Int32.of_int
            ->Int32.shift_left(16)
            ->Int32.logand(0x00FF0000l),
          )
        ->Int32.logor(
            Belt.Array.getUnsafe(message, i * 64 + 4 * t + 2)
            ->Int32.of_int
            ->Int32.shift_left(8)
            ->Int32.logand(0xFF00l)
            ->Int32.logor(
                Belt.Array.getUnsafe(message, i * 64 + 4 * t + 3)
                ->Int32.of_int
                ->Int32.logand(0xFFl),
              ),
          );
      w->Belt.Array.set(t, result)->ignore;
    };

    for (t in 16 to 63) {
      let t2 = w->Belt.Array.get(t - 2)->Belt.Option.getWithDefault(0x00l);
      let t7 = w->Belt.Array.get(t - 7)->Belt.Option.getWithDefault(0x00l);
      let t15 = w->Belt.Array.get(t - 15)->Belt.Option.getWithDefault(0x00l);
      let t16 = w->Belt.Array.get(t - 16)->Belt.Option.getWithDefault(0x00l);

      let result =
        ReCrypt_Functions.SHA2.Int32.sigma1(t2)
        ->Int32.add(t7)
        ->Int32.add(ReCrypt_Functions.SHA2.Int32.sigma0(t15))
        ->Int32.add(t16);

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

    ReCrypt_Sha256_Constants.k->Belt.Array.forEachWithIndex((t, k) => {
      let temp1 =
        (h^)
        ->Int32.add(ReCrypt_Functions.SHA2.Int32.sum1(e^))
        ->Int32.add(ReCrypt_Functions.SHA2.Int32.change(e^, f^, g^))
        ->Int32.add(k)
        ->Int32.add(
            w->Belt.Array.get(t)->Belt.Option.getWithDefault(0x00l),
          );

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
    });

    a := Int32.add(originalA, a^);
    b := Int32.add(originalB, b^);
    c := Int32.add(originalC, c^);
    d := Int32.add(originalD, d^);
    e := Int32.add(originalE, e^);
    f := Int32.add(originalF, f^);
    g := Int32.add(originalG, g^);
    h := Int32.add(originalH, h^);
  };

  Belt.Array.make(32, 0x00)
  ->ReCrypt_Utils.append32(a^, 0)
  ->ReCrypt_Utils.append32(b^, 4)
  ->ReCrypt_Utils.append32(c^, 8)
  ->ReCrypt_Utils.append32(d^, 12)
  ->ReCrypt_Utils.append32(e^, 16)
  ->ReCrypt_Utils.append32(f^, 20)
  ->ReCrypt_Utils.append32(g^, 24)
  ->ReCrypt_Utils.append32(h^, 28)
  ->Belt.Array.reduce("", (acc, curr) => acc ++ Js.String.fromCharCode(curr))
  ->ReCrypt_Utils.stringToHex;
};
