<?php

$plugin = array(
  'schema' => 'twig_template',
  'access' => 'administer twig',

  'menu' => array(
    'menu item' => 'twig',
    'menu title' => 'Twig',
    'menu description' => 'Administer Twig templates.',
  ),

  'title singular' => t('template'),
  'title plural' => t('templates'),
  'title singular proper' => t('Twig template'),
  'title plural proper' => t('Twig templates'),

  'form' => array(
    'settings' => 'twig_ctools_export_ui_form',
  ),
);

function twig_ctools_export_ui_form(&$form, &$form_state) {
  $template = $form_state['item'];

  $form['template'] = array(
    '#type' => 'textarea',
    '#title' => t('Template text'),
    '#default_value' => $template->template,
    '#required' => true,
  );
}
