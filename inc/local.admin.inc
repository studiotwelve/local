<?php

if(!function_exists("_local_variables_get_array")){
  module_load_include("inc", "local", "inc/local.vars");
}

function local_admin_settings_form(){
  $form["header"] = array(
    "#type" => "fieldset",
    "#title" => "Find the local business",
    "#description" => "Use the search field below to find the place and autofill the form with data from Google Places",
  );
  
  $form["header"]["place"] = array(
    "#type" => "item",
    "#title" => "Search",
    "#markup" => '<div id="gplace"></div><div id="locationField"><input id="edit-local-autocomplete" placeholder="Business Name, address" name="business_name_address" onFocus="geolocate()" type="text" class="form-text" autocomplete="noautofill" size="60"></div><div id="place"></div><div id="gplace-photos"></div>',
  );

  drupal_add_css(drupal_get_path('module', 'local') .'/css/local.admin.css');

  drupal_add_js("var parse_place_path='/admin/local/parse_place'", array(
    "type" => "inline",
    "scope" => "footer",
    "weight" => 5090,
  ));

  drupal_add_js(drupal_get_path("module", "local")."/js/local.admin.place.js", array(
    "scope" => "footer",
    "weight" => 6000,
  ));

  drupal_add_js("https://apis.google.com/js/auth.js?onload=init", array(
    "type" => "external",
    "scope" => "footer",
    "weight" => 1,
  ));

  drupal_add_js("https://maps.googleapis.com/maps/api/js?key=AIzaSyCRL-8r3w92eVlnxR2QFjmU5PuGpOhh8lg&libraries=places", array(
    "type" => "external",
    "scope" => "footer",
    "weight" => 6010,
  ));

  $form["contact"] = array(
    "#type" => "fieldset",
    "#title" => "Local Business Contact Info",
    "#description" => "NAP (Name, Address, Phone) / Email",
  );

  $form["contact"]["local_name"] = array(
    "#type" => "textfield",
    "#title" => t("Name"),
    "#default_value" => variable_get("local_name", variable_get("site_name", FALSE)),
    "#description" => t("Enter the preferred full name of the business. Assuming you've already changed the site name you can probably leave the default value as is, if not you should probably go change the site information first. @link", array("@link" => "<a href=\"/admin/config/system/site_information\" title=\"Edit: Site Information\" target=\"_blank\">Site information</a>")),
  );

  $form["contact"]["address"] = array(
    "#type" => "fieldset",
    "#title" => "Local Business Address",
    "#description" => "The primary address of the business.",
  );

  $form["contact"]["address"]["local_address_street"] = array(
    "#type" => "textfield",
    "#title" => t("Street address"),
    "#default_value" => variable_get("local_address_street", FALSE),
  );


  $form["contact"]["address"]["local_address_city"] = array(
    "#type" => "textfield",
    "#title" => t("City"),
    "#default_value" => variable_get("local_address_city", FALSE),
  );


  $form["contact"]["address"]["local_address_state"] = array(
    "#type" => "select",
    "#title" => t("State"),
    "#default_value" => variable_get("local_address_state", "none"),
    "#options" => array(
      "none" => "====== SELECT ONE ======",
      "ak" => t("AK (Alaska)"),
      "al" => t("AL (Alabama)"),
      "ar" => t("AR (Arkansas)"),
      "az" => t("AZ (Arizona)"),
      "ca" => t("CA (California)"),
      "co" => t("CO (Colorado)"),
      "ct" => t("CT (Connecticut)"),
      "de" => t("DE (Delaware)"),
      "fl" => t("FL (Florida)"),
      "ga" => t("GA (Georgia)"),
      "hi" => t("HI (Hawaii)"),
      "ia" => t("IA (Iowa)"),
      "id" => t("ID (Idaho)"),
      "il" => t("IL (Illinois)"),
      "in" => t("IN (Indiana)"),
      "ks" => t("KS (Kansas)"),
      "ky" => t("KY (Kentucky)"),
      "la" => t("LA (Louisiana)"),
      "ma" => t("MA (Massachusetts)"),
      "md" => t("MD (Maryland)"),
      "me" => t("ME (Maine)"),
      "mi" => t("MI (Michigan)"),
      "mn" => t("MN (Minnesota)"),
      "mo" => t("MO (Missouri)"),
      "ms" => t("MS (Mississippi)"),
      "mt" => t("MT (Montana)"),
      "nc" => t("NC (North Carolina)"),
      "nd" => t("ND (North Dakota)"),
      "ne" => t("NE (Nebraska)"),
      "nh" => t("NH (New Hampshire)"),
      "nj" => t("NJ (New Jersey)"),
      "nm" => t("NM (New Mexico)"),
      "nv" => t("NV (Nevada)"),
      "ny" => t("NY (New York)"),
      "oh" => t("OH (Ohio)"),
      "ok" => t("OK (Oklahoma)"),
      "or" => t("OR (Oregon)"),
      "pa" => t("PA (Pennsylvania)"),
      "ri" => t("RI (Rhode Island)"),
      "sc" => t("SC (South Carolina)"),
      "sd" => t("SD (South Dakota)"),
      "tn" => t("TN (Tennessee)"),
      "tx" => t("TX (Texas)"),
      "ut" => t("UT (Utah)"),
      "va" => t("VA (Virginia)"),
      "vt" => t("VT (Vermont)"),
      "wa" => t("WA (Washington)"),
      "wi" => t("WI (Wisconsin)"),
      "wv" => t("WV (West Virginia)"),
      "wy" => t("WY (Wyoming)"),
    ),
  );

  $form["contact"]["address"]["local_address_zip"] = array(
    "#type" => "textfield",
    "#title" => t("Zip"),
    "#size" => 10,
    "#maxlength" => 5,
    "#default_value" => variable_get("local_address_zip", FALSE),
    "#attributes" => array(
      "pattern" => '[\d]{5}',
      "placeholder" => "28786",
    ),
  );

  $form["contact"]["geo"] = array(
    "#type" => "fieldset",
    "#title" => "Geo Coordinates",
    "#description" => "The latitude and longitude of the business.",
  );

  $form["contact"]["geo"]["local_geo_latitude"] = array(
    "#type" => "textfield",
    "#title" => t("latitude"),
    "#size" => 60,
    "#default_value" => variable_get("local_geo_latitude", FALSE),
  );

  $form["contact"]["geo"]["local_geo_longitude"] = array(
    "#type" => "textfield",
    "#title" => t("longitude"),
    "#size" => 60,
    "#default_value" => variable_get("local_geo_longitude", FALSE),
  );

  $form["contact"]["local_phone"] = array(
    "#type" => "textfield",
    "#title" => t("Phone"),
    "#size" => 24,
    "#maxlength" => 12,
    "#default_value" => variable_get("local_phone", FALSE),
    "#description" => t("XXX-XXX-XXXX <em>10-digit phone number separated with dashes.</em>"),
    "#attributes" => array(
      "pattern" => "[\d]{3}-[\d]{3}-[\d]{4}",
      "placeholder" => "828-246-9552",
    ),
  );

  $form["contact"]["local_email"] = array(
    "#type" => "textfield",
    "#title" => t("Email"),
    "#default_value" => variable_get("local_email", FALSE),
    "#description" => t("user@company.tld <em>The primary business email.</em>"),
    "#attributes" => array(
      "pattern" => ".*@.*\.?.*?",
      "placeholder" => "hello@whitefoxstudios.net",
    ),
  );

  $form["hours"] = array(
    "#type" => "fieldset",
    "#title" => "Hours of Operation",
  );

  $days = array(
    "mo" => "Monday",
    "tu" => "Tuesday",
    "we" => "Wednesday",
    "th" => "Thursday",
    "fr" => "Friday",
    "sa" => "Saturday",
    "su" => "Sunday",
  );

  foreach($days as $day => $title){
    $key = "local_hours_$day";

    $status = $key."_status";
    $open   = $key."_open";
    $close  = $key."_close";

    $form["hours"][$day] = array(
      "#type" => "fieldset",
      "#title" => $title,
    );

    $form["hours"][$day][$status] = array(
      "#type" => "checkbox",
      "#title" => "Open?",
      "#default_value" => variable_get($status, 1),
      "#attributes" => array(
        "style" => "display:inline-block",
      ),
    );

    $form["hours"][$day][$open] = array(
      "#type" => "textfield",
      "#title" => "From:",
      "#default_value" => variable_get($open, "9:00 am"),
      "#autocomplete_path" => "admin/local/autocomplete/hours",
      "#attributes" => array(
        "style" => "display:inline-block",
      ),
    );

    $form["hours"][$day][$close] = array(
      "#type" => "textfield",
      "#title" => "To:",
      "#default_value" => variable_get($close, "5:00 pm"),
      "#autocomplete_path" => "admin/local/autocomplete/hours",
      "#attributes" => array(
        "style" => "display:inline-block",
      ),
    );

    if($day == "sa" || $day == "su"){
      $form["hours"][$day][$status]["#default_value"] = variable_get($status, 0);
      $form["hours"][$day][$open]["#default_value"] = variable_get($open, FALSE);
      $form["hours"][$day][$close]["#default_value"] = variable_get($close, FALSE);
    }
  }
  
  $form["logo"] = array(
    "#type" => 'item',
    "#markup" => '<div style="float:right">'.local_logo_render(variable_get("local_logo", FALSE)).'</div>',
  );
  
  $form["local_logo"] = array(
    "#title" => "Logo",
    "#type" => "media",
    "#default_value" => variable_get("local_logo", FALSE),
    "#description" => "A social media ready, square, jpg img file",
    "#upload_location" => "public://",
    "#progress_indicator" => "bar",
  );

  $form["local_domain"] = array(
    "#title" => "Domain",
    "#type" => "textfield",
    "#default_value" => variable_get("local_domain", FALSE),
  );

  $form["local_place"] = array(
    "#title" => "Google Maps Place ID",
    "#type" => "textfield",
    "#default_value" => variable_get("local_place", FALSE),
  );

  $form["local_page"] = array(
    "#title" => "Google+ Page ID",
    "#type" => "textfield",
    "#default_value" => variable_get("local_page", FALSE),
  );

  $form["local_categories"] = array(
    "#title" => "Target Categories",
    "#type" => "textarea",
    "#default_value" => variable_get("local_categories", FALSE),
    "#description" => "One per line",
  );

  $form["local_keywords"] = array(
    "#title" => "Target Keywords/phrases",
    "#type" => "textarea",
    "#default_value" => variable_get("local_keywords", FALSE),
    "#description" => "One per line",
  );

  $form["local_description"] = array(
    "#title" => "Description",
    "#type" => "textarea",
    "#default_value" => variable_get("local_description", FALSE),
    "#description" => "150 chars here",
  );

  $form["social"] = array(
    "#title" => "Social Links",
    "#type" => "fieldset",
  );

  $local_vars = _local_variables_get_array();

  foreach($local_vars["social"] as $key => $value){
    $form["social"]["local_social_$key"] = array(
      "#title" => ucwords(str_replace("_", " ", $key)),
      "#type" => "textfield",
      "#default_value" => variable_get("local_social_$key", FALSE),
      "#prefix" => "<span class=\"fa fa-".str_replace("_", "-", $key)."\">&nbsp;</span>",
    );
  }
  
  $form['tokens'] = array(
    '#theme' => 'token_tree_link',
    '#token_types' => array('local'),
    '#global_types' => TRUE,
    '#click_insert' => TRUE,
  );
    
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );
  
  $form["#submit"][] = "local_admin_settings_form_submit";
    
  return system_settings_form($form);
}

function local_admin_settings_form_submit($form, &$form_state){
  
}
