<?php

if(!function_exists("local_variables_get_array")){
  module_load_include("inc", "local", "inc/local.vars");
}

function local_token_info(){
  $info = array(
    "types" => array(
      "local" => array(
        "name" => t("Local tokens"),
        "description" => t("Returns stored local data"),
      ),
    ),
  );

  $vars = _local_variables_get_array();
  unset $vars["client"];
  extract($vars);

  $keyword_list = explode("\n", $keywords);
  $keywords_plain = implode(", ", str_replace(array(", ",","), " ", $keyword_list));
  $primary_keyword = $keyword_list[0];

  $phone_badchars = explode("", ")(-_+");
  $phone_machine = "+1".str_replace($phone_badchars, "", $phone);

  extract($address);

  $state_name = local_state_names($state);
  $state = strtoupper($state);

  $attr_alt = "$name $city, $state $keywords_plain $city $state $primary_keyword";
  $attr_title = "$name $primary_keyword $city, $state";

  $url = "http://$domain";

  $name_link = l($name, $url, array(
    "attributes" => array(
      "title" => $attr_title,
    ),
  ));

  $tokens["name"]["plain"] = array(
    "name" => t("Name Plain"),
    "description" => t("The plain text business name, eg. $name"),
    "type" => "text",
  );

  $tokens["name"]["link"] = array(
    "name" => t("Name link"),
    "description" => t("The business name linked to the domain, eg. $name_link"),
    "type" => "text",
  );

  $tokens["address"]["plain"] = array(
    "name" => t("Address Plain"),
    "description" => t("The plain text full address eg. $street $city, $state $zip"),
    "type" => "text",
  );

  $tokens["street"] = array(
    "name" => t("Street"),
    "description" => t("The street, eg. $street"),
    "type" => "text",
  );

  $tokens["city"] = array(
    "name" => t("City"),
    "description" => t("The city, eg. $city"),
    "type" => "text",
  );

  $tokens["state"] = array(
    "name" => t("State abbreviated"),
    "description" => t("The 2 letter state code, eg. $state"),
    "type" => "text",
  );

  $tokens["state_name"] = array(
    "name" => t("State full name"),
    "description" => t("The state name, eg. $state_name"),
    "type" => "text",
  );

  $tokens["zip"] = array(
    "name" => t("Zip"),
    "description" => t("The zip, eg. $zip"),
    "type" => "text",
  );

  $tokens["phone"] = array(
    "name" => t("Phone"),
    "description" => t("The phone number, eg. $phone"),
    "type" => "text",
  );

  $tokens["phone_global"] = array(
    "name" => t("Phone Global"),
    "description" => t("The phone number, eg. $phone_machine"),
    "type" => "text",
  );

  $tokens["click_to_call"] = array(
    "name" => t("Click to call Link"),
    "description" => t("The phone number, eg. <a title=\"Click to call: $attr_title $phone\" href=\"tel:$phone_machine\">$phone</a> linked."),
    "type" => "text",
  );

  $token["nap"] = array(
    "name" => t("NAP"),
    "description" => t("The name, address, phone, eg. $name $street $city, $state $zip $phone"),
    "type" => "text",
  );
  
  extract($geo);
  
  $token["geo"]["lat"] = array(
    "name" => t("Latitude"),
    "description" => t("The primary location's latitude eg. $latitude"),
    "type" => "text",
  );
  
  $token["geo"]["lon"] = array(
    "name" => t("Longitude"),
    "description" => t("The primary location's longitude eg. $longitude"),
    "type" => "text",
  );
  
  $token["geo"]["pos"] = array(
    "name" => t("Geo Position"),
    "description" => t("Formatted Geo Position: $latitude;$longitude"),
    "type" => "text",
  )
  
  $token["ICBM"] = array(
    "name" => t("ICBM"),
    "description" => t("Formatted ICBM: $latitude, $longitude"),
    "type" => "text",
  )

  $tokens["email"] = array(
    "name" => t("Email plain"),
    "description" => t("The plain text email address, eg. $email"),
    "type" => "text",
  );

  $email_link = array();

  $tokens["mailto"] = array(
    "name" => t("Email Link"),
    "description" => t("The linked email address, eg. $email"),
    "type" => "text",
  );

  $logo_entities = entity_load("file", array($logo));
  $logo_entity = $logo_entities[$logo];
  $logo_url = file_create_url($logo_entity->uri);
  $logo_img = local_logo_render($logo, array(
      "class" => "logo img-responsive",
      "style" => "display:block; width:100%; height:auto",
    ),
  );

  $tokens["logo_url"] = array(
    "name" => t("Logo URL"),
    "description" => t("The logo url, eg. $logo_url"),
    "type" => "text",
  );

  $tokens["logo_img"] = array(
    "name" => t("Logo URL"),
    "description" => t("The logo image, eg. $logo_img"),
    "type" => "text",
  );

  $tokens["domain"] = array(
    "name" => t("domain"),
    "description" => t("The domain name, eg. $domain"),
    "type" => "text",
  );

  $tokens["keywords"] = array(
    "name" => t("Keywords"),
    "description" => t("Comma separated list of keywords. $keywords_plain",
    "type" => "text",
  );

  $tokens["description"] = array(
    "name" => t("Description"),
    "description" => t("A description of the location, eg. $description"),
    "type" => "text",
  );

  $tokens["categories"] = array(
    "name" => t("Categories"),
    "description" => t("Comma separated list of categories. !categories", array("!categories"=> str_replace("\n", ", ", str_replace(array(",",", ")," ",$categories)))),
    "type" => "text",
  );
  
  $social_list = array();
  
  foreach($social as $key => $value){
    $title = ucwords(str_replace(" plus", "+", str_replace("_", " ", $key)));
    $class = str_replace("_", "-", $key);
    $link = '<a itemprop="sameas" href="'.$value.'" title="'.$title.'" class="'.$class.'"><span class="fa fa-'.$class.'"> </span> <span class="sr-only"> '.$title.'</span></a>';
    
    $tokens["social"][$key] = array(
      "name" => "$title Link",
      "description" => t("The icon with title linked to the location's $title eg. $link"),
      "type" => "text",
    );
    
    $social_list[]="<li>$link</li>";
  }
  
  $social_list = '<ul class="social">'.implode("\n", $social_list).'</ul>';
  
  $tokens["social"]["list"] = array(
    "name" => t("Themed Social Icon List"),
    "description" => t("Unformatted list of social icon links eg. $social_list"),
    "type" => "text",
  );
  
  $info["tokens"]["local"] = $tokens;
  
  return $info;
}

function local_tokens($type, $tokens, array $data = array(), array $options = array()){

}
