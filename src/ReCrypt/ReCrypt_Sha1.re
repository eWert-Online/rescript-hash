module Preprocess = ReCrypt_Sha1_Preprocess;
module Process = ReCrypt_Sha1_Process;

let make = message => {
  message->Preprocess.pad->Process.make;
};
