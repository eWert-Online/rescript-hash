module Functions = {
  let rotr = (x, n) => Int64.logor(Int64.shift_right_logical(x, n), Int64.shift_left(x, 64 - n))

  let change = (x, y, z) =>
    Int64.logand(x, y)->Int64.logxor(Int64.logand(Int64.logxor(x, Int64.neg(0x01L)), z))

  let majority = (x, y, z) =>
    Int64.logand(x, y)->Int64.logxor(Int64.logand(x, z))->Int64.logxor(Int64.logand(y, z))

  let sum0 = x => rotr(x, 28)->Int64.logxor(rotr(x, 34))->Int64.logxor(rotr(x, 39))

  let sum1 = x => rotr(x, 14)->Int64.logxor(rotr(x, 18))->Int64.logxor(rotr(x, 41))

  let sigma0 = x =>
    rotr(x, 1)->Int64.logxor(rotr(x, 8))->Int64.logxor(Int64.shift_right_logical(x, 7))

  let sigma1 = x =>
    rotr(x, 19)->Int64.logxor(rotr(x, 61))->Int64.logxor(Int64.shift_right_logical(x, 6))
}

module Utils = {
  let append64 = (hash, value, offset) => {
    for j in 0 to 7 {
      hash
      ->Js.Array2.unsafe_set(
        j + offset,
        Int64.shift_right_logical(value, 56 - j * 8)->Int64.logand(0xFFL)->Int64.to_int,
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
    0x428A2F98D728AE22L,
    0x7137449123EF65CDL,
    -0x4a3f043013b2c4d1L,
    -0x164a245a7e762444L,
    0x3956C25BF348B538L,
    0x59F111F1B605D019L,
    -0x6dc07d5b50e6b065L,
    -0x54e3a12a25927ee8L,
    -0x27f855675cfcfdbeL,
    0x12835B0145706FBEL,
    0x243185BE4EE4B28CL,
    0x550C7DC3D5FFB4E2L,
    0x72BE5D74F27B896FL,
    -0x7f214e01c4e9694fL,
    -0x6423f958da38edcbL,
    -0x3e640e8b3096d96cL,
    -0x1b64963e610eb52eL,
    -0x1041b879c7b0da1dL,
    0x0FC19DC68B8CD5B5L,
    0x240CA1CC77AC9C65L,
    0x2DE92C6F592B0275L,
    0x4A7484AA6EA6E483L,
    0x5CB0A9DCBD41FBD4L,
    0x76F988DA831153B5L,
    -0x67c1aead11992055L,
    -0x57ce3992d24bcdf0L,
    -0x4ffcd8376704dec1L,
    -0x40a680384110f11cL,
    -0x391ff40cc257703eL,
    -0x2a586eb86cf558dbL,
    0x06CA6351E003826FL,
    0x142929670A0E6E70L,
    0x27B70A8546D22FFCL,
    0x2E1B21385C26C926L,
    0x4D2C6DFC5AC42AEDL,
    0x53380D139D95B3DFL,
    0x650A73548BAF63DEL,
    0x766A0ABB3C77B2A8L,
    -0x7e3d36d1b812511aL,
    -0x6d8dd37aeb7dcac5L,
    -0x5d40175eb30efc9cL,
    -0x57e599b443bdcfffL,
    -0x3db4748f2f07686fL,
    -0x3893ae5cf9ab41d0L,
    -0x2e6d17e62910ade8L,
    -0x2966f9dbaa9a56f0L,
    -0xbf1ca7aa88edfd6L,
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
    -0x7b3787eb5e0f548eL,
    -0x7338fdf7e59bc614L,
    -0x6f410005dc9ce1d8L,
    -0x5baf9314217d4217L,
    -0x41065c084d3986ebL,
    -0x398e870d1c8dacd5L,
    -0x35d8c13115d99e64L,
    -0x2e794738de3f3df9L,
    -0x15258229321f14e2L,
    -0xa82b08011912e88L,
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
  ]
}

module Preprocess = {
  let pad = msg => {
    let size = ref(Js.String.length(msg) + 16 + 1)
    while mod(size.contents, 128) != 0 {
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
      bytes->Js.Array2.unsafe_set(Js.Array2.length(bytes) - i, land(va.contents, 255))

      va := asr(va.contents, 8)
    }
    bytes
  }
}

module Process = {
  let make = message => {
    let chunks = Js.Array2.length(message) / 128

    let a = ref(-0x344462a23efa6128L)
    let b = ref(0x629a292a367cd507L)
    let c = ref(-0x6ea6fea5cf8f22e9L)
    let d = ref(0x152fecd8f70e5939L)
    let e = ref(0x67332667ffc00b31L)
    let f = ref(-0x714bb57897a7eaefL)
    let g = ref(-0x24f3d1f29b067059L)
    let h = ref(0x47b5481dbefa4fa4L)

    for i in 0 to chunks - 1 {
      let w = Belt.Array.make(80, 0x00L)

      for t in 0 to 15 {
        for j in 0 to 7 {
          let result =
            Int64.shift_left(w->Js.Array2.unsafe_get(t), 8)->Int64.add(
              land(message->Js.Array2.unsafe_get(j + (i * 128 + 8 * t)), 0xff)->Int64.of_int,
            )

          w->Js.Array2.unsafe_set(t, result)->ignore
        }
      }

      for t in 16 to 79 {
        let t2 = w->Js.Array2.unsafe_get(t - 2)
        let t7 = w->Js.Array2.unsafe_get(t - 7)
        let t15 = w->Js.Array2.unsafe_get(t - 15)
        let t16 = w->Js.Array2.unsafe_get(t - 16)

        let result =
          Functions.sigma1(t2)->Int64.add(t7)->Int64.add(Functions.sigma0(t15))->Int64.add(t16)

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
          ->Int64.add(Functions.sum1(e.contents))
          ->Int64.add(Functions.change(e.contents, f.contents, g.contents))
          ->Int64.add(k)
          ->Int64.add(w->Js.Array2.unsafe_get(t))

        let temp2 = Int64.add(
          Functions.sum0(a.contents),
          Functions.majority(a.contents, b.contents, c.contents),
        )

        h := g.contents
        g := f.contents
        f := e.contents
        e := Int64.add(d.contents, temp1)
        d := c.contents
        c := b.contents
        b := a.contents
        a := Int64.add(temp1, temp2)
      })

      a := Int64.add(originalA, a.contents)
      b := Int64.add(originalB, b.contents)
      c := Int64.add(originalC, c.contents)
      d := Int64.add(originalD, d.contents)
      e := Int64.add(originalE, e.contents)
      f := Int64.add(originalF, f.contents)
      g := Int64.add(originalG, g.contents)
      h := Int64.add(originalH, h.contents)
    }

    Belt.Array.make(48, 0x00)
    ->Utils.append64(a.contents, 0)
    ->Utils.append64(b.contents, 8)
    ->Utils.append64(c.contents, 16)
    ->Utils.append64(d.contents, 24)
    ->Utils.append64(e.contents, 32)
    ->Utils.append64(f.contents, 40)
    ->Js.Array2.reduce((acc, curr) => acc ++ Js.String.fromCharCode(curr), "")
    ->Utils.stringToHex
  }
}

let make = message => message->Preprocess.pad->Process.make

let makeU = (. message) => make(message)
