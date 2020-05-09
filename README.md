# What is it?

Hashing Algorithms implemented in ReasonML based on:

- [RFC 1321](https://tools.ietf.org/html/rfc1321)
- [FIPS180-4](https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf)

# The following algorithms are currently supported

- [x] MD5
- [x] SHA-1
- [x] SHA-224
- [x] SHA-256
- [x] SHA-384
- [x] SHA-512

# How do I install it?

```
yarn add @space-labs/re-crypt
```

or

```
npm install @space-labs/re-crypt --save
```

Then add `@space-labs/re-crypt` as a dependency to `bsconfig.json`:

```diff
"bs-dependencies": [
+  "@space-labs/re-crypt"
]
```

# How do I use it?

### MD5

```reason
let hash = ReCrypt.MD5.make("unicorn");
/* 1abcb33beeb811dca15f0ac3e47b88d9 */
```

### SHA-1

```reason
let hash = ReCrypt.Sha1.make("unicorn");
/* 84de6753b298abd027fcd1d790eade2413eafb5a */
```

### SHA-224

```reason
let hash = ReCrypt.Sha224.make("unicorn");
/* 983d515094574856a57db3a13741f0a65509bb640bfa551e78fa01d9 */
```

### SHA-256

```reason
let hash = ReCrypt.Sha256.make("unicorn");
/* c6cb50e7eea0df1fd3eaf52ada2358f5423afd7c0b5ee2395231a9b3208ffcaf */
```

### SHA-384

```reason
let hash = ReCrypt.Sha384.make("unicorn");
/* de41efa2be0844783ea107630a79246fb1f7b3ab97b35c5e4b70130804f876f64b645c1064a775507a7ac3be457539f2 */
```

### SHA-512

```reason
let hash = ReCrypt.Sha512.make("unicorn");
/* e233b19aabc7d5e53826fb734d1222f1f0444c3a3fc67ff4af370a66e7cadd2cb24009f1bc86f0bed12ca5fcb226145ad10fc5f650f6ef0959f8aadc5a594b27 */
```
