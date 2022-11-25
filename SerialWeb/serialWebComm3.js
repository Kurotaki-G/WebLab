const express = require('express');
const app = express();
const path = require('path');
const router = express.Router();

router.get('/',function(req,res){
  res.sendFile(path.join(__dirname+'/indexWebComm3.html'));
});



var enableLED = false;
var blink = false;
var speed = 1000;

router.post('/setValue', function(req, res){
  let params = req.params;
  // sendSerial();
  // enableLED = !enableLED;
  
  console.log('body:'+req.body);
  console.log('query:'+JSON.stringify(req.query));
  console.log('query:'+req.query);

  // let reqJson = JSON.parse(req.body)
  
  // if(!!reqJson['LED']) enableLED = reqJson['LED']
  // if(!!reqJson['blink']) blink = reqJson['blink'];

  let data = '';

  // reading POST request's data
  req.on('data', function(char){
    data += char;
  });
  
  //function on end of reading POST request's data
 req.on('end', function(){
  console.log('Server - received from Client: '+data);

  try{
    updateServerVars(data);

  }
  catch(err){
    console.log("req isn't on JSON format");
    
  }

  res.status(200).send('Status: OK');
 })
});


//add the router
app.use('/', router);
app.listen(process.env.port || 3000);

console.log('Running at Port 3000');




router.get('/getStatus', function(req, res){

  let jsonO = {};
  jsonO['LED'] = enableLED;
  jsonO['blink'] = blink;
  jsonO['speed'] = speed;

  // console.log(jsonO);

  res.type('json');
  res.status(200);
  res.send(jsonO);
});



//--- NEW functions that process the data 

// JSON data ->> load to server's var
function updateServerVars(jsonDatas){
  
  let reqJson = JSON.parse(jsonDatas);

  if(reqJson['LED'] != null) enableLED = reqJson['LED']; 
  if(reqJson['blink'] != null) blink = reqJson['blink'];
  if(reqJson['speed'] != null) speed = reqJson['speed']; 

  sendDatasToArduino();
}

// server's var ->> JSON data to Arduino
function sendDatasToArduino(){
  
  let jsonO = {};
  jsonO['led'] = enableLED;
  jsonO['blink'] = blink;
  jsonO['speed'] = speed;
  
  let txt = JSON.stringify(jsonO);
  console.log('Server - send to Arduino: '+ txt);
  writeSerial(' '+txt+' ');
}



///from tstComm2.js


//Based on serial0.2.js

const {SerialPort} = require("serialport");


/// TEST ARDUINO RECEIVING DATA FROM NODE.JS

const port = new SerialPort({
  path: 'COM4',
  baudRate: 9600,
  autoOpen: false,
  // autoOpen: true,
})

port.open(function (err) {
  if (err) {
    return console.log('Error opening port: ', err.message)
  }
  // Because there's no callback to write, write errors will be emitted on the port:
  port.write('main screen turn on')
})

port.on('close', function(){
    console.log('closed!!');
    console.log('reconnecting...');
})

//autorreconect
setInterval(function(){
  if(!port.isOpen){
    port.open(function (err) {
      if (err) {
        return process.stdout.write('.');
      }
      console.log();
      console.log('reconected!');
    })
  }
}, 1000);

// The open event is always emitted
port.on('open', function() {
  // open logic
  console.log('Open logic');
})

// Read data that is available but keep the stream in "paused mode"
port.on('readable', function () {
    port.read();
    console.log('reading!');
})
  
//Show Serial data from Arduino in console
port.on('data', function (data) {
    console.log(data+"");
  })

//Write data in Serial port
function writeSerial(text){
    port.write(text, function(err) {
        if (err) {
          return console.log('Error on write: ', err.message)
        }
        // console.log('message '+text+' written')
      })
}

