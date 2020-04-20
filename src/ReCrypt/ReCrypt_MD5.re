module Preprocess = ReCrypt_MD5_Preprocess;
module Process = ReCrypt_MD5_Process;

let make = message => {
  let messageBytes = Bytes.of_string(message);
  let paddedMessage = Preprocess.pad(messageBytes);
  Process.make(paddedMessage);
};