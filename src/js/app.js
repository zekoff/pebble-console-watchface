// Example request: "http://maps.googleapis.com/maps/api/geocode/json?latlng=40.714224,-73.961452"
var apiTarget = 'http://maps.googleapis.com/maps/api/geocode/json?latlng=';

var xhrRequest = function(url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function() {
    callback(this.responseText);
  };
  xhr.open(type, url);
  xhr.send();
};

function locationSuccess(pos) {
  var url = apiTarget + pos.coords.latitude + ',' + pos.coords.longitude;
  console.log(url);
  xhrRequest(url, 'GET', function(responseText) {
    var json = JSON.parse(responseText);
    console.log(json);
    var location = "NYI";
    var dictionary = {
      'KEY_LOCATION': location
    };
    Pebble.sendAppMessage(dictionary,
      function(e) {
        console.log('Location info sent successfully.');
      },
      function(e) {
        console.log('Error sending location info to Pebble.');
      }
    );
  });
}

function locationError(err) {
  console.log("Error requesting location.");
}

function updateIssLocation() {
  navigator.geolocation.getCurrentPosition(
    locationSuccess,
    locationError,
    {timeout: 15000, maximumAge: 60000}
  );
}

Pebble.addEventListener('ready',function(e){
  console.log('PebbleKit JS ready!');
  updateIssLocation();
});

Pebble.addEventListener('appmessage', function(e){
  console.log('AppMessage received!');
  updateIssLocation();
});