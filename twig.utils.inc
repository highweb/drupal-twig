<?php

/**
 * @file
 * Helper functions for the Twig module.
 */

/**
 * Renders a template with a given context.
 */
function _twig_render($template, $context) {
  $path = libraries_get_path('twig');
  if (!$path) {
    drupal_set_message("Can't find `twig` library.", 'error');
    return;
  }
  require_once $path . '/lib/Twig/Autoloader.php';
  Twig_Autoloader::register();

  $templates = _twig_get_db_templates();
  if (is_array($template)) {
    $templates['_'] = $template['template'];
    $template = '_';
  }

  $loader = new Twig_Loader_Array($templates);
  $twig = new Twig_Environment($loader, array());

  return $twig->render($template, $context);
}

/**
 * Returns all templates from the database.
 */
function _twig_get_db_templates() {
  $templates = array();
  module_load_include('inc', 'ctools', 'includes/export');
  foreach (ctools_export_crud_load_all('twig_template') as $key => $template) {
    $templates[$key] = $template->template;
  }
  return $templates;
}

/**
 * Extracts entity fields from a given entity renderable.
 */
function _twig_extract_entity_fields($build) {
  $fields = array();
  if (is_array($build)) {
    foreach ($build as $key => $value) {
      if ($key[0] !== '#') {
        $key = str_replace(array('twig_', 'bd_', 'field_'), '', $key);
        $items = _twig_extract_field_items($value);
        $fields[$key] = $items;
      }
    }
  }
  return $fields;
}

/**
 * Extracts field items from a given field renderable.
 */
function _twig_extract_field_items($build) {
  $items = array();
  if (isset($build['#items']) && is_array($build['#items'])) {
    foreach ($build['#items'] as $delta => $item) {
      $item = $build[$delta];
      if ($build['#field_type'] == 'field_collection') {
        $entity_build = reset($item['entity']['field_collection_item']);
        $fields = _twig_extract_entity_fields($entity_build);
        $wrapper = entity_metadata_wrapper($entity_build['#entity_type'], $entity_build['#entity']);
        if (isset($wrapper->twig_template) && $template = $wrapper->twig_template->value()) {
          $fields['template'] = $template;
        }
        $items[] = $fields;
      }
      else {
        $items[] = drupal_render($item);
      }
    }
    $field = field_info_field($build['#field_name']);
    if ($field['cardinality'] == 1) {
      return $items[0];
    }
  }
  return $items;
}
