const addon = require('./build/Release/napi_clipboard_addon.node');

module.exports = {
  setClipboardData: addon.setClipboardData,
  getClipboardData: addon.getClipboardData,
  isClipboardTextAvailable: addon.isClipboardTextAvailable,
  clearClipboard: addon.clearClipboard
};