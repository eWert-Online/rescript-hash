/* BASED ON: https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf */

/**
   * Logical functions [§4.1.3].
   * @private
   */
module Logic = {
  let rotr = (x, n) => {
    Int64.logor(
      Int64.shift_right_logical(x, n),
      Int64.shift_left(x, 64 - n),
    );
  };

  let sum0 = x => {
    rotr(x, 28)->Int64.logxor(rotr(x, 34))->Int64.logxor(rotr(x, 39));
  };

  let sum1 = x => {
    rotr(x, 14)->Int64.logxor(rotr(x, 18))->Int64.logxor(rotr(x, 41));
  };

  let sigma0 = x => {
    rotr(x, 1)
    ->Int64.logxor(rotr(x, 8))
    ->Int64.logxor(Int64.shift_right_logical(x, 7));
  };

  let sigma1 = x => {
    rotr(x, 19)
    ->Int64.logxor(rotr(x, 61))
    ->Int64.logxor(Int64.shift_right_logical(x, 6));
  };

  let change = (x, y, z) => {
    Int64.logand(x, y)->Int64.logxor(Int64.logand(Int64.lognot(x), z));
  };

  let majority = (x, y, z) => {
    Int64.logand(x, y)
    ->Int64.logxor(Int64.logand(x, z))
    ->Int64.logxor(Int64.logand(y, z));
  };
};

/* constants [§4.2.3] */
module Constants = {
  let words = [|
    Int64.of_string("0x428a2f98d728ae22"),
    Int64.of_string("0x7137449123ef65cd"),
    Int64.of_string("0xb5c0fbcfec4d3b2f"),
    Int64.of_string("0xe9b5dba58189dbbc"),
    Int64.of_string("0x3956c25bf348b538"),
    Int64.of_string("0x59f111f1b605d019"),
    Int64.of_string("0x923f82a4af194f9b"),
    Int64.of_string("0xab1c5ed5da6d8118"),
    Int64.of_string("0xd807aa98a3030242"),
    Int64.of_string("0x12835b0145706fbe"),
    Int64.of_string("0x243185be4ee4b28c"),
    Int64.of_string("0x550c7dc3d5ffb4e2"),
    Int64.of_string("0x72be5d74f27b896f"),
    Int64.of_string("0x80deb1fe3b1696b1"),
    Int64.of_string("0x9bdc06a725c71235"),
    Int64.of_string("0xc19bf174cf692694"),
    Int64.of_string("0xe49b69c19ef14ad2"),
    Int64.of_string("0xefbe4786384f25e3"),
    Int64.of_string("0x0fc19dc68b8cd5b5"),
    Int64.of_string("0x240ca1cc77ac9c65"),
    Int64.of_string("0x2de92c6f592b0275"),
    Int64.of_string("0x4a7484aa6ea6e483"),
    Int64.of_string("0x5cb0a9dcbd41fbd4"),
    Int64.of_string("0x76f988da831153b5"),
    Int64.of_string("0x983e5152ee66dfab"),
    Int64.of_string("0xa831c66d2db43210"),
    Int64.of_string("0xb00327c898fb213f"),
    Int64.of_string("0xbf597fc7beef0ee4"),
    Int64.of_string("0xc6e00bf33da88fc2"),
    Int64.of_string("0xd5a79147930aa725"),
    Int64.of_string("0x06ca6351e003826f"),
    Int64.of_string("0x142929670a0e6e70"),
    Int64.of_string("0x27b70a8546d22ffc"),
    Int64.of_string("0x2e1b21385c26c926"),
    Int64.of_string("0x4d2c6dfc5ac42aed"),
    Int64.of_string("0x53380d139d95b3df"),
    Int64.of_string("0x650a73548baf63de"),
    Int64.of_string("0x766a0abb3c77b2a8"),
    Int64.of_string("0x81c2c92e47edaee6"),
    Int64.of_string("0x92722c851482353b"),
    Int64.of_string("0xa2bfe8a14cf10364"),
    Int64.of_string("0xa81a664bbc423001"),
    Int64.of_string("0xc24b8b70d0f89791"),
    Int64.of_string("0xc76c51a30654be30"),
    Int64.of_string("0xd192e819d6ef5218"),
    Int64.of_string("0xd69906245565a910"),
    Int64.of_string("0xf40e35855771202a"),
    Int64.of_string("0x106aa07032bbd1b8"),
    Int64.of_string("0x19a4c116b8d2d0c8"),
    Int64.of_string("0x1e376c085141ab53"),
    Int64.of_string("0x2748774cdf8eeb99"),
    Int64.of_string("0x34b0bcb5e19b48a8"),
    Int64.of_string("0x391c0cb3c5c95a63"),
    Int64.of_string("0x4ed8aa4ae3418acb"),
    Int64.of_string("0x5b9cca4f7763e373"),
    Int64.of_string("0x682e6ff3d6b2b8a3"),
    Int64.of_string("0x748f82ee5defb2fc"),
    Int64.of_string("0x78a5636f43172f60"),
    Int64.of_string("0x84c87814a1f0ab72"),
    Int64.of_string("0x8cc702081a6439ec"),
    Int64.of_string("0x90befffa23631e28"),
    Int64.of_string("0xa4506cebde82bde9"),
    Int64.of_string("0xbef9a3f7b2c67915"),
    Int64.of_string("0xc67178f2e372532b"),
    Int64.of_string("0xca273eceea26619c"),
    Int64.of_string("0xd186b8c721c0c207"),
    Int64.of_string("0xeada7dd6cde0eb1e"),
    Int64.of_string("0xf57d4f7fee6ed178"),
    Int64.of_string("0x06f067aa72176fba"),
    Int64.of_string("0x0a637dc5a2c898a6"),
    Int64.of_string("0x113f9804bef90dae"),
    Int64.of_string("0x1b710b35131c471b"),
    Int64.of_string("0x28db77f523047d84"),
    Int64.of_string("0x32caab7b40c72493"),
    Int64.of_string("0x3c9ebe0a15c9bebc"),
    Int64.of_string("0x431d67c49c100d4c"),
    Int64.of_string("0x4cc5d4becb3e42b6"),
    Int64.of_string("0x597f299cfc657e2a"),
    Int64.of_string("0x5fcb6fab3ad6faec"),
    Int64.of_string("0x6c44198c4a475817"),
  |];

  let initial = [|
    Int64.of_string("0x6a09e667f3bcc908"),
    Int64.of_string("0xbb67ae8584caa73b"),
    Int64.of_string("0x3c6ef372fe94f82b"),
    Int64.of_string("0xa54ff53a5f1d36f1"),
    Int64.of_string("0x510e527fade682d1"),
    Int64.of_string("0x9b05688c2b3e6c1f"),
    Int64.of_string("0x1f83d9abfb41bd6b"),
    Int64.of_string("0x5be0cd19137e2179"),
  |];
};

/* Padding the Message [§5.1.2] */
let pad = (msgBytes: Bytes.t) => {
  let size = ref(Bytes.length(msgBytes) + 17);
  while (size^ mod 128 != 0) {
    size := size^ + 1;
  };

  Bytes.init(
    size^,
    index => {
      let length = Bytes.length(msgBytes);
      switch (index) {
      | i when i < length => Bytes.get(msgBytes, i)
      | i when i == length => Char.chr(0x80)
      | i when i == size^ - 1 => (length * 8)->char_of_int
      | _ => Char.chr(0x00)
      };
    },
  );
};

/* Converts the byte array input starting at index j into an int64 */
let int64_of_bytes = (input, j) => {
  let v = ref(Int64.zero);
  for (i in 0 to 7) {
    v :=
      Int64.shift_left(v^, 8)
      ->Int64.add(
          switch (Bytes.get(input, i + j)) {
          | exception _ => Int64.zero
          | some => Int64.of_int(Char.code(some) land 0xff)
          },
        );
  };
  v^;
};

let append = (hash, value, offset) => {
  for (j in 0 to 7) {
    Bytes.set(
      hash,
      j + offset,
      Int64.shift_right_logical(value, 56 - j * 8)
      ->Int64.logand(Int64.of_int(0xFF))
      ->Int64.to_int
      ->Char.chr,
    );
  };
};

let stringToHex = input => {
  let hex = "0123456789abcdef";
  let length = String.length(input);
  String.init(
    length * 2,
    index => {
      let char = input.[index / 2];
      let charCode = Char.code(char);
      if (index mod 2 == 0) {
        hex.[charCode lsr 4 land 0x0F];
      } else {
        hex.[charCode land 0x0F];
      };
    },
  );
};

let processMessage = (message: Bytes.t) => {
  let chunks = Bytes.length(message) / 128;

  let a = ref(Constants.initial[0]);
  let b = ref(Constants.initial[1]);
  let c = ref(Constants.initial[2]);
  let d = ref(Constants.initial[3]);
  let e = ref(Constants.initial[4]);
  let f = ref(Constants.initial[5]);
  let g = ref(Constants.initial[6]);
  let h = ref(Constants.initial[7]);

  for (i in 0 to chunks - 1) {
    let w = Array.make(80, Int64.zero);

    for (t in 0 to 15) {
      w[t] = int64_of_bytes(message, i * 128 + 8 * t);
    };

    for (t in 16 to 79) {
      w[t] =
        Logic.sigma1(w[t - 2])
        ->Int64.add(w[t - 7])
        ->Int64.add(Logic.sigma0(w[t - 15]))
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
        ->Int64.add(Logic.sum1(e^))
        ->Int64.add(Logic.change(e^, f^, g^))
        ->Int64.add(Constants.words[t])
        ->Int64.add(w[t]);

      let temp2 = Int64.add(Logic.sum0(a^), Logic.majority(a^, b^, c^));

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

  let sha512raw = Bytes.make(64, Char.chr(0));
  append(sha512raw, a^, 0);
  append(sha512raw, b^, 8);
  append(sha512raw, c^, 16);
  append(sha512raw, d^, 24);
  append(sha512raw, e^, 32);
  append(sha512raw, f^, 40);
  append(sha512raw, g^, 48);
  append(sha512raw, h^, 56);

  Bytes.to_string(sha512raw)->stringToHex;
};

let make = message => {
  let messageBytes = Bytes.of_string(message);
  let paddedMessage = pad(messageBytes);
  processMessage(paddedMessage);
};