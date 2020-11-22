module Functions = {
  let rotr = (x, n) => Int64.logor(Int64.shift_right_logical(x, n), Int64.shift_left(x, 64 - n))

  let change = (x, y, z) => Int64.logand(x, y)->Int64.logxor(Int64.logand(Int64.lognot(x), z))

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
      ->Belt.Array.set(
        j + offset,
        Int64.shift_right_logical(value, 56 - j * 8)->Int64.logand(0xFFL)->Int64.to_int,
      )
      ->ignore
    }
    hash
  }

  let stringToHex = input => {
    let hex = "0123456789abcdef"
    input->Js.String2.split("")->Belt.Array.reduce("", (acc, curr) => {
      let charCode = curr->Js.String2.charCodeAt(0)->Belt.Int.fromFloat

      acc ++
      (hex->Js.String2.charAt(land(lsr(charCode, 4), 0x0F)) ++
      hex->Js.String2.charAt(land(charCode, 0x0F)))
    })
  }
}

module Constants = {
  let k = [
    0x428a2f98d728ae22L,
    0x7137449123ef65cdL,
    0xb5c0fbcfec4d3b2fL,
    0xe9b5dba58189dbbcL,
    0x3956c25bf348b538L,
    0x59f111f1b605d019L,
    0x923f82a4af194f9bL,
    0xab1c5ed5da6d8118L,
    0xd807aa98a3030242L,
    0x12835b0145706fbeL,
    0x243185be4ee4b28cL,
    0x550c7dc3d5ffb4e2L,
    0x72be5d74f27b896fL,
    0x80deb1fe3b1696b1L,
    0x9bdc06a725c71235L,
    0xc19bf174cf692694L,
    0xe49b69c19ef14ad2L,
    0xefbe4786384f25e3L,
    0x0fc19dc68b8cd5b5L,
    0x240ca1cc77ac9c65L,
    0x2de92c6f592b0275L,
    0x4a7484aa6ea6e483L,
    0x5cb0a9dcbd41fbd4L,
    0x76f988da831153b5L,
    0x983e5152ee66dfabL,
    0xa831c66d2db43210L,
    0xb00327c898fb213fL,
    0xbf597fc7beef0ee4L,
    0xc6e00bf33da88fc2L,
    0xd5a79147930aa725L,
    0x06ca6351e003826fL,
    0x142929670a0e6e70L,
    0x27b70a8546d22ffcL,
    0x2e1b21385c26c926L,
    0x4d2c6dfc5ac42aedL,
    0x53380d139d95b3dfL,
    0x650a73548baf63deL,
    0x766a0abb3c77b2a8L,
    0x81c2c92e47edaee6L,
    0x92722c851482353bL,
    0xa2bfe8a14cf10364L,
    0xa81a664bbc423001L,
    0xc24b8b70d0f89791L,
    0xc76c51a30654be30L,
    0xd192e819d6ef5218L,
    0xd69906245565a910L,
    0xf40e35855771202aL,
    0x106aa07032bbd1b8L,
    0x19a4c116b8d2d0c8L,
    0x1e376c085141ab53L,
    0x2748774cdf8eeb99L,
    0x34b0bcb5e19b48a8L,
    0x391c0cb3c5c95a63L,
    0x4ed8aa4ae3418acbL,
    0x5b9cca4f7763e373L,
    0x682e6ff3d6b2b8a3L,
    0x748f82ee5defb2fcL,
    0x78a5636f43172f60L,
    0x84c87814a1f0ab72L,
    0x8cc702081a6439ecL,
    0x90befffa23631e28L,
    0xa4506cebde82bde9L,
    0xbef9a3f7b2c67915L,
    0xc67178f2e372532bL,
    0xca273eceea26619cL,
    0xd186b8c721c0c207L,
    0xeada7dd6cde0eb1eL,
    0xf57d4f7fee6ed178L,
    0x06f067aa72176fbaL,
    0x0a637dc5a2c898a6L,
    0x113f9804bef90daeL,
    0x1b710b35131c471bL,
    0x28db77f523047d84L,
    0x32caab7b40c72493L,
    0x3c9ebe0a15c9bebcL,
    0x431d67c49c100d4cL,
    0x4cc5d4becb3e42b6L,
    0x597f299cfc657e2aL,
    0x5fcb6fab3ad6faecL,
    0x6c44198c4a475817L,
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
      | i when i < length => msg->Js.String2.charCodeAt(i)->Belt.Int.fromFloat
      | i when i == length => 0x80
      | _ => 0x00
      }
    )

    let va = ref(length * 8)
    for i in 1 to 15 {
      let _ = bytes->Belt.Array.set(Belt.Array.length(bytes) - i, land(va.contents, 255))

      va := asr(va.contents, 8)
    }
    bytes
  }
}

module Process = {
  let make = message => {
    let chunks = Belt.Array.length(message) / 128

    let a = ref(0x6a09e667f3bcc908L)
    let b = ref(0xbb67ae8584caa73bL)
    let c = ref(0x3c6ef372fe94f82bL)
    let d = ref(0xa54ff53a5f1d36f1L)
    let e = ref(0x510e527fade682d1L)
    let f = ref(0x9b05688c2b3e6c1fL)
    let g = ref(0x1f83d9abfb41bd6bL)
    let h = ref(0x5be0cd19137e2179L)

    for i in 0 to chunks - 1 {
      let w = Belt.Array.make(80, 0x00L)

      for t in 0 to 15 {
        for j in 0 to 7 {
          let result =
            Int64.shift_left(w->Belt.Array.get(t)->Belt.Option.getWithDefault(0x00L), 8)->Int64.add(
              land(
                message->Belt.Array.get(j + (i * 128 + 8 * t))->Belt.Option.getWithDefault(0x00),
                0xff,
              )->Int64.of_int,
            )

          w->Belt.Array.set(t, result)->ignore
        }
      }

      for t in 16 to 79 {
        let t2 = w->Belt.Array.get(t - 2)->Belt.Option.getWithDefault(0x00L)
        let t7 = w->Belt.Array.get(t - 7)->Belt.Option.getWithDefault(0x00L)
        let t15 = w->Belt.Array.get(t - 15)->Belt.Option.getWithDefault(0x00L)
        let t16 = w->Belt.Array.get(t - 16)->Belt.Option.getWithDefault(0x00L)

        let result =
          Functions.sigma1(t2)->Int64.add(t7)->Int64.add(Functions.sigma0(t15))->Int64.add(t16)

        w->Belt.Array.set(t, result)->ignore
      }

      let originalA = a.contents
      let originalB = b.contents
      let originalC = c.contents
      let originalD = d.contents
      let originalE = e.contents
      let originalF = f.contents
      let originalG = g.contents
      let originalH = h.contents

      Constants.k->Belt.Array.forEachWithIndex((t, k) => {
        let temp1 =
          h.contents
          ->Int64.add(Functions.sum1(e.contents))
          ->Int64.add(Functions.change(e.contents, f.contents, g.contents))
          ->Int64.add(k)
          ->Int64.add(w->Belt.Array.get(t)->Belt.Option.getWithDefault(0x00L))

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

    Belt.Array.make(64, 0x00)
    ->Utils.append64(a.contents, 0)
    ->Utils.append64(b.contents, 8)
    ->Utils.append64(c.contents, 16)
    ->Utils.append64(d.contents, 24)
    ->Utils.append64(e.contents, 32)
    ->Utils.append64(f.contents, 40)
    ->Utils.append64(g.contents, 48)
    ->Utils.append64(h.contents, 56)
    ->Belt.Array.reduce("", (acc, curr) => acc ++ Js.String.fromCharCode(curr))
    ->Utils.stringToHex
  }
}

let make = message => message->Preprocess.pad->Process.make
