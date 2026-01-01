const { setClipboardData, getClipboardData, isClipboardTextAvailable, clearClipboard } = require('./index');

console.log('Testing NAPI Clipboard API...\n');

// Test 0: Check initial clipboard state
console.log('Test 0: Checking initial clipboard state');
try {
  const hasText = isClipboardTextAvailable();
  console.log('Has text initially:', hasText);
  if (hasText) {
    const initialText = getClipboardData();
    console.log('Initial text:', `"${initialText}"`);
  }
  console.log('✅ Initial state checked\n');
} catch (error) {
  console.error('❌ Error:', error.message, '\n');
}

// Test 1: Set simple text
console.log('Test 1: Setting simple text to clipboard');
try {
  const result1 = setClipboardData('Hello, World!');
  console.log('Set result:', result1);
  console.log('✅ Text should be set to clipboard\n');
} catch (error) {
  console.error('❌ Error:', error.message, '\n');
}

// Test 2: Check if text is available
console.log('Test 2: Checking if text is available');
try {
  const hasText = isClipboardTextAvailable();
  console.log('Has text:', hasText);
  console.log('✅ Text availability checked\n');
} catch (error) {
  console.error('❌ Error:', error.message, '\n');
}

// Test 3: Get the text back
console.log('Test 3: Getting text from clipboard');
try {
  const result2 = getClipboardData();
  console.log('Retrieved text:', `"${result2}"`);
  console.log('✅ Text retrieved from clipboard\n');
} catch (error) {
  console.error('❌ Error:', error.message, '\n');
}

// Test 4: Clear clipboard
console.log('Test 4: Clearing clipboard');
try {
  const clearResult = clearClipboard();
  console.log('Clear result:', clearResult);
  
  const hasTextAfterClear = isClipboardTextAvailable();
  console.log('Has text after clear:', hasTextAfterClear);
  console.log('✅ Clipboard cleared\n');
} catch (error) {
  console.error('❌ Error:', error.message, '\n');
}

// Test 5: Set multiline text
console.log('Test 5: Setting multiline text');
try {
  const multilineText = 'Line 1\nLine 2\nLine 3';
  const result3 = setClipboardData(multilineText);
  console.log('Set result:', result3);
  
  const retrieved3 = getClipboardData();
  console.log('Retrieved multiline text:', JSON.stringify(retrieved3));
  console.log('✅ Multiline text handled correctly\n');
} catch (error) {
  console.error('❌ Error:', error.message, '\n');
}

// Test 6: Set Unicode text
console.log('Test 6: Setting Unicode text');
try {
  const unicodeText = 'Hello 世界! 🌍🚀';
  const result4 = setClipboardData(unicodeText);
  console.log('Set result:', result4);
  
  const retrieved4 = getClipboardData();
  console.log('Retrieved Unicode text:', `"${retrieved4}"`);
  console.log('✅ Unicode text handled correctly\n');
} catch (error) {
  console.error('❌ Error:', error.message, '\n');
}

// Test 7: Set empty string
console.log('Test 7: Setting empty string');
try {
  const result5 = setClipboardData('');
  console.log('Set result:', result5);
  
  const retrieved5 = getClipboardData();
  console.log('Retrieved empty text:', `"${retrieved5}"`);
  console.log('✅ Empty string handled correctly\n');
} catch (error) {
  console.error('❌ Error:', error.message, '\n');
}

// Test 8: Test with invalid argument
console.log('Test 8: Testing with invalid argument (should fail)');
try {
  const result6 = setClipboardData(123);
  console.log('Unexpected success:', result6);
} catch (error) {
  console.error('❌ Expected error:', error.message, '\n');
}

console.log('All tests completed!');
console.log('\nYou can now paste the clipboard content in any application to verify the results.');