#ifndef WIN32_CLIPBOARD_H
#define WIN32_CLIPBOARD_H

#include <windows.h>
#include <string>

namespace Win32Clipboard {

    // Result structure for clipboard operations
    struct ClipboardResult {
        bool success;
        std::string error;
        std::string data;
    };

    // Win32 clipboard functions
    ClipboardResult SetText(const std::string& text);
    ClipboardResult GetText();
    
    // Helper functions
    bool IsTextAvailable();
    void ClearClipboard();
}

#endif // WIN32_CLIPBOARD_H