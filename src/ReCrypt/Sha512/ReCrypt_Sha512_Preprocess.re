let pad = msg => {
  let size = ref(Js.String.length(msg) + 16 + 1);
  while (size^ mod 128 != 0) {
    size := size^ + 1;
  };

  let length = Js.String.length(msg);

  let bytes =
    Belt.Array.makeBy(size^, index =>
      switch (index) {
      | i when i < length =>
        msg->(Js.String2.charCodeAt(i))->Belt.Int.fromFloat
      | i when i == length => 0x80
      | _ => 0x00
      }
    );

  let va = ref(length * 8);
  for (i in 1 to 15) {
    let _ =
      bytes->Belt.Array.set(Belt.Array.length(bytes) - i, va^ land 255);

    va := va^ asr 8;
  };
  bytes;
};
