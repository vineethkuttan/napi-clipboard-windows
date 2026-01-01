# NAPI Clipboard API for Windows

A Node.js Native Addon using NAPI and C++ that provides Windows clipboard functionality with a clean separation between Win32 APIs and Node.js bindings.

## Architecture

The project is structured with clear separation of concerns:

- **`win32_clipboard.cpp/h`** - Pure Win32 API implementation for clipboard operations
- **`clipboard_api.cpp/h`** - Node-API bindings that interface with JavaScript
- **`main.cpp`** - Module initialization and exports

## Features

- Set text data to Windows clipboard
- Get text data from Windows clipboard
- Support for Unicode text (UTF-8)
- Support for multiline text
- Proper error handling with meaningful messages
- Windows-specific implementation using Win32 API

## Prerequisites

- Node.js (v14 or higher)
- Windows (this addon is Windows-specific)
- Visual Studio Build Tools or Visual Studio with C++ support
- Python (for node-gyp)

### Visual Studio Requirements

This project requires Visual Studio 2022 build tools. The build process uses:

```bash
yarn build  # Uses: npx node-gyp rebuild --msvs_version=2022
```

**Important:** If you encounter build errors, it's likely due to Visual Studio version detection issues. The `--msvs_version=2022` flag ensures:
- Correct toolchain compatibility
- Proper Windows SDK linking
- ABI compatibility with Node.js

**Troubleshooting Build Issues:**
- Make sure Visual Studio 2022 Build Tools are installed
- Verify Windows 10/11 SDK is available
- If auto-detection fails, the explicit version flag prevents build failures

## Installation

```bash
yarn install
yarn build
```

## Usage

```javascript
const { setClipboardData, getClipboardData, isClipboardTextAvailable, clearClipboard } = require('./index');

// Set text to clipboard
setClipboardData('Hello, World!');
console.log('Text set to clipboard');

// Get text from clipboard
const text = getClipboardData();
console.log('Retrieved text:', text); // "Hello, World!"

// Check if text is available
const hasText = isClipboardTextAvailable();
console.log('Has text:', hasText); // true

// Clear clipboard
clearClipboard();
console.log('Clipboard cleared');

// Unicode support
setClipboardData('Hello 世界! 🌍🚀');
const unicodeText = getClipboardData();
console.log(unicodeText); // "Hello 世界! 🌍🚀"

// Multiline text
setClipboardData('Line 1\nLine 2\nLine 3');
const multilineText = getClipboardData();
console.log(multilineText); // "Line 1\nLine 2\nLine 3"
```

## API Reference

### `setClipboardData(text)`

Sets text data to the Windows clipboard.

**Parameters:**
- `text` (string, required): The text to set to the clipboard

**Returns:**
- `undefined`

**Throws:**
- `TypeError`: If the argument is not a string
- `Error`: If clipboard operations fail

### `getClipboardData()`

Retrieves text data from the Windows clipboard.

**Parameters:**
None

**Returns:**
- `string`: The text content from the clipboard, or empty string if no text data is available

**Throws:**
- `Error`: If clipboard operations fail

### `isClipboardTextAvailable()`

Checks if text data is available in the clipboard.

**Parameters:**
None

**Returns:**
- `boolean`: `true` if text data is available, `false` otherwise

### `clearClipboard()`

Clears all data from the clipboard.

**Parameters:**
None

**Returns:**
- `undefined`

**Throws:**
- `Error`: If clipboard operations fail

## Development

### Building with Visual Studio 2022

You can also develop using Visual Studio 2022 IDE:

1. **Generate project files:** `yarn build` (creates `build/binding.sln`)
2. **Open in Visual Studio:** Open `build/binding.sln`
3. **Build in IDE:** Build → Build Solution
4. **Debugging:** Attach to Node.js process for C++ debugging

### Available Scripts

- `yarn build` - Build the native addon
- `yarn clean` - Clean build artifacts
- `yarn test` - Run comprehensive tests
- `yarn example` - Run usage examples
- `yarn demo:architecture` - Demonstrate architecture separation

## Testing

```bash
yarn test
```

This will run various tests including:
- Setting simple text
- Getting text back
- Multiline text handling
- Unicode text support
- Empty string handling
- Utility functions (check availability, clear clipboard)
- Error cases

## Error Handling

The functions throw JavaScript exceptions for:
- Invalid arguments (non-string input for setClipboardData)
- Clipboard access failures (clipboard locked by another process)
- Memory allocation failures
- Text encoding/decoding failures

## Implementation Details

- Uses Win32 API functions: `OpenClipboard`, `EmptyClipboard`, `SetClipboardData`, `GetClipboardData`
- Handles Unicode text using `CF_UNICODETEXT` format
- Properly converts between UTF-8 (Node.js) and UTF-16 (Windows)
- Manages clipboard memory allocation and cleanup
- Thread-safe clipboard operations
- Clean separation between Win32 implementation and Node-API bindings

## License

MIT