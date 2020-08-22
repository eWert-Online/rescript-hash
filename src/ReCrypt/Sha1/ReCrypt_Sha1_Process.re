let make = message => {
  let chunks = (Belt.Array.length(message) + 8) asr 6;

  let a = ref(0x67452301l);
  let b = ref(0xEFCDAB89l);
  let c = ref(0x98BADCFEl);
  let d = ref(0x10325476l);
  let e = ref(0xC3D2E1F0l);

  for (i in 0 to chunks - 1) {
    let w = Belt.Array.make(80, 0x00l);

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

    for (t in 16 to 79) {
      let t3 = w->Belt.Array.get(t - 3)->Belt.Option.getWithDefault(0x00l);
      let t8 = w->Belt.Array.get(t - 8)->Belt.Option.getWithDefault(0x00l);
      let t14 = w->Belt.Array.get(t - 14)->Belt.Option.getWithDefault(0x00l);
      let t16 = w->Belt.Array.get(t - 16)->Belt.Option.getWithDefault(0x00l);
      let result =
        ReCrypt_Functions.SHA1.rotl(
          t3->Int32.logxor(t8)->Int32.logxor(t14)->Int32.logxor(t16),
          1,
        );

      w->Belt.Array.set(t, result)->ignore;
    };

    let originalA = a^;
    let originalB = b^;
    let originalC = c^;
    let originalD = d^;
    let originalE = e^;

    ReCrypt_Sha1_Constants.k->Belt.Array.forEachWithIndex((t, k) => {
      let temp =
        ReCrypt_Functions.SHA1.rotl(a^, 5)
        ->Int32.add(ReCrypt_Functions.SHA1.f(t, b^, c^, d^))
        ->Int32.add(e^)
        ->Int32.add(k)
        ->Int32.add(
            w->Belt.Array.get(t)->Belt.Option.getWithDefault(0x00l),
          );

      e := d^;
      d := c^;
      c := ReCrypt_Functions.SHA1.rotl(b^, 30);
      b := a^;
      a := temp;
    });

    a := Int32.add(originalA, a^);
    b := Int32.add(originalB, b^);
    c := Int32.add(originalC, c^);
    d := Int32.add(originalD, d^);
    e := Int32.add(originalE, e^);
  };

  Belt.Array.make(20, 0x00)
  ->ReCrypt_Utils.append32(a^, 0)
  ->ReCrypt_Utils.append32(b^, 4)
  ->ReCrypt_Utils.append32(c^, 8)
  ->ReCrypt_Utils.append32(d^, 12)
  ->ReCrypt_Utils.append32(e^, 16)
  ->Belt.Array.reduce("", (acc, curr) => acc ++ Js.String.fromCharCode(curr))
  ->ReCrypt_Utils.stringToHex;
};
