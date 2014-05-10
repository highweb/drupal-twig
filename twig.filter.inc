<?php

/**
 * @file
 * Filter module functionality for the Twig module.
 */


/**
 * Implements hook_filter_info().
 */
function twig_filter_info() {
  $filters['twig'] = array(
    'title' => t('Twig template engine'), 
    'process callback' => '_twig_filter', 
  );
  return $filters;
}

/**
 * Callback: performs Twig rendering.
 */
function _twig_filter($text, $filter, $format, $langcode, $cache, $cache_id) {
  $path = libraries_get_path('twig');
  if (!$path) {
    drupal_set_message("Can't find 'twig' library.", 'error');
    return;
  }

  require_once $path . '/lib/Twig/Autoloader.php';
  Twig_Autoloader::register();
  $templates = array();
  module_load_include('inc', 'ctools', 'includes/export');
  foreach (ctools_export_crud_load_all('twig_template') as $key => $template) {
    $templates[$key] = $template->template;
  }
  $templates['_filter_text'] = $text;
  $loader = new Twig_Loader_Array($templates);
  $twig = new Twig_Environment($loader, array());
  return $twig->render('_filter_text');
}