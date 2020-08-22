let make = message => {
  let chunks = (Belt.Array.length(message) + 8) asr 6;

  let a = ref(-0x3efa6128l);
  let b = ref(0x367cd507l);
  let c = ref(0x3070dd17l);
  let d = ref(-0x8f1a6c7l);
  let e = ref(-0x3ff4cfl);
  let f = ref(0x68581511l);
  let g = ref(0x64f98fa7l);
  let h = ref(-0x4105b05cl);

  for (i in 0 to chunks - 1) {
    let w = Belt.Array.make(64, 0x00l);

    for (t in 0 to 15) {
      let result =
        Belt.Array.get(message, i * 64 + 4 * t)
        ->Belt.Option.getWithDefault(0)
        ->Int32.of_int
        ->Int32.shift_left(24)
        ->Int32.logand(-0x1000000l)
        ->Int32.logor(
            Belt.Array.get(message, i * 64 + 4 * t + 1)
            ->Belt.Option.getWithDefault(0)
            ->Int32.of_int
            ->Int32.shift_left(16)
            ->Int32.logand(0x00FF0000l),
          )
        ->Int32.logor(
            Belt.Array.get(message, i * 64 + 4 * t + 2)
            ->Belt.Option.getWithDefault(0)
            ->Int32.of_int
            ->Int32.shift_left(8)
            ->Int32.logand(0xFF00l)
            ->Int32.logor(
                Belt.Array.get(message, i * 64 + 4 * t + 3)
                ->Belt.Option.getWithDefault(0)
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

    ReCrypt_Sha224_Constants.k->Belt.Array.forEachWithIndex((t, k) => {
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

  Belt.Array.make(28, 0x00)
  ->ReCrypt_Utils.append32(a^, 0)
  ->ReCrypt_Utils.append32(b^, 4)
  ->ReCrypt_Utils.append32(c^, 8)
  ->ReCrypt_Utils.append32(d^, 12)
  ->ReCrypt_Utils.append32(e^, 16)
  ->ReCrypt_Utils.append32(f^, 20)
  ->ReCrypt_Utils.append32(g^, 24)
  ->Belt.Array.reduce("", (acc, curr) => acc ++ Js.String.fromCharCode(curr))
  ->ReCrypt_Utils.stringToHex;
};
