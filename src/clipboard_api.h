#ifndef CLIPBOARD_API_H
#define CLIPBOARD_API_H

#include <napi.h>
#include "win32_clipboard.h"

// Function declarations for Node-API clipboard operations
Napi::Value SetClipboardData(const Napi::CallbackInfo& info);
Napi::Value GetClipboardData(const Napi::CallbackInfo& info);
Napi::Value IsClipboardTextAvailable(const Napi::CallbackInfo& info);
Napi::Value ClearClipboard(const Napi::CallbackInfo& info);

#endif // CLIPBOARD_API_H