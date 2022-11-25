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
  // sendSerial();
  enableLED = !enableLED;
  writeSerial( '{"led":'+enableLED+', "vel":2000} ');
  res.status(200).send('Status: OK');
});


//add the router
app.use('/', router);
app.listen(process.env.port || 3000);

console.log('Running at Port 3000');


var textSerial = "";


router.get('/getSerial', function(req, res){
  res.status(200);
  res.send(textSerial);
});


///from tstComm2.js




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







function writeSerial(text){
    port.write(text, function(err) {
        if (err) {
          return console.log('Error on write: ', err.message)
        }
        // console.log('message '+text+' written')
      })
}



// from serialWebComm1.js


function sendSerial(){
    // port.write('{"led":'+enableLED+'}\n');
    port.write('{"led":false, "vel":2000}\n');
    // port.write('{"led":'+enableLED+'}', function(err) {
    //   if (err) {
    //     return console.log('Error on write: ', err.message)
    //   }
    //   console.log('message written')
    // })
    console.log('{"led":'+enableLED+'}\n');
    // console.log('{"led":'+enableLED+', "vel":'+100+'}');
  }
  