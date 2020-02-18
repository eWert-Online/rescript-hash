open Jest;
open Expect;
open ReCrypt;

describe("Sha512", () => {
  test("make(\"unicorn\")", () =>
    expect(Sha512.make("unicorn"))
    |> toBe(
         "e233b19aabc7d5e53826fb734d1222f1f0444c3a3fc67ff4af370a66e7cadd2cb24009f1bc86f0bed12ca5fcb226145ad10fc5f650f6ef0959f8aadc5a594b27",
       )
  );
  test("make(\"\")", () =>
    expect(Sha512.make(""))
    |> toBe(
         "cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e",
       )
  );
  test("make(\"123\")", () =>
    expect(Sha512.make("123"))
    |> toBe(
         "3c9909afec25354d551dae21590bb26e38d53f2173b8d3dc3eee4c047e7ab1c1eb8b85103e3be7ba613b31bb5c9c36214dc9f14a42fd7a2fdb84856bca5c44c2",
       )
  );
});