// code written in js, can be executed from command line with node.js
binary "node":
// code starts here, save me to  translator.js and execute with "node
translator.js"
// simple is beautiful

var mapping = {
    'A' : '2', 'B' : '22', 'C' : '222',
    'D' : '3', 'E' : '33', 'F' : '333',
    'G' : '4', 'H' : '44', 'I' : '444',
    'J' : '5', 'K' : '55', 'L' : '555',
    'M' : '6', 'N' : '66', 'O' : '666',
    'P' : '7', 'Q' : '77', 'R' : '777', 'S' : '7777',
    'T' : '8', 'U' : '88', 'V' : '888',
    'W' : '9', 'X' : '99', 'Y' : '999', 'Z' : '9999',
    ' ' : '0'
}

function translate(input) {
    var output = [];
    input.split('').forEach(function(i){
        output.push(mapping[i]);
    });
    return output.join(' ');
}


function demo () {
    console.log( translate('HELLO WORLD THIS IS A TEST') );
}

// call demo
demo();

// if a nickname for code is required: simple-is-beautiful will do
