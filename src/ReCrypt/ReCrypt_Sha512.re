module Preprocess = ReCrypt_Sha512_Preprocess;
module Process = ReCrypt_Sha512_Process;

let make = message => {
  let messageBytes = Bytes.of_string(message);
  let paddedMessage = Preprocess.pad(messageBytes);
  Process.make(paddedMessage);
};