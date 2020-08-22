let pad = msg => {
  let size = ref(Js.String.length(msg) + 8 + 1);
  while (size^ mod 64 != 0) {
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
  for (i in 0 to 7) {
    bytes->Belt.Array.set(i + (size^ - 8), va^ land 255)->ignore;
    va := va^ lsr 8;
  };

  bytes;
};
