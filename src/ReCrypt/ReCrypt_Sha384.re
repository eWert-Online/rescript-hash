module Preprocess = ReCrypt_Sha384_Preprocess;
module Process = ReCrypt_Sha384_Process;

let make = message => {
  let messageBytes = Bytes.of_string(message);
  let paddedMessage = Preprocess.pad(messageBytes);
  Process.make(paddedMessage);
};