<?php

/**
 * @file
 * Field module functionality for the Twig module.
 */

/**
 * Implements hook_field_extra_fields().
 */
function twig_field_extra_fields() {
  $entity_info = entity_get_info();
  $info = array();
  foreach (array_keys($entity_info) as $entity_type) {
    foreach (array_keys($entity_info[$entity_type]['bundles']) as $bundle) {
      if (!field_info_instance($entity_type, 'twig_template', $bundle)) {
        $info[$entity_type][$bundle]['form']['twig_template'] = array(
          'label' => t('Template'),
          'weight' => 0,
        );
      }
    }
  }
  return $info;
}

/**
 * Callback: returns allowed values for the Twig template field.
 */
function _twig_template_field_allowed_values() {
  module_load_include('inc', 'ctools', 'includes/export');
  $templates = ctools_export_crud_load_all('twig_template');
  $keys = array_keys($templates);
  sort($keys);
  return array_combine($keys, $keys);
}
