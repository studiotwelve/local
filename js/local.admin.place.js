var placeDetails, autocomplete;

(function($){
  $(document).ready(function(){
    $.getScript("https://apis.google.com/js/client.js?onload=init");

    initAutocomplete();
    initMap();
        
    getBadge($("#edit-local-social-google-plus").val()+"?", $("#gplace"));
  });
})(jQuery)

function init(){
  gapi.client.setApiKey('AIzaSyA0ycf4y0jdqzZcK7B0lgyTjl0CUZ_i8wk');
}

function initAutocomplete() {
  autocomplete = new google.maps.places.Autocomplete((document.getElementById('edit-local-autocomplete')));

  autocomplete.addListener('place_changed', fillInAddress);
}

function fillInAddress() {
  (function($, place){
    $.ajax({
      method:'POST',
      url: parse_place_path,
      data: place,
    }).done(function(data){
      var local = JSON.parse(data);
      
      for(var name in local){
        $("#edit-"+name.replace(/_/gi,"-")).val(local[name]).addClass("autocompleted").each(function(i,o){
          if($(o).attr("type")=="checkbox" && parseInt(local[name]) == 1 && (!$(o).is(":checked"))){
            $(o).attr("checked", true);
          }
        });
      }
      
      getBadge(local.local_social_google_plus+"&", $("#gplace"));
      
      getPhotos(place);
    });
  })(jQuery, JSON.parse(JSON.stringify(autocomplete.getPlace())))
}

function getPhotos(place){
  (function($){
    var e = $("#gplace-photos");
    
    e.html("");
    
    var photos = place.photos;
     
    if(photos){
      for($i = 0; $i<photos.length; ++$i){
        e.append('<img src="'+photos[$i].getUrl({
          maxWidth:  photos[$i].width,
          maxHeight: photos[$i].height,
        })+'" style="width:auto; height:250px; display:block; float:left;">');
      }
    }
  })(jQuery)
}

function getBadge(url, target){
  (function($){
    var pattern = /\/([\d]+)\//gi,
        matches = pattern.exec(url),
        gscript = "https://apis.google.com/js/client:platform.js";
    
    if(matches){
      var page_id = matches[1];
    }
    
    if(page_id){
      gscript+="&publisherid="+page_id;
    }
    
    target.addClass("loading");
    
    $.getScript(gscript).done(function(){
      target.removeClass("loading");
    });
    
    target.html('<g:page href="'+url+'output=embed" width="450"></g:page>');
  })(jQuery)
}

function geolocate() {
  if (navigator.geolocation) {
    navigator.geolocation.getCurrentPosition(function(position) {
      var geolocation = {
        lat: position.coords.latitude,
        lng: position.coords.longitude
      };
      var circle = new google.maps.Circle({
        center: geolocation,
        radius: position.coords.accuracy
      });
      autocomplete.setBounds(circle.getBounds());
    });
  }
}

function initMap() {
  var map = new google.maps.Map(document.getElementById('place'), {
    center: {
      lat: parseFloat(jQuery("#edit-local-geo-latitude").val()),
      lng: parseFloat(jQuery("#edit-local-geo-longitude").val())
    },
    zoom: 17
  });

  var infowindow = new google.maps.InfoWindow();
  var service = new google.maps.places.PlacesService(map);
  
  service.getDetails({
    placeId: jQuery("#edit-local-place").val()
  }, function(place, status) {
    if (status === google.maps.places.PlacesServiceStatus.OK) {
      var marker = new google.maps.Marker({
        map: map,
        position: place.geometry.location
      });
      
      map.center = place.geometry.location;
      
      google.maps.event.addListener(marker, 'click', function() {
        infowindow.setContent(place.name);
        infowindow.open(map, this);
      });
      
      getPhotos(place);
    }    
  });
}
