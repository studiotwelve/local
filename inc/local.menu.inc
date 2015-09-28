<?php

/**
 * Implements hook_menu().
 */
function local_menu() {
  $items = array();

  $path = drupal_get_path("module","local");

  $items['admin/local'] = array(
    'title' => 'Local',
    'description' => 'Administer local module.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('local_admin_settings_form'),
    'access arguments' => array('administer site configuration'),
    'file' => 'inc/local.admin.inc',
    'file path' => $path,
    'type' => MENU_NORMAL_ITEM,
  );

  $items['admin/local/data'] = array(
    'title' => 'Local Data',
    'description' => 'Manage local business info.',
    'type' => MENU_DEFAULT_LOCAL_TASK,
  );

  $items['admin/local/client'] = array(
    'title' => 'Client Data',
    'description' => 'Manage client data.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('local_admin_client_settings_form'),
    'access arguments' => array('administer site configuration'),
    'file' => 'inc/local.admin.client.inc',
    'file path' => $path,
    'type' => MENU_LOCAL_TASK,
  );

  $items['admin/local/locations'] = array(
    'title' => 'Locations',
    'description' => 'Manage business locations.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('local_admin_locations_settings_form'),
    'access arguments' => array('administer site configuration'),
    'file' => 'inc/local.admin.locations.inc',
    'file path' => $path,
    'type' => MENU_LOCAL_TASK,
  );

  $items['admin/local/services'] = array(
    'title' => 'Services',
    'description' => 'Manage business services.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('local_admin_services_settings_form'),
    'access arguments' => array('administer site configuration'),
    'file' => 'inc/local.admin.services.inc',
    'file path' => $path,
    'type' => MENU_LOCAL_TASK,
  );

  $items['admin/local/areas'] = array(
    'title' => 'Service Areas',
    'description' => 'Manage business service areas.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('local_admin_areas_settings_form'),
    'access arguments' => array('administer site configuration'),
    'file' => 'inc/local.admin.areas.inc',
    'file path' => $path,
    'type' => MENU_LOCAL_TASK,
  );

  $items['admin/local/citations'] = array(
    'title' => 'Citations',
    'description' => 'Manage local business citations.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('local_admin_citations_settings_form'),
    'access arguments' => array('administer site configuration'),
    'file' => 'inc/local.admin.citations.inc',
    'file path' => $path,
    'type' => MENU_LOCAL_TASK,
  );

  $items['admin/local/parse_place'] = array(
    'page callback' => '_local_admin_parse_place',
    'access arguments' => array('administer site configuration'),
    'file' => 'lib/parse_place.php',
    'file path' => $path,
    'type' => MENU_CALLBACK,
  );

  $items['admin/local/get_place'] = array(
    'page callback' => '_local_admin_get_place',
    'access arguments' => array('administer site configuration'),
    'file' => 'lib/get_place.php',
    'file path' => $path,
    'type' => MENU_CALLBACK,
  );

  $items['admin/local/autocomplete/hours'] = array(
    'page callback' => '_local_autocomplete_hours',
    'access arguments' => array('administer site configuration'),
    'type' => MENU_CALLBACK,
  );

  $items['maker/get/fb/page/photo'] = array(
    'page callback' => '_local_maker_get_fb_page_photo',
    'type' => MENU_CALLBACK,
  );

  return $items;
}
