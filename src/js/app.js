var reverseGeocodeApiTarget = 'http://maps.googleapis.com/maps/api/geocode/json?latlng=';
var issLocationApiTarget = 'http://api.open-notify.org/iss-now.json';

var xhrRequest = function(url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function() {
    callback(this.responseText);
  };
  xhr.open(type, url);
  xhr.send();
};

function locationSuccess(pos) {
  console.log(pos);
  var url = reverseGeocodeApiTarget + pos.latitude + ',' + pos.longitude;
  console.log(url);
  xhrRequest(url, 'GET', function(responseText) {
    var response = JSON.parse(responseText);
    var location = response.results[response.results.length - 2].formatted_address;
    console.log(location);
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

function updateIssLocation() {
  xhrRequest(issLocationApiTarget, 'GET', function(responseText) {
    console.log(responseText);
    locationSuccess(JSON.parse(responseText).iss_position);
  });
}

Pebble.addEventListener('ready',function(e){
  console.log('PebbleKit JS ready!');
  updateIssLocation();
});

Pebble.addEventListener('appmessage', function(e){
  console.log('AppMessage received!');
  updateIssLocation();
});