module Preprocess = ReCrypt_MD5_Preprocess;
module Process = ReCrypt_MD5_Process;

let make = message => {
  message->Preprocess.pad->Process.make;
};
