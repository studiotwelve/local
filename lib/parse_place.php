<?php
if($_POST){
  $data = array(
    "name" => ($_POST["name"]) ? $_POST["name"] : FALSE,
    "address" => array(),
    "geo" => array(
      "latitude"  => ($_POST["geometry"]) ? $_POST["geometry"]["location"]["H"] : FALSE,
      "longitude" => ($_POST["geometry"]) ? $_POST["geometry"]["location"]["L"] : FALSE,     
    ),
    "phone" => ($_POST["international_phone_number"]) ? str_replace("+1 ", "",$_POST["international_phone_number"]) : FALSE,
    "hours" => array(),
    "place" => ($_POST["place_id"]) ? $_POST["place_id"] : FALSE,
    "page"  => FALSE,
    "social_google_plus" => ($_POST["url"]) ? $_POST["url"] : FALSE,
  );
  
  if($_POST["address_components"]){
    foreach($_POST["address_components"] as $key => $comp){
      switch ($comp["types"][0]) {
        case 'street_number':
          $data["address"]["street"]  = $comp["long_name"];
        break;
        
        case 'route':
          $data["address"]["street"] .= " ".$comp["long_name"];
        break;
        
        case 'locality':
          $data["address"]["city"]    = $comp["long_name"];
        break;
        
        case 'administrative_area_level_1':
          $data["address"]["state"]   = strtolower($comp["short_name"]);
        break;
        
        case 'postal_code':
          $data["address"]["zip"]     = $comp["long_name"];
        break;
      }
    }
  } else {
    $data["address"] = FALSE;
  }
  
  if($_POST["opening_hours"]){
    $days = array("mo","tu","we","th","fr","sa","su",);
    
    foreach($_POST["opening_hours"]["periods"] as $key => $day){
      $data["hours"][$days[$key]] = array(
        "status" => 1,
        "open" => $day["open"]["time"],
        "close" => $day["close"]["time"],
      );
    }
  } else {
    $data["hours"] = FALSE;
  }
  
  if($data["social_google_plus"]){
    $matches = preg_match("/\/([\d]+)\//g", $data["social_google_plus"]);
    
    $data["page"] = (count($matches)>1) ? $matches[1] : stripslashes($matches[0]);
  }
  
  foreach($data as $field_key => $field_value){
    if(is_array($field_value)){
      foreach($field_value as $key => $val){
        if(is_array($val)){
          foreach($val as $k => $v){
            $output["local_".$field_key."_".$key."_".$k] = $v;
          }
        }else{          
          $output["local_".$field_key."_".$key] = $val;
        }
      }
    }else{          
      $output["local_$field_key"] = $field_value;
    }
  }
    
  print json_encode(array_filter($output));
}
