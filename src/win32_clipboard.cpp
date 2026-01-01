#include "win32_clipboard.h"
#include <vector>

namespace Win32Clipboard {

    ClipboardResult SetText(const std::string& text) {
        ClipboardResult result = { false, "", "" };

        // Open the clipboard
        if (!OpenClipboard(NULL)) {
            DWORD error = GetLastError();
            result.error = "Failed to open clipboard. Error code: " + std::to_string(error);
            return result;
        }

        // Empty the clipboard
        if (!EmptyClipboard()) {
            CloseClipboard();
            DWORD error = GetLastError();
            result.error = "Failed to empty clipboard. Error code: " + std::to_string(error);
            return result;
        }

        // Convert UTF-8 string to wide string for Windows
        int wideSize = MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, NULL, 0);
        if (wideSize == 0) {
            CloseClipboard();
            DWORD error = GetLastError();
            result.error = "Failed to convert text to wide string. Error code: " + std::to_string(error);
            return result;
        }

        // Allocate memory for the clipboard data
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, wideSize * sizeof(wchar_t));
        if (hMem == NULL) {
            CloseClipboard();
            DWORD error = GetLastError();
            result.error = "Failed to allocate memory. Error code: " + std::to_string(error);
            return result;
        }

        // Lock the memory and copy the string
        wchar_t* pMem = static_cast<wchar_t*>(GlobalLock(hMem));
        if (pMem == NULL) {
            GlobalFree(hMem);
            CloseClipboard();
            DWORD error = GetLastError();
            result.error = "Failed to lock memory. Error code: " + std::to_string(error);
            return result;
        }

        MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, pMem, wideSize);
        GlobalUnlock(hMem);

        // Set the clipboard data
        if (SetClipboardData(CF_UNICODETEXT, hMem) == NULL) {
            GlobalFree(hMem);
            CloseClipboard();
            DWORD error = GetLastError();
            result.error = "Failed to set clipboard data. Error code: " + std::to_string(error);
            return result;
        }

        // Close the clipboard (memory is now owned by the system)
        CloseClipboard();

        result.success = true;
        return result;
    }

    ClipboardResult GetText() {
        ClipboardResult result = { false, "", "" };

        // Open the clipboard
        if (!OpenClipboard(NULL)) {
            DWORD error = GetLastError();
            result.error = "Failed to open clipboard. Error code: " + std::to_string(error);
            return result;
        }

        // Check if clipboard contains text data
        if (!IsClipboardFormatAvailable(CF_UNICODETEXT)) {
            CloseClipboard();
            // Return empty string if no text data available (not an error)
            result.success = true;
            result.data = "";
            return result;
        }

        // Get the clipboard data
        HANDLE hData = GetClipboardData(CF_UNICODETEXT);
        if (hData == NULL) {
            CloseClipboard();
            DWORD error = GetLastError();
            result.error = "Failed to get clipboard data. Error code: " + std::to_string(error);
            return result;
        }

        // Lock the memory
        wchar_t* pData = static_cast<wchar_t*>(GlobalLock(hData));
        if (pData == NULL) {
            CloseClipboard();
            DWORD error = GetLastError();
            result.error = "Failed to lock clipboard memory. Error code: " + std::to_string(error);
            return result;
        }

        // Convert wide string to UTF-8
        int utf8Size = WideCharToMultiByte(CP_UTF8, 0, pData, -1, NULL, 0, NULL, NULL);
        if (utf8Size == 0) {
            GlobalUnlock(hData);
            CloseClipboard();
            DWORD error = GetLastError();
            result.error = "Failed to convert wide string to UTF-8. Error code: " + std::to_string(error);
            return result;
        }

        std::string textResult(utf8Size - 1, '\0'); // -1 to exclude null terminator
        WideCharToMultiByte(CP_UTF8, 0, pData, -1, &textResult[0], utf8Size, NULL, NULL);

        // Unlock and close
        GlobalUnlock(hData);
        CloseClipboard();

        result.success = true;
        result.data = textResult;
        return result;
    }

    bool IsTextAvailable() {
        return IsClipboardFormatAvailable(CF_UNICODETEXT) != 0;
    }

    void ClearClipboard() {
        if (OpenClipboard(NULL)) {
            EmptyClipboard();
            CloseClipboard();
        }
    }

}