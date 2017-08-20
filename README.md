# balanced-match
A N-API version of https://github.com/juliangruber/balanced-match

# Reuirements
Node.js v8 

# Install
```
npm install git+https://github.com/shivanth/balanced-match.git
```
# Usage

```javascript

var balanced = require('balanced-match-native');
balanced('{', '}',"1{234}5")
//{start:1, end:5,pre:"1", post:"5",body:"234"}

balanced('{{{', '}}',"123{{{234}}")
// {start:3, end:9,pre:"123", post:"",body:"234"}

```
# Note
Regex is not supported yet for the first two arguments of balanced.
