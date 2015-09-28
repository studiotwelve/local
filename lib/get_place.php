<?php
if($_POST["place_id"]){
  $key = "AIzaSyA0ycf4y0jdqzZcK7B0lgyTjl0CUZ_i8wk";
  
  print json_encode(file_get_contents("https://maps.googleapis.com/maps/api/place/details/json?placeid=".$_POST["place_id"]."&key=".$key.""));
}
