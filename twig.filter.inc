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
    'title' => t('Twig'), 
    'process callback' => '_twig_filter', 
  );
  return $filters;
}

/**
 * Callback: performs Twig rendering.
 */
function _twig_filter($text, $filter, $format, $langcode, $cache, $cache_id) {
  return _twig_render(array('template' => $text), array());
}
