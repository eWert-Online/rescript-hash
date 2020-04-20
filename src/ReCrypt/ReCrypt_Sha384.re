/* constants [§4.2.3] */
let constants = [|
  0x428A2F98D728AE22L,
  0x7137449123EF65CDL,
  (-0x4a3f043013b2c4d1L),
  (-0x164a245a7e762444L),
  0x3956C25BF348B538L,
  0x59F111F1B605D019L,
  (-0x6dc07d5b50e6b065L),
  (-0x54e3a12a25927ee8L),
  (-0x27f855675cfcfdbeL),
  0x12835B0145706FBEL,
  0x243185BE4EE4B28CL,
  0x550C7DC3D5FFB4E2L,
  0x72BE5D74F27B896FL,
  (-0x7f214e01c4e9694fL),
  (-0x6423f958da38edcbL),
  (-0x3e640e8b3096d96cL),
  (-0x1b64963e610eb52eL),
  (-0x1041b879c7b0da1dL),
  0x0FC19DC68B8CD5B5L,
  0x240CA1CC77AC9C65L,
  0x2DE92C6F592B0275L,
  0x4A7484AA6EA6E483L,
  0x5CB0A9DCBD41FBD4L,
  0x76F988DA831153B5L,
  (-0x67c1aead11992055L),
  (-0x57ce3992d24bcdf0L),
  (-0x4ffcd8376704dec1L),
  (-0x40a680384110f11cL),
  (-0x391ff40cc257703eL),
  (-0x2a586eb86cf558dbL),
  0x06CA6351E003826FL,
  0x142929670A0E6E70L,
  0x27B70A8546D22FFCL,
  0x2E1B21385C26C926L,
  0x4D2C6DFC5AC42AEDL,
  0x53380D139D95B3DFL,
  0x650A73548BAF63DEL,
  0x766A0ABB3C77B2A8L,
  (-0x7e3d36d1b812511aL),
  (-0x6d8dd37aeb7dcac5L),
  (-0x5d40175eb30efc9cL),
  (-0x57e599b443bdcfffL),
  (-0x3db4748f2f07686fL),
  (-0x3893ae5cf9ab41d0L),
  (-0x2e6d17e62910ade8L),
  (-0x2966f9dbaa9a56f0L),
  (-0xbf1ca7aa88edfd6L),
  0x106AA07032BBD1B8L,
  0x19A4C116B8D2D0C8L,
  0x1E376C085141AB53L,
  0x2748774CDF8EEB99L,
  0x34B0BCB5E19B48A8L,
  0x391C0CB3C5C95A63L,
  0x4ED8AA4AE3418ACBL,
  0x5B9CCA4F7763E373L,
  0x682E6FF3D6B2B8A3L,
  0x748F82EE5DEFB2FCL,
  0x78A5636F43172F60L,
  (-0x7b3787eb5e0f548eL),
  (-0x7338fdf7e59bc614L),
  (-0x6f410005dc9ce1d8L),
  (-0x5baf9314217d4217L),
  (-0x41065c084d3986ebL),
  (-0x398e870d1c8dacd5L),
  (-0x35d8c13115d99e64L),
  (-0x2e794738de3f3df9L),
  (-0x15258229321f14e2L),
  (-0xa82b08011912e88L),
  0x06F067AA72176FBAL,
  0x0A637DC5A2C898A6L,
  0x113F9804BEF90DAEL,
  0x1B710B35131C471BL,
  0x28DB77F523047D84L,
  0x32CAAB7B40C72493L,
  0x3C9EBE0A15C9BEBCL,
  0x431D67C49C100D4CL,
  0x4CC5D4BECB3E42B6L,
  0x597F299CFC657E2AL,
  0x5FCB6FAB3AD6FAECL,
  0x6C44198C4A475817L,
|];

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
        ->Int64.add(constants[t])
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

let make = message => {
  let messageBytes = Bytes.of_string(message);
  let paddedMessage = ReCrypt_Preprocess.Sha384_512.pad(messageBytes);
  processMessage(paddedMessage);
};