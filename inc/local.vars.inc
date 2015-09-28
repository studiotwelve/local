<?php

function _local_variables_get_array(){
  $vars = array();

  // client data
  $vars["client"]["name"] = variable_get("local_client_name", FALSE);

  $vars["client"]["address"] = array(
    "street" => variable_get("local_client_address_street", FALSE),
    "city"   => variable_get("local_client_address_city", FALSE),
    "state"  => variable_get("local_client_address_state", FALSE),
    "zip"    => variable_get("local_client_address_zip", FALSE),
  );

  $vars["client"]["phone"] = variable_get("local_client_phone", FALSE);

  $vars["client"]["email"] = variable_get("local_client_email", FALSE);

  $vars["client"]["registrar"] = array(
    "name" => variable_get("local_client_registrar_name", FALSE),
    "user" => variable_get("local_client_registrar_user", FALSE),
    "pass" => variable_get("local_client_registrar_pass", FALSE),
  );

  $vars["client"]["server"] = array(
    "name" => variable_get("local_client_server_name", FALSE),
    "ip" => variable_get("local_client_server_ip", FALSE),
    "ftp" => array(
      "user" => variable_get("local_client_server_ftp_user", FALSE),
      "pass" => variable_get("local_client_server_ftp_pass", FALSE),
    ),
  );
  
  $vars["client"]["seo"] = array(
    "package" => variable_get("local_client_seo_package", FALSE),
    "email" => array(
      "address" => variable_get("local_client_seo_email_address", FALSE),
      "password" => variable_get("local_client_seo_email_password", FALSE),
    ),
    "username" => variable_get("local_client_seo_username", FALSE),
    "password" => variable_get("local_client_seo_password", FALSE),
  );

  // seo data
  $vars["name"] = variable_get("local_name", false);

  $vars["address"] = array(
    "street" => variable_get("local_address_street", FALSE),
    "city"   => variable_get("local_address_city", FALSE),
    "state"  => variable_get("local_address_state", FALSE),
    "zip"    => variable_get("local_address_zip", FALSE),
  );
  
  $vars["geo"] = array(
    "latitude" => variable_get("local_geo_latitude", FALSE),
    "longitude"   => variable_get("local_geo_longitude", FALSE),
  );

  $vars["phone"] = variable_get("local_phone", FALSE);

  $vars["email"] = variable_get("local_email", FALSE);

  $vars["hours"] = array(
    "mo" => array(
      "status" => variable_get("local_hours_mo_status", FALSE),
      "open"   => variable_get("local_hours_mo_open", FALSE),
      "close"  => variable_get("local_hours_mo_close", FALSE),
    ),

    "tu" => array(
      "status" => variable_get("local_hours_tu_status", FALSE),
      "open"   => variable_get("local_hours_tu_open", FALSE),
      "close"  => variable_get("local_hours_tu_close", FALSE),
    ),

    "we" => array(
      "status" => variable_get("local_hours_we_status", FALSE),
      "open"   => variable_get("local_hours_we_open", FALSE),
      "close"  => variable_get("local_hours_we_close", FALSE),
    ),

    "th" => array(
      "status" => variable_get("local_hours_th_status", FALSE),
      "open"   => variable_get("local_hours_th_open", FALSE),
      "close"  => variable_get("local_hours_th_close", FALSE),
    ),

    "fr" => array(
      "status" => variable_get("local_hours_fr_status", FALSE),
      "open"   => variable_get("local_hours_fr_open", FALSE),
      "close"  => variable_get("local_hours_fr_close", FALSE),
    ),

    "sa" => array(
      "status" => variable_get("local_hours_sa_status", FALSE),
      "open"   => variable_get("local_hours_sa_open", FALSE),
      "close"  => variable_get("local_hours_sa_close", FALSE),
    ),

    "su" => array(
      "status" => variable_get("local_hours_su_status", FALSE),
      "open"   => variable_get("local_hours_su_open", FALSE),
      "close"  => variable_get("local_hours_su_close", FALSE),
    ),
  );

  $vars["logo"]   = variable_get("local_logo", FALSE);

  $vars["domain"] = variable_get("local_domain", FALSE);
  
  $vars["place"] = variable_get("local_place", FALSE);
  
  $vars["page"] = variable_get("local_page", FALSE);

  $vars["categories"]  = variable_get("local_categories", FALSE);
  $vars["keywords"]    = variable_get("local_keywords", FALSE);
  $vars["description"] = variable_get("local_description", FALSE);

  //required
  $vars["social"]["facebook"]    = variable_get("local_social_facebook", FALSE);
  $vars["social"]["twitter"]     = variable_get("local_social_twitter", FALSE);
  $vars["social"]["google_plus"] = variable_get("local_social_google_plus", FALSE);
  $vars["social"]["linkedin"]    = variable_get("local_social_linkedin", FALSE);
  $vars["social"]["instagram"]   = variable_get("local_social_instagram", FALSE);
  $vars["social"]["pinterest"]   = variable_get("local_social_pinterest", FALSE);
  $vars["social"]["youtube"]     = variable_get("local_social_youtube", FALSE);

  //optional
  $vars["social"]["myspace"]     = variable_get("local_social_myspace", FALSE);
  $vars["social"]["soundcloud"]  = variable_get("local_social_soundcloud", FALSE);
  $vars["social"]["tumblr"]      = variable_get("local_social_tumblr", FALSE);

  return $vars;
}

function _local_variables_get_keys(){
  $vars = _local_variables_get_array();
  $keys = array();

  foreach($vars as $var_key => $var_val){
    if(is_array($var_val)){
      foreach($var_val as $key => $val){
        if(is_array($val)){
          foreach($val as $k => $v){
            $keys[]="local_".$var_key."_".$key."_".$k;
          }
        } else {
          $keys[]="local_".$var_key."_".$key;
        }
      }
    } else {
      $keys[]="local_".$var_key;
    }
  }

  return $keys;
}

function _local_variables_flush(){
  $vars = _local_variables_get_keys();

  foreach($vars as $var){
    if(!variable_get($var, FALSE) == FALSE){
      variable_del($var);
    }
  }
}

function _local_state_names($state=NULL){
  $names = array(
    "ak" => "Alaska",
    "al" => "Alabama",
    "ar" => "Arkansas",
    "az" => "Arizona",
    "ca" => "California",
    "co" => "Colorado",
    "ct" => "Connecticut",
    "de" => "Delaware",
    "fl" => "Florida",
    "ga" => "Georgia",
    "hi" => "Hawaii",
    "ia" => "Iowa",
    "id" => "Idaho",
    "il" => "Illinois",
    "in" => "Indiana",
    "ks" => "Kansas",
    "ky" => "Kentucky",
    "la" => "Louisiana",
    "ma" => "Massachusetts",
    "md" => "Maryland",
    "me" => "Maine",
    "mi" => "Michigan",
    "mn" => "Minnesota",
    "mo" => "Missouri",
    "ms" => "Mississippi",
    "mt" => "Montana",
    "nc" => "North Carolina",
    "nd" => "North Dakota",
    "ne" => "Nebraska",
    "nh" => "New Hampshire",
    "nj" => "New Jersey",
    "nm" => "New Mexico",
    "nv" => "Nevada",
    "ny" => "New York",
    "oh" => "Ohio",
    "ok" => "Oklahoma",
    "or" => "Oregon",
    "pa" => "Pennsylvania",
    "ri" => "Rhode Island",
    "sc" => "South Carolina",
    "sd" => "South Dakota",
    "tn" => "Tennessee",
    "tx" => "Texas",
    "ut" => "Utah",
    "va" => "Virginia",
    "vt" => "Vermont",
    "wa" => "Washington",
    "wi" => "Wisconsin",
    "wv" => "West Virginia",
    "wy" => "Wyoming",
  );

  if($state && count($state) > 2 && in_array($state, $names)){
  //return the abbreviation in caps if given the full state name
    return strtoupper(array_search($state, $names));
  } else {
  //return the full name in title case or the states array
    return ($state && in_array($state, $names)) ? $names[$state] : $names;
  }
}
