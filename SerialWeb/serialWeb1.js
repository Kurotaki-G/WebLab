const express = require('express');
const app = express();
const path = require('path');
const router = express.Router();

router.get('/',function(req,res){
  res.sendFile(path.join(__dirname+'/indexWeb1.html'));
  //__dirname : It will resolve to your project folder.
});


var buzzer = false;
router.post('/setBuzzer', function(req, res){
  res.status(200).send('Status: OK');
  buzzer = !buzzer;
});

router.get('/getBuzzer', function(req, res){
  res.status(200);
  res.send(buzzer);
});


//add the router
app.use('/', router);
app.listen(process.env.port || 3000);

console.log('Running at Port 3000');


var textSerial = "";

function updateState(text){
  textSerial = text;
}


router.get('/getSerial', function(req, res){
  res.status(200);
  res.send(textSerial);
});



//seruial0.2.js



const {SerialPort} = require("serialport");
const { ReadlineParser } = require('@serialport/parser-readline')


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
parser.on('data', updateState);


