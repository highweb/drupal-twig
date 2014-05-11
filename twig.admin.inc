<?php

/**
 * @file
 * Admin functionality for the Twig module.
 */

/**
 * Callback: creates Twig template field instance for the given entity type and bundle.
 */
function _twig_enable_field($entity_type, $bundle) {

  if (!field_info_field('twig_template')) {
    $field = array(
      'field_name' => 'twig_template',
      'cardinality' => 1,
      'type' => 'list_text',
      'settings' => array(
        'allowed_values_function' => '_twig_template_field_allowed_values',
      ),
    );
    field_create_field($field);
  }

  if (!field_info_instance($entity_type, 'twig_template', $bundle)) {
    $instance = array(
      'entity_type' => $entity_type,
      'bundle' => $bundle,
      'field_name' => 'twig_template',
      'label' => t('Template'),
      'widget' => array(
        'module' => 'options',
        'type' => 'options_select',
        'weight' => -10,
      ),
      'display' => array(
        'default' => array(
          'type' => 'hidden',
        ),
      ),
    );
    field_create_instance($instance);
  }

  // Redirect to the fields managemenet page:
  $admin_path = _field_ui_bundle_admin_path($entity_type, $bundle) . '/fields';
  drupal_goto($admin_path);
}
