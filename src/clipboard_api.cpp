#include "clipboard_api.h"

Napi::Value SetClipboardData(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    // Check if we have the required argument
    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Wrong number of arguments. Expected 1 argument (text)")
            .ThrowAsJavaScriptException();
        return env.Null();
    }

    // Check if the argument is a string
    if (!info[0].IsString()) {
        Napi::TypeError::New(env, "Argument must be a string")
            .ThrowAsJavaScriptException();
        return env.Null();
    }

    std::string text = info[0].As<Napi::String>().Utf8Value();

    // Use the Win32 clipboard function
    Win32Clipboard::ClipboardResult result = Win32Clipboard::SetText(text);

    if (!result.success) {
        Napi::Error::New(env, result.error).ThrowAsJavaScriptException();
        return env.Null();
    }

    return Napi::Boolean::New(env, true);
}

Napi::Value GetClipboardData(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    // Use the Win32 clipboard function
    Win32Clipboard::ClipboardResult result = Win32Clipboard::GetText();

    if (!result.success) {
        Napi::Error::New(env, result.error).ThrowAsJavaScriptException();
        return env.Null();
    }

    return Napi::String::New(env, result.data);
}

Napi::Value IsClipboardTextAvailable(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    
    bool isAvailable = Win32Clipboard::IsTextAvailable();
    return Napi::Boolean::New(env, isAvailable);
}

Napi::Value ClearClipboard(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    
    Win32Clipboard::ClearClipboard();
    return Napi::Boolean::New(env, true);
}