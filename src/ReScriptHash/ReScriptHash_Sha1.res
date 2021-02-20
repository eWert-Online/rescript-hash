module Functions = {
  let rotl = (x, n) => Int32.logor(Int32.shift_left(x, n), Int32.shift_right_logical(x, 64 - n))

  let change = (x, y, z) => Int32.logand(x, y)->Int32.logxor(Int32.logand(Int32.lognot(x), z))

  let majority = (x, y, z) =>
    Int32.logand(x, y)->Int32.logxor(Int32.logand(x, z))->Int32.logxor(Int32.logand(y, z))

  let parity = (x, y, z) => x->Int32.logxor(y)->Int32.logxor(z)

  let f = (t, x, y, z) =>
    switch t {
    | t if t >= 0 && t <= 19 => change(x, y, z)
    | t if t >= 20 && t <= 39 => parity(x, y, z)
    | t if t >= 40 && t <= 59 => majority(x, y, z)
    | t if t >= 60 && t <= 79 => parity(x, y, z)
    | _ => 0x00l
    }
}

module Utils = {
  let append32 = (hash, value, offset) => {
    for j in 0 to 3 {
      hash
      ->Js.Array2.unsafe_set(
        j + offset,
        Int32.shift_right_logical(value, 24 - j * 8)->Int32.logand(0xFFl)->Int32.to_int,
      )
      ->ignore
    }
    hash
  }

  let stringToHex = input => {
    let hex = "0123456789abcdef"
    input->Js.String2.split("")->Js.Array2.reduce((acc, curr) => {
      let charCode = curr->Js.String2.charCodeAt(0)->Belt.Int.fromFloat

      acc ++
      (hex->Js.String2.charAt(land(lsr(charCode, 4), 0x0F)) ++
      hex->Js.String2.charAt(land(charCode, 0x0F)))
    }, "")
  }
}

module Constants = {
  let k = [
    0x5A827999l,
    0x5A827999l,
    0x5A827999l,
    0x5A827999l,
    0x5A827999l,
    0x5A827999l,
    0x5A827999l,
    0x5A827999l,
    0x5A827999l,
    0x5A827999l,
    0x5A827999l,
    0x5A827999l,
    0x5A827999l,
    0x5A827999l,
    0x5A827999l,
    0x5A827999l,
    0x5A827999l,
    0x5A827999l,
    0x5A827999l,
    0x5A827999l,
    0x6ED9EBA1l,
    0x6ED9EBA1l,
    0x6ED9EBA1l,
    0x6ED9EBA1l,
    0x6ED9EBA1l,
    0x6ED9EBA1l,
    0x6ED9EBA1l,
    0x6ED9EBA1l,
    0x6ED9EBA1l,
    0x6ED9EBA1l,
    0x6ED9EBA1l,
    0x6ED9EBA1l,
    0x6ED9EBA1l,
    0x6ED9EBA1l,
    0x6ED9EBA1l,
    0x6ED9EBA1l,
    0x6ED9EBA1l,
    0x6ED9EBA1l,
    0x6ED9EBA1l,
    0x6ED9EBA1l,
    0x8F1BBCDCl,
    0x8F1BBCDCl,
    0x8F1BBCDCl,
    0x8F1BBCDCl,
    0x8F1BBCDCl,
    0x8F1BBCDCl,
    0x8F1BBCDCl,
    0x8F1BBCDCl,
    0x8F1BBCDCl,
    0x8F1BBCDCl,
    0x8F1BBCDCl,
    0x8F1BBCDCl,
    0x8F1BBCDCl,
    0x8F1BBCDCl,
    0x8F1BBCDCl,
    0x8F1BBCDCl,
    0x8F1BBCDCl,
    0x8F1BBCDCl,
    0x8F1BBCDCl,
    0x8F1BBCDCl,
    0xCA62C1D6l,
    0xCA62C1D6l,
    0xCA62C1D6l,
    0xCA62C1D6l,
    0xCA62C1D6l,
    0xCA62C1D6l,
    0xCA62C1D6l,
    0xCA62C1D6l,
    0xCA62C1D6l,
    0xCA62C1D6l,
    0xCA62C1D6l,
    0xCA62C1D6l,
    0xCA62C1D6l,
    0xCA62C1D6l,
    0xCA62C1D6l,
    0xCA62C1D6l,
    0xCA62C1D6l,
    0xCA62C1D6l,
    0xCA62C1D6l,
    0xCA62C1D6l,
  ]
}

module Preprocess = {
  let pad = msg => {
    let size = ref(Js.String.length(msg) + 8 + 1)
    while mod(size.contents, 64) != 0 {
      size := size.contents + 1
    }

    let length = Js.String.length(msg)

    let bytes = Belt.Array.makeBy(size.contents, index =>
      switch index {
      | i if i < length => msg->Js.String2.charCodeAt(i)->Belt.Int.fromFloat
      | i if i == length => 0x80
      | _ => 0x00
      }
    )

    let va = ref(length * 8)
    for i in 1 to 15 {
      let _ = bytes->Js.Array2.unsafe_set(Js.Array2.length(bytes) - i, land(va.contents, 255))

      va := asr(va.contents, 8)
    }
    bytes
  }
}

module Process = {
  let make = message => {
    let chunks = asr(Js.Array2.length(message) + 8, 6)

    let a = ref(0x67452301l)
    let b = ref(0xEFCDAB89l)
    let c = ref(0x98BADCFEl)
    let d = ref(0x10325476l)
    let e = ref(0xC3D2E1F0l)

    for i in 0 to chunks - 1 {
      let w = Belt.Array.make(80, 0x00l)

      for t in 0 to 15 {
        let result =
          Js.Array2.unsafe_get(message, i * 64 + 4 * t)
          ->Int32.of_int
          ->Int32.shift_left(24)
          ->Int32.logand(-0x1000000l)
          ->Int32.logor(
            Js.Array2.unsafe_get(message, i * 64 + 4 * t + 1)
            ->Int32.of_int
            ->Int32.shift_left(16)
            ->Int32.logand(0x00FF0000l),
          )
          ->Int32.logor(
            Js.Array2.unsafe_get(message, i * 64 + 4 * t + 2)
            ->Int32.of_int
            ->Int32.shift_left(8)
            ->Int32.logand(0xFF00l)
            ->Int32.logor(
              Js.Array2.unsafe_get(message, i * 64 + 4 * t + 3)->Int32.of_int->Int32.logand(0xFFl),
            ),
          )

        w->Js.Array2.unsafe_set(t, result)->ignore
      }

      for t in 16 to 79 {
        let t3 = w->Js.Array2.unsafe_get(t - 3)
        let t8 = w->Js.Array2.unsafe_get(t - 8)
        let t14 = w->Js.Array2.unsafe_get(t - 14)
        let t16 = w->Js.Array2.unsafe_get(t - 16)
        let result = Functions.rotl(t3->Int32.logxor(t8)->Int32.logxor(t14)->Int32.logxor(t16), 1)

        w->Js.Array2.unsafe_set(t, result)->ignore
      }

      let originalA = a.contents
      let originalB = b.contents
      let originalC = c.contents
      let originalD = d.contents
      let originalE = e.contents

      Constants.k->Js.Array2.forEachi((k, t) => {
        let temp =
          Functions.rotl(a.contents, 5)
          ->Int32.add(Functions.f(t, b.contents, c.contents, d.contents))
          ->Int32.add(e.contents)
          ->Int32.add(k)
          ->Int32.add(w->Js.Array2.unsafe_get(t))

        e := d.contents
        d := c.contents
        c := Functions.rotl(b.contents, 30)
        b := a.contents
        a := temp
      })

      a := Int32.add(originalA, a.contents)
      b := Int32.add(originalB, b.contents)
      c := Int32.add(originalC, c.contents)
      d := Int32.add(originalD, d.contents)
      e := Int32.add(originalE, e.contents)
    }

    Belt.Array.make(20, 0x00)
    ->Utils.append32(a.contents, 0)
    ->Utils.append32(b.contents, 4)
    ->Utils.append32(c.contents, 8)
    ->Utils.append32(d.contents, 12)
    ->Utils.append32(e.contents, 16)
    ->Js.Array2.reduce((acc, curr) => acc ++ Js.String.fromCharCode(curr), "")
    ->Utils.stringToHex
  }
}

let make = message => message->Preprocess.pad->Process.make
