#include <napi.h>
#include "clipboard_api.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  // Export the clipboard functions with explicit function pointer casting
  exports["setClipboardData"] = Napi::Function::New(env, static_cast<Napi::Value(*)(const Napi::CallbackInfo&)>(SetClipboardData));
  exports["getClipboardData"] = Napi::Function::New(env, static_cast<Napi::Value(*)(const Napi::CallbackInfo&)>(GetClipboardData));
  exports["isClipboardTextAvailable"] = Napi::Function::New(env, static_cast<Napi::Value(*)(const Napi::CallbackInfo&)>(IsClipboardTextAvailable));
  exports["clearClipboard"] = Napi::Function::New(env, static_cast<Napi::Value(*)(const Napi::CallbackInfo&)>(ClearClipboard));
  return exports;
}

NODE_API_MODULE(napi_clipboard_addon, InitAll)