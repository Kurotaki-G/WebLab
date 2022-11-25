

//Based on serial0.2.js

const {SerialPort} = require("serialport");


/// TEST ARDUINO RECEIVING DATA FROM NODE.JS

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
    // console.log('Data:', data+"");
    // if(data == 10) console.log('enter!!');
    console.log(data+"");
  })

var input = "";

function updateState(serialText){
    try{
    let jsonData = JSON.parse(serialText);
    let text = 'Button ';
    if(jsonData.hasOwnProperty("but")) text += jsonData["but"] ? 'ON' : 'OFF';
    text += "  ";
    text += "Pot: ";
    if(jsonData.hasOwnProperty("pot")) text += jsonData["pot"];
    text += "  ";
    text += "Input: ";
    text += input;

    console.log(text);
}
catch(e){
    console.log(serialText);
}
}

var readline = require('readline');

var leitor = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

// getInput();


// setInterval(function() {
//     port.write("aaa\n\n");
// }, 1000)

getInput();

function getInput(){
    leitor.question("", function (answer) {
        input = answer;
        writeSerial(input+"\n");
        getInput();
    });
    // leitor.question("Write Something: \n", function(answer) {
    //     input = answer;
    //     // console.log("\nInput '" + input + "' Saved");
    //     // leitor.close();
    //     writeSerial(input+"\n");
    //     getInput();
    //     // console.log("finished input");
    // });
}

function writeSerial(text){
    port.write(text, function(err) {
        if (err) {
          return console.log('Error on write: ', err.message)
        }
        // console.log('message '+text+' written')
      })
}