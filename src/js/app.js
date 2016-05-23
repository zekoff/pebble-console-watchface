var reverseGeocodeApiTarget = 'http://maps.googleapis.com/maps/api/geocode/json?latlng=';
var issInfoTarget = 'https://api.wheretheiss.at/v1/satellites/25544';

var xhrRequest = function(url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function() {
    callback(this.responseText);
  };
  xhr.open(type, url);
  xhr.send();
};

function locationSuccess(info) {
  var url = reverseGeocodeApiTarget + info.latitude + ',' + info.longitude;
  console.log(url);
  xhrRequest(url, 'GET', function(responseText) {
    var response = JSON.parse(responseText);
    var location = "";
    if (response.status == "OK")
      location = response.results[response.results.length - 1].formatted_address;
    console.log(location);
    var dictionary = {
      'KEY_LOCATION': location,
      'KEY_VISIBILITY': info.visibility == "eclipsed" ? "0" : "1"
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
  xhrRequest(issInfoTarget, 'GET', function(responseText) {
    console.log(responseText);
    locationSuccess(JSON.parse(responseText));
  });
}

Pebble.addEventListener('ready',function(e) {
  updateIssLocation();
});

Pebble.addEventListener('appmessage', function(e) {
  updateIssLocation();
});