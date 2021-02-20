module Functions = {
  let rotr = (x, n) => Int32.logor(Int32.shift_right_logical(x, n), Int32.shift_left(x, 64 - n))

  let change = (x, y, z) => Int32.logand(x, y)->Int32.logxor(Int32.logand(Int32.lognot(x), z))

  let majority = (x, y, z) =>
    Int32.logand(x, y)->Int32.logxor(Int32.logand(x, z))->Int32.logxor(Int32.logand(y, z))

  let sum0 = x => rotr(x, 2)->Int32.logxor(rotr(x, 13))->Int32.logxor(rotr(x, 22))

  let sum1 = x => rotr(x, 6)->Int32.logxor(rotr(x, 11))->Int32.logxor(rotr(x, 25))

  let sigma0 = x =>
    rotr(x, 7)->Int32.logxor(rotr(x, 18))->Int32.logxor(Int32.shift_right_logical(x, 3))

  let sigma1 = x =>
    rotr(x, 17)->Int32.logxor(rotr(x, 19))->Int32.logxor(Int32.shift_right_logical(x, 10))
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
    0x428a2f98l,
    0x71374491l,
    -0x4a3f0431l,
    -0x164a245bl,
    0x3956c25bl,
    0x59f111f1l,
    -0x6dc07d5cl,
    -0x54e3a12bl,
    -0x27f85568l,
    0x12835b01l,
    0x243185bel,
    0x550c7dc3l,
    0x72be5d74l,
    -0x7f214e02l,
    -0x6423f959l,
    -0x3e640e8cl,
    -0x1b64963fl,
    -0x1041b87al,
    0x0fc19dc6l,
    0x240ca1ccl,
    0x2de92c6fl,
    0x4a7484aal,
    0x5cb0a9dcl,
    0x76f988dal,
    -0x67c1aeael,
    -0x57ce3993l,
    -0x4ffcd838l,
    -0x40a68039l,
    -0x391ff40dl,
    -0x2a586eb9l,
    0x06ca6351l,
    0x14292967l,
    0x27b70a85l,
    0x2e1b2138l,
    0x4d2c6dfcl,
    0x53380d13l,
    0x650a7354l,
    0x766a0abbl,
    -0x7e3d36d2l,
    -0x6d8dd37bl,
    -0x5d40175fl,
    -0x57e599b5l,
    -0x3db47490l,
    -0x3893ae5dl,
    -0x2e6d17e7l,
    -0x2966f9dcl,
    -0xbf1ca7bl,
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
    -0x7b3787ecl,
    -0x7338fdf8l,
    -0x6f410006l,
    -0x5baf9315l,
    -0x41065c09l,
    -0x398e870el,
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

    let a = ref(0x6a09e667l)
    let b = ref(-0x4498517bl)
    let c = ref(0x3c6ef372l)
    let d = ref(-0x5ab00ac6l)
    let e = ref(0x510e527fl)
    let f = ref(-0x64fa9774l)
    let g = ref(0x1f83d9abl)
    let h = ref(0x5be0cd19l)

    for i in 0 to chunks - 1 {
      let w = Belt.Array.make(64, 0x00l)

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

      for t in 16 to 63 {
        let t2 = w->Js.Array2.unsafe_get(t - 2)
        let t7 = w->Js.Array2.unsafe_get(t - 7)
        let t15 = w->Js.Array2.unsafe_get(t - 15)
        let t16 = w->Js.Array2.unsafe_get(t - 16)

        let result =
          Functions.sigma1(t2)->Int32.add(t7)->Int32.add(Functions.sigma0(t15))->Int32.add(t16)

        w->Js.Array2.unsafe_set(t, result)->ignore
      }

      let originalA = a.contents
      let originalB = b.contents
      let originalC = c.contents
      let originalD = d.contents
      let originalE = e.contents
      let originalF = f.contents
      let originalG = g.contents
      let originalH = h.contents

      Constants.k->Js.Array2.forEachi((k, t) => {
        let temp1 =
          h.contents
          ->Int32.add(Functions.sum1(e.contents))
          ->Int32.add(Functions.change(e.contents, f.contents, g.contents))
          ->Int32.add(k)
          ->Int32.add(w->Js.Array2.unsafe_get(t))

        let temp2 = Int32.add(
          Functions.sum0(a.contents),
          Functions.majority(a.contents, b.contents, c.contents),
        )

        h := g.contents
        g := f.contents
        f := e.contents
        e := Int32.add(d.contents, temp1)
        d := c.contents
        c := b.contents
        b := a.contents
        a := Int32.add(temp1, temp2)
      })

      a := Int32.add(originalA, a.contents)
      b := Int32.add(originalB, b.contents)
      c := Int32.add(originalC, c.contents)
      d := Int32.add(originalD, d.contents)
      e := Int32.add(originalE, e.contents)
      f := Int32.add(originalF, f.contents)
      g := Int32.add(originalG, g.contents)
      h := Int32.add(originalH, h.contents)
    }

    Belt.Array.make(32, 0x00)
    ->Utils.append32(a.contents, 0)
    ->Utils.append32(b.contents, 4)
    ->Utils.append32(c.contents, 8)
    ->Utils.append32(d.contents, 12)
    ->Utils.append32(e.contents, 16)
    ->Utils.append32(f.contents, 20)
    ->Utils.append32(g.contents, 24)
    ->Utils.append32(h.contents, 28)
    ->Js.Array2.reduce((acc, curr) => acc ++ Js.String.fromCharCode(curr), "")
    ->Utils.stringToHex
  }
}

let make = message => message->Preprocess.pad->Process.make
