const { 
  setClipboardData, 
  getClipboardData, 
  isClipboardTextAvailable, 
  clearClipboard 
} = require('./index');

console.log('=== Architecture Demonstration ===');
console.log('This demo shows the separation between Win32 and Node-API layers\\n');

console.log('📋 1. Clear clipboard to start fresh...');
clearClipboard();
console.log(`   Has text: ${isClipboardTextAvailable()}`);

console.log('\\n📝 2. Setting data through Node-API layer...');
setClipboardData('Win32 ➡️ Node-API ➡️ JavaScript');
console.log(`   Has text: ${isClipboardTextAvailable()}`);

console.log('\\n📖 3. Reading data back through the layers...');
const data = getClipboardData();
console.log(`   Retrieved: "${data}"`);

console.log('\\n🏗️ Architecture Flow:');
console.log('   JavaScript Call');
console.log('   ⬇️');
console.log('   clipboard_api.cpp (Node-API bindings)');
console.log('   ⬇️');
console.log('   win32_clipboard.cpp (Pure Win32 API)');
console.log('   ⬇️');
console.log('   Windows Clipboard');

console.log('\\n✅ Demo completed! The separation allows for:');
console.log('   • Clean testing of Win32 functions');
console.log('   • Reusable Win32 code');
console.log('   • Clear error handling boundaries');
console.log('   • Easy maintenance and debugging');

console.log('\\nFinal clipboard content:');
console.log(`"${getClipboardData()}"`);