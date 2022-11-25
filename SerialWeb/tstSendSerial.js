

//Based on serial0.2.js

const {SerialPort} = require("serialport");


/// TEST ARDUINO SENDING DATA TO NODEJS

const port = new SerialPort({
  path: 'COM4',
  baudRate: 9600,
  autoOpen: false,
})

port.open(function (err) {
  if (err) {
    return console.log('Error opening port: ', err.message)
  }
  // Because there's no callback to write, write errors will be emitted on the port:
  port.write('main screen turn on')
})

// The open event is always emitted
port.on('open', function() {
  // open logic
  console.log('Open logic');
})

// Read data that is available but keep the stream in "paused mode"
port.on('readable', function () {
    port.read();
})
  
port.on('data', function (data) {
  console.log('Data:', data+"");
  if(data == 10) console.log('enter!!');
})

var input = "";

function updateState(serialText){
    let jsonData = JSON.parse(serialText);
    let text = 'Button ';
    text += jsonData["but"] ? 'ON' : 'OFF';
    text += "  ";
    text += "Pot: ";
    text += jsonData["pot"];

    text += "  ";
    text += "Input: ";
    text += input;

    console.log(text);
}

// var readline = require('readline');
// var resp = "";

// var leitor = readline.createInterface({
//     input: process.stdin,
//     output: process.stdout
// });

// // getInput();

// function getInput(){
//     leitor.question("Write Something: \n", function(answer) {
//         input = answer;
//         console.log("\nInput '" + resp + "' Saved");
//         // leitor.close();
//         getInput();
//     });
// }
