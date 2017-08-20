var chai = require('chai');
var assert = chai.assert

describe('Import Library', function(){
         it('Should require the node lib directly', function(done){
             var matching = require('../build/Release/balanced-match');
             assert.isDefined(matching, 'Failed direct node lib import');
             done();
         }),
         it('Should require the binrary', function(done){
             var matching = require('../index.js');
             assert.isDefined(matching, 'Failed direct node lib import');
             done();
         })});

describe('Valid ', function(){
    it('Should evaluate single delimiters correctly', function(done){
        var balanced = require('../index.js');
        //console.log(matching);
        assert.deepEqual(balanced('{', '}',"1{234}5"),{start:1, end:5,pre:"1", post:"5",body:"234"});
        done();
    })
    it('Should evaluate multiple delimiters correctly', function(done){
        var balanced = require('../index.js');
        //console.log(matching);
        assert.deepEqual(balanced('{{{', '}}',"1{{{234}}5"),{start:1, end:7,pre:"1", post:"5",body:"234"});
        done();
    })
    it('Should evaluate delimiters at start correctly', function(done){
        var balanced = require('../index.js');
        //console.log(matching);
        assert.deepEqual(balanced('{{{', '}}',"{{{234}}5"),{start:0, end:6,pre:"", post:"5",body:"234"});
        done();
    })
    it('Should evaluate delimiters at the end correctly', function(done){
        var balanced = require('../index.js');
        //console.log(matching);
        assert.deepEqual(balanced('{{{', '}}',"123{{{234}}"),{start:3, end:9,pre:"123", post:"",body:"234"});
        done();
    })

});

describe('Invalid',function(){
it('Should return undefined if there is no match', function(done){
        var balanced = require('../index.js');
        //console.log(matching);
        assert.isUndefined(balanced('{{{', '}}',"{{{2345"));
        done();
    })
})
