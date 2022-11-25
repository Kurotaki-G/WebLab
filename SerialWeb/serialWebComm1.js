const express = require('express');
const app = express();
const path = require('path');
const router = express.Router();

router.get('/',function(req,res){
  res.sendFile(path.join(__dirname+'/indexWebComm1.html'));
});


var buzzer = false;
router.post('/setBuzzer', function(req, res){
  res.status(200).send('Status: OK');
  buzzer = !buzzer;
});

var enableLED = false;

router.get('/getBuzzer', function(req, res){
  res.status(200);
  // res.send(buzzer);
  res.send(enableLED);
});



router.post('/setValue', function(req, res){
  let params = req.params;
  enableLED = !enableLED;
  res.status(200).send('Status: OK');
  sendSerial();
});


//add the router
app.use('/', router);
app.listen(process.env.port || 3000);

console.log('Running at Port 3000');


var textSerial = "";

function updateState(text){
  textSerial = text;
  console.log(text);
}


router.get('/getSerial', function(req, res){
  res.status(200);
  res.send(textSerial);
});



//seruial0.2.js



const {SerialPort} = require("serialport");
const { ReadlineParser } = require('@serialport/parser-readline');
const { send } = require('process');
const { serialize } = require('v8');


const port = new SerialPort({
  path: 'COM4',
  baudRate: 115200,
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
  
const parser = new ReadlineParser({delimiter: '\r\n'});

port.pipe(parser);
// parser.on('data', updateState);
parser.on('data', console.log);


function sendSerial(){
  // port.write('{"led":'+enableLED+'}\n');
  port.write('{"led":'+enableLED+'}\n', function(err) {
    if (err) {
      return console.log('Error on write: ', err.message)
    }
    console.log('message written')
  })
  console.log('{"led":'+enableLED+'}\n');
  // console.log('{"led":'+enableLED+', "vel":'+100+'}');
}
