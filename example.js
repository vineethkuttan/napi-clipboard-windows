const { setClipboardData, getClipboardData, isClipboardTextAvailable, clearClipboard } = require('./index');

console.log('=== NAPI Clipboard Demo ===\n');

// Example 1: Basic clipboard operations
console.log('1. Setting text to clipboard...');
setClipboardData('Hello from Node.js NAPI!');
console.log('   ✓ Text set successfully');

console.log('2. Reading from clipboard...');
const text = getClipboardData();
console.log(`   ✓ Retrieved: "${text}"\n`);

// Example 2: Working with existing clipboard content
console.log('3. Current clipboard content:');
const currentContent = getClipboardData();
console.log(`   "${currentContent}"\n`);

// Example 3: Appending to clipboard
console.log('4. Appending to existing content...');
const newContent = currentContent + ' - Modified by NAPI!';
setClipboardData(newContent);
console.log('   ✓ Content updated');

console.log('5. Final clipboard content:');
const finalContent = getClipboardData();
console.log(`   "${finalContent}"\n`);

// Example 4: Working with special characters
console.log('6. Testing with special characters...');
const specialText = 'Special: àáâãäåæçèéêë ñ 中文 🎉🚀💻';
setClipboardData(specialText);
const retrievedSpecial = getClipboardData();
console.log(`   Set: "${specialText}"`);
console.log(`   Got: "${retrievedSpecial}"`);
console.log(`   ✓ Match: ${specialText === retrievedSpecial ? 'Yes' : 'No'}\n`);

console.log('Demo completed! You can now paste in any application to see the final result.');